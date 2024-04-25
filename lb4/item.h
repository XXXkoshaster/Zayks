#ifndef  __ITEM_H__
#define __ITEM_H__
#define MAX_LEN 100

typedef struct Item {
    struct Item *next;
    char key[MAX_LEN];
}Item;

Item *intitBarrier(void);
void stateOne(Item *head, Item *barrier);
void stateTwo(Item **head, Item *barrier);
void stateThree(Item **head, Item *barrier);
void stateFour(Item *head, Item *barrier);
void stateFive(Item **head, Item *barrier);
Item *createNode(Item *barrier, char str[]);
void addNode(Item **head, Item *barrier, int pos, char add[]);
void printList(Item *head, Item *barrier);
void deleteNode(Item **head, Item *barrier, char str[]);
void deleteList(Item **head, Item *barrier);
int sizeList(Item *head, Item *barrier);
void specialAct(Item **head, Item *barrier, int k);
#endif
