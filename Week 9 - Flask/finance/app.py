from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, get_stock_name, is_valid_stock

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0][
        "username"
    ]

    holdings_db = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)

    transactions = []
    for trans in holdings_db:
        # Get the current price of each stock
        price = lookup(trans["symbol"])["price"]
        # Round the price to 2 decimal places
        price = round(price, 2)

        # Get the total value of each stock symbol
        value = trans["shares"] * lookup(trans["symbol"])["price"]
        # Round the value to 2 decimal places
        value = round(value, 2)

        transactions.append(
            {
                "symbol": trans["symbol"],
                "shares": trans["shares"],
                "price": price,
                "value": value,
            }
        )

    total_stock_value = 0

    for stock in transactions:
        total_stock_value += stock["value"]

    # Round to the nearest 2 decimal places
    total_stock_value = round(total_stock_value, 2)

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    user_cash = round(user_cash, 2)

    total = user_cash + total_stock_value

    return render_template(
        "index.html",
        username=username,
        transactions=transactions,
        total_stock_value=float(total_stock_value),
        cash=float(user_cash),
        total=float(total),
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        # Get the symbol of the stock ex. AAPL
        symbol = request.form.get("symbol")

        symbol = symbol.upper().strip()

        if not is_valid_stock(symbol):
            return apology("Invalid symbol")

        # Get the stock quote ex. {"price": 123.45, "symbol": "AAPL"}
        price = lookup(symbol)["price"]

        # Get the number of shares the user wants to buy
        shares = request.form["shares"]

        # Check if the user entered a valid number of shares
        if len(shares) <= 0 or float(shares) <= 0:
            return apology("Invalid number of shares")

        """ Buy the desired stock """
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = ?", session["user_id"]
        )

        total_cost = float(price) * float(shares)

        if user_cash[0]["cash"] < total_cost:
            return apology("Insufficient funds")

        # Look up current date and time
        date_time = datetime.now().strftime("%d-%m-%Y %H:%M:%S")

        # Update cash in users account
        db.execute(
            "UPDATE users SET cash = cash - ? WHERE id = ?",
            total_cost,
            session["user_id"],
        )

        # Add the transaction to transactions table
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)",
            session["user_id"],
            symbol,
            shares,
            price,
            date_time,
        )

        # Update the holdings table
        query_result = db.execute(
            "SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?",
            session["user_id"],
            symbol,
        )

        if query_result:
            # Get the number of shares in the table
            existing_shares_value = float(query_result[0]["shares"])

            # Add the new shares to the existing ones
            new_shares = existing_shares_value + float(shares)

            # Change the value in the database
            db.execute(
                "UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?",
                new_shares,
                session["user_id"],
                symbol,
            )
        else:
            # Create a new row in the holdings table
            db.execute(
                "INSERT INTO holdings (user_id, symbol, shares) VALUES (?, ?, ?)",
                session["user_id"],
                symbol,
                shares,
            )

        # Render the bought.html page with the transaction details
        return render_template(
            "bought.html",
            name=get_stock_name(symbol),
            symbol=symbol,
            shares=shares,
            price=price,
        )
    else:
        # Get the value of the 'symbol' parameter from the URL, if there is a symbol in the URL
        symbol = request.args.get("symbol", "")

        return render_template("buy.html", symbol=symbol)


@app.route("/history")
@login_required
def history():
    user_id = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0][
        "username"
    ]

    transactions_db = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY id DESC;", user_id
    )

    transactions = []
    for trans in transactions_db:
        # Get the current price of each stock
        price = db.execute(
            "SELECT price FROM transactions WHERE user_id = ? AND symbol = ?",
            user_id,
            trans["symbol"],
        )[0]["price"]
        # Round the price to 2 decimal places
        price = round(price, 2)

        transactions.append(
            {
                "symbol": trans["symbol"],
                "shares": trans["shares"],
                "price": price,
                "date": trans["date"],
            }
        )

    total_stock_value = 0

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    user_cash = round(user_cash, 2)

    return render_template(
        "history.html",
        username=username,
        transactions=transactions,
        cash=float(user_cash),
    )


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        """symbol is the stock symbol of the stock being quoted. ex: AAPL"""
        symbol = request.form["symbol"]
        symbol = symbol.upper().strip()

        if not is_valid_stock(symbol):
            return apology("Invalid symbol")

        """ symbol_lookup is the dictionary returned by the lookup function"""
        """ example: {"price": 123.45, "symbol": "AAPL"}"""
        symbol_lookup = lookup(symbol)

        # Turn the stock price from an int to a dollar format (ex: 123.45 to $123.45)
        price = usd(symbol_lookup["price"])

        name = get_stock_name(symbol)

        return render_template("quoted.html", name=name, symbol=symbol, price=price)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Ensure username and password are valid
        username = request.form.get("username")
        password = request.form.get("password")
        password_confirmation = request.form.get("confirmation")
        if not username:
            return apology("Hold on, I think you forgot to mention your username", 403)
        if not password:
            return apology("What about your password?", 403)

        if password != password_confirmation:
            return apology("Your passwords don't match", 403)

        # If all the user information is valid, add the user to the database
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)",
            username,
            generate_password_hash(password),
        )

        # Redirect to login page after successful registration
        return redirect("/login")

    elif request.method == "GET":
        return render_template("register.html")

    # Handle other request methods more explicitly
    else:
        return apology("Invalid request method", 405)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        symbol = request.form["symbol"]
        shares_to_sell = float(request.form["shares"])
        stock_price = lookup(symbol)["price"]

        shares_owned = float(
            db.execute(
                "SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?",
                session["user_id"],
                symbol,
            )[0]["shares"]
        )

        if shares_owned >= shares_to_sell:
            # Add an entry to the transactions table
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)",
                session["user_id"],
                symbol,
                -shares_to_sell,
                stock_price,
                datetime.now().strftime("%d-%m-%Y %H:%M:%S"),
            )

            # Add or deduct cash from user's account
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[
                    0
                ]["cash"]
                + shares_to_sell * stock_price,
                session["user_id"],
            )

            if shares_owned == shares_to_sell:
                # Delete the stock if the user has no more shares
                db.execute(
                    "DELETE FROM holdings WHERE user_id = ? AND symbol = ?",
                    session["user_id"],
                    symbol,
                )
            else:
                # Update the new number of shares
                db.execute(
                    "UPDATE holdings SET shares = ? WHERE user_id = ? AND symbol = ?",
                    shares_owned - shares_to_sell,
                    session["user_id"],
                    symbol,
                )

            if str(shares_to_sell).endswith(".0"):
                shares_to_sell = int(shares_to_sell)

            # Render the sold.html page with the transaction details
            return render_template(
                "sold.html",
                name=get_stock_name(symbol),
                symbol=symbol,
                shares=shares_to_sell,
                price=stock_price,
            )

        else:
            return apology("You don't have enough shares to sell")

    else:
        holdings_db = db.execute(
            "SELECT * FROM holdings WHERE user_id = ?", session["user_id"]
        )
        stocks = []
        for trans in holdings_db:
            stocks.append(
                {"name": get_stock_name(trans["symbol"]), "symbol": trans["symbol"]}
            )
        return render_template("sell.html", stocks=stocks)
