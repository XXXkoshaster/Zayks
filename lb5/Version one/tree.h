#ifndef _TREE_H_
#define _TREE_H_

#include "lexer.h"
#include "stack.h"

typedef struct tree_node {
    Token token;
    struct tree_node *left;
    struct tree_node *right;
} TreeNode;

TreeNode *tree_node_create(Token *token);
void tree_build(TreeNode **node, Stack *postfix_stack);
void tree_print_subtree(TreeNode *node, int depth);
void tree_print(TreeNode *node);
void tree_delete(TreeNode **node);
void tree_infix_linearization(TreeNode *node);

#endif
