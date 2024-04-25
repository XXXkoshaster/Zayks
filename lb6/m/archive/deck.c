#include "deck.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#define Tvalue int

void Init(Deck D) {//
    D.first = 0;
    D.size = 0;
    D.last = 0;
}
int Empty(Deck D) {
    return D.size == 0;
}

void PushFront(Deck D, Tvalue V) {//
    El_D* t=(El_D*) malloc (sizeof (El_D));
    t->next=D.first;
    if (!Empty(D))
        D.first->previous=t;

    D.first=t;
    D.first->V=V;
    if (!D.size)
        D.last=t;
    
    D.size++;
}

void PushBack(Deck D, Tvalue V) {//
    El_D* t=(El_D*) malloc (sizeof (El_D));
    t->previous=D.last;
    if (!Empty(D))
        D.last->next=t;
    
    D.last=t;
    D.last->V=V;
    if (!D.size)
        D.first=t;
    
    D.size++;
}

Tvalue PopFront(Deck D) {//
    if (Empty(D))
        printf("Дек пуст");
    else {
        Tvalue V=D.first->V;
        D.first=D.first->next;
        D.size--;
        return V;
    }
    return -1;
}

Tvalue PopBack(Deck D) {//
    if (Empty(D))
        printf("Дек пуст");
    else {
        Tvalue V=D.last->V;
        D.last=D.last->previous;
        D.last->next=NULL;
        D.size--;
        return V;
    }
    return -1;
}

Tvalue Top(Deck D) {
    if (Empty(D))
        printf("Дек пуст");
    else
        return D.first->V;
    return -1;
}

int Size(Deck D) {
    return D.size;
}

void Display(Deck D) {
    if(Empty(D))
        printf("\nДек пуст\n");
    else {
        printf("\n[ ");
        El_D* t=D.first;
        while(t) {
            printf("%d ",t->V); 
            t=t->next;
        }
        printf("]\n");
    }
}

void Cat(Deck D1, Deck D2) {//
    while (!Empty(D2))
        PushBack(D1, PopFront(D2));
}

void Append(Deck D1, Deck D2) {//
    int k = Size(D1);
    Cat(D1, D2);
    for (int i = 0; i < k; i++)
        PushBack(D1, PopFront(D1));
}  
