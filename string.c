#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// void modifyArray(int theArray[])
// {
//     int theArray[2] = 44;
//     for (int number = 0; number < 3; number++)
//     {
//         printf("The number at %i is %i\n", number, theArray[number]);
//     }
// }


int main(void)
{
    char* name = "Dan";
    for (int i = strlen(name); i >= 0 ; i--)
    {
        printf("%c", name[i]);
    }
    // printf("Hello, %s\n", name);

    // int anArray[] = {28, 32, 29};
    // printf("pos 2 is %i\n", anArray[1]);
    // modifyArray(anArray);
    // printf("pos 3 is %i\n", anArray[2]);

    // int* anotherArray = malloc(sizeof(int) * 3);
    // anotherArray[0] = 8;
    // anotherArray[1] = 8;
    // anotherArray[3] = 8;
    // printf("the number at position 2 is %i\n", anotherArray[1]);
}