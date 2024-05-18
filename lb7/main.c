#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

void PrintMenu()
{
    printf("\nВыберите действие:\n");
    printf("1) Создать таблицу.\n");
    printf("2) Произвести сортировку методом простой вставки.\n");
    printf("3) Бинарный поиск по ключу.\n");
    printf("4) Распечатать таблицу.\n");
    printf("5) Реверс таблицы.\n");
    printf("6) Перемешать таблицу.\n");
    printf("0) Выйти\n");
    printf("Действие: ");
}

Data *BinarySearch(Data *datas, Key *keys, int L, int R, int searchKey)
{
    if (R >= L) {
        int mid = L + (R - L) / 2;

        if (keys[mid].key == searchKey)
            return &datas[keys[mid].index];

        if (keys[mid].key > searchKey)
            return BinarySearch(datas, keys, L, mid - 1, searchKey);

        return BinarySearch(datas, keys, mid + 1, R, searchKey);
    }
}
void InsertionSort(Key *keys)
{
    for (int i = 1; i < COUNT_ELEMENTS; i++) {
        Key key = keys[i];
        int j = i - 1;

        while (j >= 0 && keys[j].key > key.key) {
            keys[j + 1] = keys[j];
            j = j - 1;
        }
        keys[j + 1] = key;
    }
}

int main(void)
{
    Key keys[COUNT_ELEMENTS] = {0};
    Data datas[POOL_SIZE] = {0};
    int state;

    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    do
    {
        PrintMenu();
        scanf("%d", &state);
        if (state == 0) break;
        switch (state)
        {
            case 1:
                CreateTable(file, keys, datas);
                fclose(file);
                printf("Таблица создана.\n");
                break;
            case 2:
                InsertionSort(keys);
                printf("Таблица отсортирована методом простой вставки.\n");
                break;
            case 3:
                printf("Введите ключ для поиска: ");
                int searchKey;
                scanf("%d", &searchKey);
                Data *result = BinarySearch(datas, keys, 0, COUNT_ELEMENTS - 1, searchKey);
                if (result) {
                    printf("Найденные данные: %s\n", result->data);
                } else {
                    printf("Данные с ключом %d не найдены.\n", searchKey);
                }
                break;
            case 4:
                PrintTable(keys, datas);
                break;
            case 5:
                Reverse(keys);
                printf("Таблица реверсирована.\n");
                break;
            case 6:
                Snap(keys);
                printf("Таблица перемешана.\n");
                break;
            default:
                printf("\nНет такого действия\n");
                break;
        }
    } while (state);
    
    return 0;
}
