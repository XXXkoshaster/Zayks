#ifndef __TREE_TRANSFORM_H__
#define __TREE_TRANSFORM_H__

#include "lexer.h"
#include "stack.h"
#include "tree.h"

int tree_must_be_transformed_unary(TreeNode **node);
int tree_must_be_transformed_power(TreeNode **node);
void transform_unary(TreeNode **node);
void transform_power(TreeNode **node);
void tree_transform(TreeNode **node);

#endif