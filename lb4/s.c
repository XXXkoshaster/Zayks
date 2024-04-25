#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "item.h"
#define MAX_LEN 100

int main() {
    int state;
    char headValue[MAX_LEN];

    printf("Put first element of list\n");
    scanf("%s", headValue);
    Item *barrier = createNode(""); 
    
    addNode(barrier, 0, headValue);

    printf("Choose option: 1 - print list, 2 - add new element, 3 - delete element, 4 - size of list, 5 - delete every k-th element, 0 - finish script\n");

    while (scanf("%d", &state)) {
        if (state == 1) {
            stateOne(barrier);
        } else if (state == 2) {
            stateTwo(barrier);
        } else if (state == 3) {
            stateThree(barrier);
        } else if (state == 4) {
            stateFour(barrier);
        } else if (state == 5) {
            stateFive(barrier);
        } else if (state == 0) {
            break;
        } else {
            printf("Choose option from 0 to 5\n");
        }
    }
    
    deleteList(&barrier);
    return 0;
}


Item* createNode(char str[]) 
{
    Item* tmp = (Item*)malloc(sizeof(Item));
    strncpy(tmp->key, str, MAX_LEN);
    tmp->key[MAX_LEN] = '\0';
    tmp->next = NULL;
    return tmp;
}

void addNode(Item *barrier, int pos, char add[]) 
{
    Item* newNode = createNode(add);
    Item* current = barrier;

    while (pos-- > 0 && current->next != NULL) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}


void printList(Item *barrier) 
{
    Item* current = barrier->next; 
    printf("List: ");
    while (current != NULL) {
        printf("%s ", current->key);
        current = current->next;
    }
    printf("\n");
}

void deleteNode(Item *barrier, char str[]) 
{
    Item* current = barrier; 
    
    while (current->next != NULL && strcmp(current->next->key, str) != 0) {
        current = current->next;
    }

    if (current->next != NULL) {
        Item* toDelete = current->next;
        current->next = toDelete->next;
        free(toDelete);
        printf("Value: %s, deleted\n", str);
    } else {
        printf("Value not found\n");
    }
}

void deleteList(Item **barrier) 
{
    Item* current = *barrier;
    Item* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *barrier = NULL;
}


int sizeList(Item *barrier) 
{
    int size = 0;
    Item* current = barrier->next;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}


void specialAct(Item *barrier, int k) 
{
    if (k <= 0) {
        printf("Invalid k value\n");
        return;
    }

    int count = 0;
    Item* current = barrier; 
    while (current->next != NULL) {
        count++;
        if (count % k == 0) {
            Item* toDelete = current->next;
            current->next = toDelete->next;
            free(toDelete);
        } else {
            current = current->next;
        }
    }
    printf("Every %d-th element has been deleted\n", k);
}

void stateOne(Item *barrier) {
    printList(barrier);
    printf("Choose anoter option\n");   
}

void stateTwo(Item *barrier) {
    int pos;
    char str[MAX_LEN + 1];
    printf("Enter position and string: ");
    scanf("%d %s", &pos, str);
    addNode(barrier, pos, str);
    printf("Choose anoter option\n");   
}

void stateThree(Item *barrier) {
    char str[MAX_LEN + 1];
    printf("Enter string to delete: ");
    scanf("%s", str);
    deleteNode(barrier, str);
    printf("Choose anoter option\n");   
}

void stateFour(Item *barrier) {
    printf("Size of list: %d\n", sizeList(barrier));
    printf("Choose anoter option\n");   
}

void stateFive(Item *barrier) {
    int k;
    printf("Enter k: ");
    scanf("%d", &k);
    specialAct(barrier, k);
    printf("Choose anoter option\n");   
}