#include <stdlib.h>
#include <time.h>
#include "table.h"

void swap(Key *a, Key *b)
{
    Key tmp = *a;
    *a = *b;
    *b = tmp;
}

void CreateTable(FILE *file, Key *keys, Data *datas)
{
    int res = 0;
    for (int i = 0; i < COUNT_ELEMENTS; i++) {
        res = fscanf(file, "%d %[^\n]\n", &keys[i].key, datas[i].data);
        keys[i].index = i;
    }

    if (res) {
        puts("Таблица успешно создана");
    } else {
        fprintf(stderr, "Возникла ошибка при создании таблицы!\n");
    }
}

void PrintTable(const Key *keys, const Data *datas)
{
    printf("|------------------------------------------------------------|\n");
    printf("| Ключ  | Строка                                             |\n");
    printf("|------------------------------------------------------------|\n");
    for (int i = 0; i < COUNT_ELEMENTS; i++) {
        printf("| %-5d| %s\n", keys[i].key, datas[keys[i].index].data);     
        printf("|------------------------------------------------------------|\n");
    }
}


void Snap(Key *keys)
{
    srand(time(NULL));
    for (int i = 0; i < COUNT_ELEMENTS; i++) {
        int a = rand() % COUNT_ELEMENTS;
        int b = rand() % COUNT_ELEMENTS;
        swap(&keys[a], &keys[b]);
    }
}

void Reverse(Key *keys)
{
    for (int i = 0; i < COUNT_ELEMENTS / 2; i++) {
        swap(&keys[i], &keys[COUNT_ELEMENTS - i - 1]);
    }
}

