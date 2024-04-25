#include <math.h>
#include <stdlib.h>
#include "tree_transform.h"


int tree_must_be_transformed_unary(TreeNode **node)
{

    return ((*node) != NULL) && (token_is_unary_operator(&(*node)->token)) &&
           ((token_is_integer_value(&(*node)->right->token)) ||
            (token_is_double_value(&(*node)->right->token)));
}

int tree_must_be_transformed_power(TreeNode **node)
{
    return ((*node) != NULL) && (token_is_operator(&(*node)->token))
           && (token_is_power(&(*node)->token))
           && ((token_is_integer_value(&(*node)->left->token)) ||
               (token_is_double_value(&(*node)->left->token)))
           && (token_is_integer_value(&(*node)->right->token));

}

void transform_unary(TreeNode **node)
{

    TreeNode *temp_node = (TreeNode *) malloc(sizeof(TreeNode));

    if (token_is_minus(&(*node)->token)) {

        if (token_is_integer_value(&(*node)->right->token)) {
            temp_node->token.type = INTEGER_VALUE;
            temp_node->token.data.int_value = -(*node)->right->token.data.int_value;
        } else {
            temp_node->token.type = DOUBLE_VALUE;
            temp_node->token.data.double_value = -(*node)->right->token.data.double_value;
        }
    } else  if (token_is_plus(&(*node)->token)) {

        if (token_is_integer_value(&(*node)->right->token)) {
            temp_node->token.type = INTEGER_VALUE;
            temp_node->token.data.int_value = (*node)->right->token.data.int_value;
        } else {
            temp_node->token.type = DOUBLE_VALUE;
            temp_node->token.data.double_value = (*node)->right->token.data.double_value;
        }
    }

    temp_node->left  = NULL;
    temp_node->right = NULL;

    tree_delete(node);
    *node = temp_node;
}


void transform_power(TreeNode **node)
{
    TreeNode *temp_node = (TreeNode *) malloc(sizeof(TreeNode));

    if (token_is_integer_value(&(*node)->left->token) && token_is_positive_integer_value(&(*node)->right->token)) {
        temp_node->token.type = INTEGER_VALUE;
        temp_node->token.data.int_value = pow((*node)->left->token.data.int_value, (*node)->right->token.data.int_value);
    } else {
        temp_node->token.type = DOUBLE_VALUE;
        if (token_is_double_value(&(*node)->left->token)) {
            temp_node->token.data.double_value = pow((*node)->left->token.data.double_value, (*node)->right->token.data.int_value);
        } else {
            temp_node->token.data.double_value = pow((*node)->left->token.data.int_value, (*node)->right->token.data.int_value);
        }
    }

    temp_node->left  = NULL;
    temp_node->right = NULL;

    tree_delete(node);
    *node = temp_node;
}

void tree_transform(TreeNode **node)
{
    if ((*node) != NULL) {
        tree_transform(&((*node)->left));
        tree_transform(&((*node)->right));

        if (tree_must_be_transformed_unary(node)) {
            transform_unary(node);
        }

        if (tree_must_be_transformed_power(node)) {
            transform_power(node);
        }
    }
}
