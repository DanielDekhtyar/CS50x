// Learning C with CS50x
// Lab 1: Population Growth
// https://cs50.harvard.edu/x/2023/labs/1/

#include <stdio.h>

int main(void)
{
  int n;   // the start amount of llamas and represent the current amount as the years go
  int end; // the end number of llamas
  do
  {
    printf("Start size : ");
    scanf("%d", &n);
  } while (n < 9);

  do
  {
    printf("End size : ");
    scanf("%d", &end);
  } while (n > end);

  int year = 0;
  while (n < end)
  {
    n = n + (n / 3) - (n / 4);
    year++;
  }

  printf("Years: %d", year);
  printf("\n");
}