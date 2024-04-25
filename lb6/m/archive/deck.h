#ifndef _DECK_H_
#define _DECK_H_

#define N 100
#define Tvalue int

typedef struct Deck Deck;
typedef struct El_D El_D;

struct El_D {
    Tvalue V;
    El_D* next;
    El_D* previous;
};

struct Deck {
    El_D* first;
    El_D* last;
    int size;
};

void Init(Deck D);//
int Empty(Deck D);
void PushFront(Deck D, Tvalue V);//
void PushBack(Deck D, Tvalue V);//
Tvalue PopFront(Deck D);//
Tvalue PopBack(Deck D);//
Tvalue Top(Deck D);
int Size(Deck D);
void Display(Deck D);
void Cat(Deck D1, Deck D2);//
void Append(Deck D1, Deck D2);//

#endif
