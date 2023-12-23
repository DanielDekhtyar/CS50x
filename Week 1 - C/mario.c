// Learning C with CS50x
// Mario
// https://cs50.harvard.edu/x/2023/psets/1/mario/more/

#include <stdio.h>

void print_hash(int);

int main(void)
{
  int h;
  do // does the loop if 'h' given by the user is bigger the 8 or smaller then 1
  {
    printf("Hight (1-8 inclusive) : ");
    scanf("%d", &h);
  } while (h < 1 || h > 8);

  int l = h - 1; // will count the number of empty spaces to print
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < l; j++)
    {
      printf(" "); // the empty space before the #
    }
    int blocks = h - l; // represent the amount of blocks that needed to be build
    print_hash(blocks); // prints the first # before the space in between
    printf("  ");       // 2 empty spaces in the middle
    print_hash(blocks); // prints the second # after the space in between
    printf("\n");       // goes to the next line
    l--;
  }
}

void print_hash(int blocks)
{
  for (int k = 0; k < blocks; k++)
  {
    printf("#");
  }
}