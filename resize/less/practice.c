

#include <stdio.h>

int add(int x, int y)
{
    return x + y;
}

int modifyAdder(int *x, int y)
{
    // go to where x is ponting and add to the value at that position
    *x += 7;
    return *x + y;
}

int main(void)
{
    int a = 5;
    int b = 13;


    // have modify adder permanetly modify a
    printf("The total is %i\n", add(a, b));
    printf("The modified total is %i\n", modifyAdder(&a, b));
    printf("Running normal add again: %i\n", add(a, b));

    // the ampersand "&" tells you to give you the memory address of the variable not the value
    int* intPointer = &b;
    // printf("b is %i\n", b);

    //now go to that memory address and get that value
    *intPointer += 4;
    // printf("now b is %i\n", b);
}
