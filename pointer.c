#include <cs50.h>
#include <stdio.h>

// struct called node containing an int identified as 'value',
// refernece to another node identfied as 'next'
typedef struct NODE
{
    int value;
    struct NODE *next;
} NODE;


// iterate through the linked list until you get to the end

void addNode(int value, NODE *homeNode)
{
    NODE *trav = homeNode;
    while (true)
        {
            if (trav->next == NULL)
        {
            NODE *newNode = malloc(sizeof(NODE));
            newNode->value = value;
            newNode->next = NULL;
            trav->next = newNode;
            break;
        } else
        {
            trav = trav->next;
            // printf("Moved Deeper\n");
        }
    }
}

    // iterate through the list and print each number until you hit the end i.e. 5, 10, 8, 17)
void displayList(NODE *trav)
{
    printf("Hello!\n");
}

int main(void)
{
    NODE rootNode;
    rootNode.value = 5;
    rootNode.next = NULL;

    addNode(10, &rootNode);

    // printf("%i\n", rootNode.value);
    // printf("%i\n", rootNode.next->value);

    addNode(8, &rootNode);
    addNode(17, &rootNode);

    // GOAL IS TO GET THE NUMBERS TO BE DISPLAYED ONE BY ONE
    displayList(&rootNode);
}
