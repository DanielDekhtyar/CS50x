-- Learning SQL with CS50x
-- Problem Set 7 : Fiftyville
-- The CS50 Duck was stolen !!!!!!!
-- https://cs50.harvard.edu/x/2024/psets/7/fiftyville/


-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the crime scene description
SELECT description
FROM crime_scene_reports
WHERE year = 2023 AND month = 7 AND day = 28
AND street = "Humphrey Street";

-- Crime scene description:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- Littering took place at 16:36. No known witnesses. 

-- Get the bakery security log
SELECT id, license_plate, activity
FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28
AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Bakery security log:
+-----+---------------+----------+
| id  | license_plate | activity |
+-----+---------------+----------+
| 260 | 5P2BI95       | exit     |
| 261 | 94KL13X       | exit     |
| 262 | 6P58WS2       | exit     |
| 263 | 4328GD8       | exit     |
| 264 | G412CB7       | exit     |
| 265 | L93JTIZ       | exit     |
| 266 | 322W7JE       | exit     |
| 267 | 0NTHK55       | exit     |
+-----+---------------+----------+

-- Get the interviews
SELECT id, name, transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28;

-- Interviews:
+-----+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| id  |  name   |                                                                                                                                                     transcript                                                                                                                                                      |
+-----+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| 158 | Jose    | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”                                                                                                                               |
| 159 | Eugene  | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”                                                                                                                                                                                      |
| 160 | Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.                                                                                                                   |
| 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma s bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
| 191 | Lily    | Our neighboring courthouse has a very annoying rooster that crows loudly at 6am every day. My sons Robert and Patrick took the rooster to a city far, far away, so it may never bother us again. My sons have successfully arrived in Paris.                                                                        |
+-----+---------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- Get the phone calls
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2023 AND month = 7 AND day = 28
AND duration < 60;

-- Phone calls:
+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (130) 555-0289 | (996) 555-8899 | 51       |
| (499) 555-9472 | (892) 555-8872 | 36       |
| (367) 555-5533 | (375) 555-8161 | 45       |
| (499) 555-9472 | (717) 555-1342 | 50       |
| (286) 555-6063 | (676) 555-6554 | 43       |
| (770) 555-1861 | (725) 555-3243 | 49       |
| (031) 555-6622 | (910) 555-3251 | 38       |
| (826) 555-1652 | (066) 555-9701 | 55       |
| (338) 555-6650 | (704) 555-2131 | 54       |
+----------------+----------------+----------+

-- Find the people with those phone numbers

-- Only callers
SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND passport_number IS NOT NULL
    AND duration < 60
);


-- Only receivers
SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND license_plate IS NOT NULL
    AND duration < 60
);

-- Caller names:
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
| 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
+--------+---------+----------------+-----------------+---------------+

-- Receiver names:
+--------+------------+----------------+-----------------+---------------+
|   id   |    name    |  phone_number  | passport_number | license_plate |
+--------+------------+----------------+-----------------+---------------+
| 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
| 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
| 567218 | Jack       | (996) 555-8899 | 9029462229      | 52R0Y8U       |
| 712712 | Jacqueline | (910) 555-3251 | NULL            | 43V0R5D       |
| 847116 | Philip     | (725) 555-3243 | 3391710505      | GW362R6       |
| 864400 | Robin      | (375) 555-8161 | NULL            | 4V16VO0       |
| 953679 | Doris      | (066) 555-9701 | 7214083635      | M51FA04       |
+--------+------------+----------------+-----------------+---------------+

-- Find if any of those license plates match the bakery security log
SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND hour = 10 AND minute >= 15 AND minute <= 25
);

-- Here are the people who were in the bakery security log:
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
| 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+

-- Find the earliest flight out of Fiftyville tomorrow
SELECT *
FROM flights
WHERE origin_airport_id IN (
    SELECT id
    FROM airports
    WHERE city = "Fiftyville"
)
AND year = 2023 AND month = 7 AND day = 29
ORDER BY hour ASC, minute ASC
LIMIT 1;

-- Earliest flight from Fiftyville:
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+

-- Find if anyone from the callers was on the flight
SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28
    AND duration < 60
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
);

-- People on the flight that where also the callers on that day:
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
| 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+

-- Find all the transactions at the ATM on Leggett Street
SELECT id, account_number, transaction_type, amount
FROM atm_transactions
WHERE year = 2023 AND month = 7 AND day = 28
AND atm_location = "Leggett Street" AND transaction_type = 'withdraw'
ORDER BY account_number;

-- All the withdrawals from the ATM on Leggett Street on that day:
+-----+----------------+------------------+--------+
| id  | account_number | transaction_type | amount |
+-----+----------------+------------------+--------+
| 269 | 16153065       | withdraw         | 80     |
| 288 | 25506511       | withdraw         | 20     |
| 336 | 26013199       | withdraw         | 35     |
| 264 | 28296815       | withdraw         | 20     |
| 246 | 28500762       | withdraw         | 48     |
| 267 | 49610011       | withdraw         | 50     |
| 266 | 76054385       | withdraw         | 60     |
| 313 | 81061156       | withdraw         | 30     |
+-----+----------------+------------------+--------+

-- Find the people who withdrew the money
SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate, bank_accounts.account_number
FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw'
ORDER BY bank_accounts.account_number;

-- All the people who withdrew the money:
+--------+---------+----------------+-----------------+---------------+----------------+
|   id   |  name   |  phone_number  | passport_number | license_plate | account_number |
+--------+---------+----------------+-----------------+---------------+----------------+
| 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       | 16153065       |
| 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       | 25506511       |
| 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       | 26013199       |
| 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       | 28296815       |
| 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       | 28500762       |
| 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       | 49610011       |
| 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       | 76054385       |
| 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       | 81061156       |
+--------+---------+----------------+-----------------+---------------+----------------+

-- Currently the theft Bruce

-- Find the destination of the flight
SELECT id, abbreviation, full_name, city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
);

-- The airport where Bruce flew to:
+----+--------------+-------------------+---------------+
| id | abbreviation |     full_name     |     city      |
+----+--------------+-------------------+---------------+
| 4  | LGA          | LaGuardia Airport | New York City |
+----+--------------+-------------------+---------------+

-- To find who help, I check who the theft called
-- I found the Robin has helped the theft
