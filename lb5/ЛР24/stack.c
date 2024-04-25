#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "symbol.h"
#include "stack.h"

#define MINSIZE 4

STACK *stack_create() {
    STACK *stack = (STACK*)malloc(sizeof(STACK));
    stack->cap = MINSIZE;
    stack->size = 0;
    stack->body = (symbol*)malloc(sizeof(symbol) * stack->cap);
    return stack;
}
void stack_delete(STACK *stack) {
    free(stack->body);
    free(stack);
}
bool stack_empty(STACK *stack) {
    return stack->size == 0;
}

void stack_push(STACK *stack, symbol t) {
    if(stack->size <= stack->cap) {
        stack->cap *= 2;
        stack->body = (symbol*)realloc(stack->body, sizeof(symbol) * stack->cap);
    }

    stack->body[stack->size] = t;
    stack->size++;
}

symbol stack_pop(STACK *stack) {
    symbol res = stack->body[stack->size - 1];
    stack->size--;

    if(stack->size * 2 < stack->cap && stack->cap > MINSIZE) {
        stack->cap /= 2;
        stack->body = (symbol*)realloc(stack->body, sizeof(symbol) * stack->cap);
    }

    return res;
}

symbol stack_peek(STACK *stack) {
    return stack->body[stack->size - 1];
}
