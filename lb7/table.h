#ifndef _table_h_
#define _table_h_

#include <stdio.h>

#define POOL_SIZE 100
#define COUNT_ELEMENTS 12

typedef struct Key 
{
    int key;
    int index;
} Key;

typedef struct Data 
{
    char data[POOL_SIZE];
} Data;

void CreateTable(FILE *file, Key *keys, Data *datas);
void PrintTable(const Key *keys, const Data *datas);
void swap(Key *a, Key *b);
void Snap(Key *keys);
void Reverse(Key *keys);

#endif