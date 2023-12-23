// Learning C with CS50x
// Hello
// https://cs50.harvard.edu/x/2024/psets/1/hello/

#include <stdio.h>

int get_size(void);
void print_grid(int n);

int main(void)
{
    int n = get_size();

    print_grid(n);
}

int get_size(void)
{
    int n;
    do
    {
        printf("What size do you want it to be? ");
        scanf("%d", &n);
    } while (n < 1);
    return n;
}

void print_grid(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}