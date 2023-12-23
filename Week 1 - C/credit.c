// Learning C with CS50x
// Credit
// https://cs50.harvard.edu/x/2024/psets/1/credit/


// This program checks if the credit card is valid using Luhn’s CheckSum Algorithm and says to which credit card network the card belongs


#include <stdio.h>
#include <stdbool.h>

int last_digit(long long num);
int product_sum(int num);
bool checkSum(long long num);
void printCardName(long long num);

int main(void)
{
  printf("Give me the credit card number: ");
  long long num;
  scanf("%lld", &num);
  bool isValid = checkSum(num);
  if (isValid)
  {
    printCardName(num);
  }
  else
    printf("INVALID\n");
}

int last_digit(long long num) // returns that last digit of a number
{
  return (num % 10);
}

int product_sum(int num) // returns the sum of the product of a number. exemple : gets:6. 6*2=12. 1+2=3. return:3
{
  num *= 2;
  return num % 10 + num / 10;
}

bool checkSum(long long num) // check if the credit card is valid using Luhn’s CheckSum Algorithm
{
  int oddSum = 0;  // a sum of all the numbers that we haven't multiplied
  int evenSum = 0; // a sum off all the numbers that we multiplied by 2
  while (num > 0)
  {
    oddSum = oddSum + last_digit(num);
    num = num / 10;
    evenSum = evenSum + product_sum(last_digit(num));
    num = num / 10;
  }
  return last_digit(oddSum + evenSum) == 0;
}

int cardLength(long long num)
{
  int length = 0;
  while (num > 0)
  {
    num = num / 10;
    length++;
  }
  return length;
}

void printCardName(long long num)
{
  int length = cardLength(num);
  do
  {
    num = num / 10; // leave the 2 first digits
  } while (num > 99);

  if (length == 15) // check if it is AMEX
  {
    if (num == 34 || num == 37)
    {
      printf("AMEX\n");
      return;
    }
    else
    {
      printf("INVALID\n");
      return;
    }
  }

  if (length == 13) // check if it is VISA
  {
    if (num / 10 == 4)
    {
      printf("VISA\n");
      return;
    }
    else
    {
      printf("INVALID\n");
      return;
    }
  }

  if (length == 16) // check if it is VISA or MASTERCARD
  {
    if (num == 51 || num == 52 || num == 53 || num == 54 || num == 55)
    {
      printf("MASTERCARD\n");
      return;
    }
    else if (num / 10 == 4)
    {
      printf("VISA\n");
      return;
    }
  }
  else
  {
    printf("INVALID\n");
    return;
  }
}
