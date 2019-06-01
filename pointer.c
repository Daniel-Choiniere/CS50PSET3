#include <cs50.h>
#include <stdio.h>

// struct called node containing an int identified as 'value',
// refernece to another node identfied as 'next'


typedef struct
{
    int VALUE;
    node *next;
} node;

int add(int *x, int y)
{
    *x += 3;
    return *x + y;
}

int main(void)
{
    int a = 5;
    int b = 10;
    printf("the total is: %i\n", add(&a, b));
    printf("the total is: %i\n", add(&a, b));
}
