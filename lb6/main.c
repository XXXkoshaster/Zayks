#include <stdio.h>
#include "udt.h"


int FindMin(deque *d)
{
    int min_el = TopHeadDeque(d);
    int cur_el;
    int min_ind = 0;
    
    for (int i=0; i < d->size; ++i) {
        cur_el = TopHeadDeque(d);
        PopHeadDeque(d);
        PushTailDeque(d, cur_el);

        if (cur_el < min_el) {
            min_el = cur_el;
            min_ind = i;
        }
    }

    for (int i=0; i < d->size; ++i) {
        cur_el = TopHeadDeque(d);
        PopHeadDeque(d);

        if (min_ind != i) 
            PushTailDeque(d, cur_el);
    }

    return min_el;
}


void selectionSort(deque *d)
{
    deque sorted_d;
    CreateDeque(&sorted_d);
    int min_el;

    while (!isEmptyDeque(d))
    {
        min_el = FindMin(d);
        PushTailDeque(&sorted_d, min_el);
    }

    while (!isEmptyDeque(&sorted_d)) {
        min_el = TopHeadDeque(&sorted_d);
        PopHeadDeque(&sorted_d);
        PushTailDeque(d, min_el);
    }
    
}


void printDeque(deque *d) 
{
    int i, index;
    for (i = 0; i < d->size; i++) {
        index = (d->head + i) % POOL_SIZE;
        printf("%d ", d->data[index]);
    }
    printf("\n");
}


int main()
{   
    deque deck;
    
    CreateDeque(&deck);
    
    int state, key;
    
    do {
        printf("Choose the option: 1-push to head, 2-push to tail, 3 - sort deque, 4 - pop head, 5 - pop tail, 6 - size, 7 - check if empty, 8 - print deque\n");
        scanf("%d", &state);
        if (state == 1) {
            printf("Type value: ");
            scanf(" %d", &key);
            PushHeadDeque(&deck, key);
            printf("%d added to head\n", key);
        } else if (state == 2) {
            printf("Type value: ");
            scanf(" %d", &key);
            PushTailDeque(&deck, key);
            printf("%d added to tail\n", key);
        } else if (state == 3) {
            if (!isEmptyDeque(&deck)) {
                selectionSort(&deck);
                printDeque(&deck);
            } else {
                printf("Deque is empty\n");
            }
         } else if (state == 4) {
            PopHeadDeque(&deck);
            printf("Delete head\n");
        } else if (state == 5) {
            PopTailDeque(&deck);
            printf("Delete tail\n");    
        } else if (state == 6) {
            int size = getSizeDeque(&deck);
            printf("Size is %d\n", size);
        } else if (state == 7) {
            int empty = isEmptyDeque(&deck);
            printf("Deque is %s\n", empty ? "empty" : "not empty");
        } else if (state == 8) {
            printf("Deque:\n");
            printDeque(&deck);
        }
    } while(state);

    deleteDeque(&deck);

    return 0;
}
