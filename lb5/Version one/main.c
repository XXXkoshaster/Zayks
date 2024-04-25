#include <stdio.h>
#include <stdbool.h>

#include "tree.h"
#include "lexer.h"
#include "stack.h"
#include "tree_transform.h"
#include "parser.h"

int main(void)
{
    bool can_be_unary = true;
    Token token;

    Stack postfix_stack;
    Stack operators_and_brackets_stack;

    stack_create(&postfix_stack);
    stack_create(&operators_and_brackets_stack);

    while (token_read(&token, &can_be_unary)) {
        infix_to_postfix(&token, &postfix_stack, &operators_and_brackets_stack);
    }

    while (!stack_is_empty(&operators_and_brackets_stack)) {
        stack_push(&postfix_stack, stack_top(&operators_and_brackets_stack));
        stack_pop(&operators_and_brackets_stack);
    }

    TreeNode *root = NULL;
    tree_build(&root, &postfix_stack);

    printf("Expression tree:\n");
    tree_print(root);

    tree_transform(&root);
    printf("Transformed expression tree:\n");
    tree_print(root);

    printf("Resulting expression:\n");
    tree_infix_linearization(root);
    printf("\n");

    stack_destroy(&postfix_stack);
    stack_destroy(&operators_and_brackets_stack);

    return 0;
}
