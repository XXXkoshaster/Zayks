#include <stdio.h>
#include "udt.h"

void swap(int *xp, int *yp)
{
    int tmp = *xp;
    *xp = *yp;
    *yp = tmp;
}

void selectionSort(deque *d)
{
    int i, j, min_idx, real_i, real_min_idx, real_j;

    for (i = 0; i < d->size - 1; i++) {
        real_i = (d->head + i) % POOL_SIZE;
        min_idx = real_i;

        for (j = i + 1; j < d->size;  j++) {
            real_j = (d->head + j) % POOL_SIZE; 
            if (d->data[real_j] < d->data[min_idx])
                min_idx = real_j;
        }
            
        if (min_idx != real_i)
            swap(&(d->data[min_idx]), &(d->data[real_i]));
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
        printf("Choose the option: 1-push to head, 2-push to tail, 3-print min, 4-print max, 5-delete min, 6-delete max, 7-size, 8-check if empty, 9-print deque\n");
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
                char head = TopHeadDeque(&deck);
                printf("Min is %d\n", head);
            } else {
                printf("Deque is empty\n");
            }
        } else if (state == 4) {
            if (!isEmptyDeque(&deck)) {
                selectionSort(&deck);
                char tail = TopTailDeque(&deck);
                printf("Max is %d\n", tail);
            } else {
                printf("Deque is empty\n");
            }
        } else if (state == 5) {
            if (!isEmptyDeque(&deck)) {
                selectionSort(&deck);
                PopHeadDeque(&deck);
                printf("Min is deleted\n");
            } else {
                printf("Deque is empty\n");
            }
        } else if (state == 6) {
            if (!isEmptyDeque(&deck)) {
                selectionSort(&deck);
                PopTailDeque(&deck);
                printf("Max is deleted\n");
            } else {
                printf("Deque is empty\n");
            }
        } else if (state == 7) {
            int size = getSizeDeque(&deck);
            printf("Size is %d\n", size);
        } else if (state == 8) {
            int empty = isEmptyDeque(&deck);
            printf("Deque is %s\n", empty ? "empty" : "not empty");
        } else if (state == 9) {
            printf("Deque:\n");
            printDeque(&deck);
        }
    } while(state);

    deleteDeque(&deck);

    return 0;
}
