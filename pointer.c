#include <cs50.h>
#include <stdio.h>

// struct called node containing an int identified as 'value',
// refernece to another node identfied as 'next'
typedef struct NODE
{
    int value;
    struct NODE *next;
} NODE;

NODE *rootNode;

void addNode(int value)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->value = value;
    newNode->next = NULL;

    if (rootNode == NULL)
    {
        rootNode = newNode;
        return;
    }

    NODE *trav = rootNode;

    while (trav->next == NULL)
    {
        trav = trav->next;
    }
}


    // iterate through the list and print each number until you hit the end i.e. 5, 10, 8, 17)
void displayList()
{
    NODE *trav = NULL;
    while (trav != NULL)
    {
        printf("%d", trav->value);
        trav = trav->next;

        if (trav == NULL)
        {
            printf("");
        } else {
            printf(", ");
        }
    }
    printf("\n");
}

int main(void)
{
    addNode(5);
    addNode(10);
    addNode(8);
    addNode(17);
    displayList();

    // printf("%i\n", rootNode.value);
    // printf("%i\n", rootNode.next->value);
    // printf("%i\n", rootNode.next->next->value);
    // printf("%i\n", rootNode.next->next->next->value);

    // GOAL IS TO be able to clear out all the items in the list automatically
        // each item needs to be removed individually, starting from the last value in the list
        // find the one beofre the last free him and make him NULL


}
