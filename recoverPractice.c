#include <stdio.h>

int main(int argc, char *argv[])
{
    int x = 0xea;
    if (x >= 0xe0 && x <= 0xef)
    {
        printf("the number is in the range 0xe0 and 0xef\n");
    } else
    {
        printf("the statement is outside the range");
    }
}