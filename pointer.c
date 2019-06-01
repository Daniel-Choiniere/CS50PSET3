#include <cs50.h>
#include <stdio.h>

// struct called node containing an int identified as 'value',
// refernece to another node identfied as 'next'
typedef struct NODE
{
    int value;
    struct NODE *next;
} NODE;


void addNode(int value, NODE *homeNode)
{
    NODE *newNode = malloc(sizeof(NODE));
    newNode->value = value;
    newNode->next = NULL;
    homeNode->next = newNode;
}

int main(void)
{
    NODE rootNode;
    rootNode.value = 5;
    rootNode.next = NULL;

    addNode(10, &rootNode);

    printf("%i\n", rootNode.value);
    printf("%i\n", rootNode.next->value);
}
