#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "item.h"
#define MAX_LEN 100

int main()
{
    char headValue[MAX_LEN];
    int state;
    printf("Put first element of list\n");
    
    Item *barrier = intitBarrier();
    
    scanf("%s", headValue);
    Item *head = createNode(barrier, headValue);

    printf("Choose option: 1 - print tree, 2 - add new element, 3 - delete element, 4 -  size of list, 5 - delete every k-th element, 0 - finish script\n");

    while (scanf("%d", &state))
    {
        if (state == 1) {
            stateOne(head, barrier);
        } else if (state == 2) {
            stateTwo(&head, barrier);
        } else if (state == 3) {
            stateThree(&head, barrier);
        } else if (state == 4) {
            stateFour(head, barrier);
        } else if (state == 5) {
            stateFive(&head, barrier);
        } else if (state == 0) {
            break;
        } else {
            printf("Choose option from 0 to 5\n");
        }
    }
    
    deleteList(&head, barrier);
    free(barrier);
    
    return 0;
}
Item *intitBarrier(void)
{
    Item *barrier = malloc(sizeof(Item));

    barrier->next = barrier;

    return barrier;
}

void stateOne(Item *head, Item *barrier)
{
    printList(head, barrier);

    printf("Chose another option\n");
}

void stateTwo(Item **head, Item *barrier)
{
    char add[MAX_LEN];
    int pos;
   
    printf("Give positon and value:\n");
   
    scanf("%d %s", &pos, add);
    
    addNode(head, barrier, pos, add);

    printf("Chose another option\n");
}

void stateThree(Item **head, Item *barrier)
{
    char del[MAX_LEN];

    printf("Choose node to delete:\n");
    scanf("%s", del);

    deleteNode(head, barrier, del);
    printf("Chose another option\n");
}

void stateFour(Item *head, Item *barrier)
{
    int size = sizeList(head, barrier);

    printf("Size of list is %d\n", size);
    printf("Chose another option\n");
}

void stateFive(Item **head, Item *barrier)
{
    int k;
    
    printf("Choose k:\n");
    scanf("%d", &k);

    specialAct(head, barrier, k);

    printf("Chose another option\n");
}
    
Item *createNode(Item *barrier, char str[])
{
    Item *tmp = malloc(sizeof(Item));

    strncpy(tmp->key, str, MAX_LEN);
    tmp->key[MAX_LEN] = '\0';
    
    tmp->next = barrier;   

    return tmp;
}

void addNode(Item **head, Item *barrier, int pos, char add[])
{   
    int size = sizeList(*head, barrier);

    Item *newNode = createNode(barrier, add);

    if (pos < 0 || pos > size) {
        printf("Invalid position to insert\n");
    
    } else if (pos == 0) {
        newNode->next = *head;
        *head = newNode;
    
    } else {
        Item *tmp = *head;

        while (--pos) {
            tmp = tmp->next;

        }

        newNode->next = tmp->next;
        tmp->next = newNode;
    }
}

void printList(Item *head, Item *barrier)
{
    printf("Your list:\n");

    while(head != barrier) {   
        printf("%s ", head->key);
        head = head->next;
    }

    printf("\n");
}

void deleteNode(Item **head, Item *barrier, char str[])
{
    Item *tmp = *head;
    Item *prv;
    
    if (tmp->next == barrier) {
        *head = barrier;
        free(tmp);
        printf("Value: %s, deleted\n", str);
        return;
    }

    if (tmp != barrier && strcmp(str, tmp->key) == 0) {
        *head = tmp->next;
        printf("Value: %s, deleted\n", str);
        free(tmp);
        return;
    }

    while(tmp != barrier && strcmp(str, tmp->key) != 0) {
        prv = tmp;
        tmp = tmp->next;
    }

    if (tmp == barrier) {
        printf("Value not founded\n");
        return;
    }

    prv->next = tmp->next;
    free(tmp);

    printf("Value: %s, deleted\n", str);
}

void deleteList(Item **head, Item *barrier)
{
    Item *tmp = *head;
    Item *next;

    while (tmp != barrier) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }

    *head = barrier;
}

int sizeList(Item *head, Item *barrier)
{
    int size = 0;

    while (head != barrier) {
        size++;
        head = head->next;
    }

    return size;
}

void specialAct(Item **head, Item *barrier, int k)
{   
    Item *tmp = *head;
    Item *prv;
    int count = 0;

    if (tmp == barrier || k <= 0) {
        printf("Error. Choose anotherl k\n");
        return;
    }

    if (k == 1) {
        deleteList(head, barrier);
        printf("List was deleted\n");
        return;
    }

    while(tmp != barrier) {
        count++;

        if (k == count) {
            prv->next = tmp->next;
            free(tmp);
            tmp = prv->next;

            count = 0;
        }

        if (count != 0)
            prv = tmp;

        tmp = prv->next;
    }

    printf("Every %d-th element was deleted\n", k);
}