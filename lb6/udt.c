#include <stdio.h>

#include "udt.h"

void CreateDeque(deque *d)
{
    d->head = 0;
    d->tail = 0;
    d->size = 0;
}

int isEmptyDeque(deque *d)
{
    return d->size == 0;
}

int getSizeDeque(deque *d)
{
    return d->size;
}

void PushHeadDeque(deque *d, int key)
{
    if (d->size == POOL_SIZE) // Проверяем, не заполнен ли дек.
        return; // Если дек полон, мы не можем добавить новый элемент.

    // Если дек пуст, добавляем элемент в начало, не меняем индекс head.
    if (d->size == 0) {
        d->data[d->head] = key; // Вставляем элемент в текущую позицию head, которая равна 0.
    } else {
        // Уменьшаем head на 1 с учетом кольцевой структуры.
        d->head = (d->head - 1 + POOL_SIZE) % POOL_SIZE;
        d->data[d->head] = key; // Вставляем элемент в позицию перед текущим head.
    }
    d->size++; // Увеличиваем размер дека.
}


void PushTailDeque(deque *d, int key)
{
    if (d->size == POOL_SIZE) // Проверяем, не заполнен ли дек.
        return; // Если дек полон, мы не можем добавить новый элемент.

    // Вычисляем индекс для вставки элемента в конец дека.
    int index = (d->head + d->size) % POOL_SIZE;
    d->data[index] = key; // Вставляем элемент.
    d->size++; // Увеличиваем размер дека.
    d->tail = index; // Обновляем индекс tail.
}


void PopHeadDeque(deque *d)
{
    if (!d->size)
        return;
    d->head++;
    d->head %= POOL_SIZE;
    d->size--;
}

void PopTailDeque(deque *d)
{
    if (!d->size)
        return;
    d->tail = (d->tail - 1 + POOL_SIZE) % POOL_SIZE;
    d->size--;
}

char TopHeadDeque(deque *d)
{
    if (d->size) 
        return d->data[d->head];
    else 
        return '\0';
}

char TopTailDeque(deque *d)
{
    if (d->size) 
        return d->data[d->tail];
    else 
        return '\0';
}

void deleteDeque(deque *d) 
{
    d->head = 0;
    d->tail = 0;
    d->size = 0;
}
