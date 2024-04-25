#ifndef __stack_h__
#define __stack_h__

#include <stdbool.h>

#include "symbol.h"

// стек на массиве
typedef struct {
    symbol *body; //указатель на резидентный массив (вектор!)
    int size; // текущий размер стека
    int cap; // максимальная вместимость
} STACK;

STACK *stack_create();
void stack_delete(STACK *stack);
bool stack_empty(STACK *stack);
void stack_push(STACK *stack, symbol t);
symbol stack_pop(STACK *stack);
symbol stack_peek(STACK *stack);

#endif