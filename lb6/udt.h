#ifndef _UDT_H_
#define _UDT_H_

#define POOL_SIZE 100

typedef struct {
    int head;
    int tail;
    int size;
    int data[POOL_SIZE];
} deque;

void PushHeadDeque(deque *d, int key);
void PushTailDeque(deque *d, int key);
void PopHeadDeque(deque *d);
void PopTailDeque(deque *d);
int TopHeadDeque(deque *d);
int TopTailDeque(deque *d);
void CreateDeque(deque *d);
void deleteDeque(deque *d);
int getSizeDeque(deque *d);
int isEmptyDeque(deque *d);

#endif