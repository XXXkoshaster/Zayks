#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"
#define N 100
#define Tvalue int

void QuickSort(Deck D) {//
    Deck D1, D2; 
    Tvalue V, V1;
    if (!Empty(D)) {
        Init(D1);
        Init(D2);
        V = PopFront(D);
        while (!Empty(D)) {
            if (Top(D) < V)
                PushBack(D1, PopFront(D));
            else
                PushBack(D2, PopFront(D));
        }
        QuickSort(D1);
        QuickSort(D2);
        PushBack(D1, V);
        Cat(D1, D2);
        Cat(D, D1);
    }
}

int main() {
    int k=11, i, n;
    Deck D;
    Init(D);
    Tvalue v;
    Deck D1, D2;
    while (k) {
        printf("\nВыберите действие:"
        "\n1. Создать случайный дек\n2. Распечатать дек\n3. Вывести размер дека"
        "\n4. Вставить в начало дека"
        "\n5. Вставить в конец дека"
        "\n6. Удалить первый элемент дека"
        "\n7. Удалить последний элемент дека"
        "\n8. Сортировка дека\n9. Очистить дек"
        "\n10. Конкатенация двух деков" 
        "\n0. Выйти"
        "\nВведите номер действия =>");
        scanf("%d", &k);
        switch (k) {
            case 1: 
                printf("Введите количество элементов =>");
                scanf("%d", &n);
                Init(D1);
                for (i = 0; i < n / 2; i++) {
                    v = rand()%11;
                    PushBack(D1, v);
                }
                Init(D2);
                for (i = 0; i < n - n / 2; i++) {
                    v = rand()%11;
                    PushFront(D2, v);
                }
                Cat(D1, D2);
                Append(D, D1);
                Display(D);
                getchar();
                break;
            
            case 2: 
                Display(D);
                getchar();
                break;
            
            case 3: 
                n = Size(D);
                printf("\nРазмер дека =%d\n", n);
                break;
            
            case 4:  
                printf("\nВведите значение элемента =>");
                scanf("%d", &v);
                PushFront(D, v);
                break;
            
            case 5:  
                printf("\nВведите значение элемента =>");
                scanf("%d", &v);
                PushBack(D, v);
                break;
            
            case 6: 
                v = PopFront(D);
                printf ("\nЭлемент =%d удалён\n", v);
                break;
            
            case 7: 
                v = PopBack(D);
                printf("\nЭлемент =%d удалён\n", v);
                break;
            
            case 8: 
                QuickSort(D);
                Display(D);
                getchar();
                break;
                
            case 9:
                Init(D);
                break;
                
            case 10: 
                printf("\nВведите размер второго дека =>");
                int n1;
                scanf("%d", &n1);
                printf("\nВыберите действие:\n1) Создать рандомный дек\n2) Задать элементы дека вручную\nВведите номер действия =>");
                int k1;
                scanf("%d", &k1);
                Init(D1);
                if (k1==1){
                    for (int i=0; i<n1; i++){
                        v=rand()%11;
                        PushBack(D1, v);
                    }
                }
                if (k1==2){
                    printf("\nВведите значения элементов =>");
                    for(int i=0; i<n1; i++){
                        scanf("%d", &v);
                        PushBack(D1, v);
                    }
                }
                Cat(D, D1);
                Display(D);
                getchar();
                break;
        }
    }
}
