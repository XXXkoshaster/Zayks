#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void infix(Node **node);
void printTree(Node *node, int h);

int main()
{   
    Node *root = NULL;
    infix(&root);
    printTree(root, 0);
}

void infix(Node **node)
{
    char c = getchar();
    
    if (c == '(') {
        *node = malloc(sizeof(Node));
        
        infix(&(*node)->left);
        (*node)->key = getchar();
        infix(&(*node)->right);
        
        c = getchar();
    } else {
        *node = malloc(sizeof(Node));

        (*node)->key = c;
        (*node)->right = NULL;
        (*node)->left = NULL; 
    }
}

void printTree(Node *node, int h) {
    if (node != NULL) {
        printTree(node->left, h + 1);

        for (int i = 0; i < h; i++)
            printf(" ");
        
        printf("%c\n", node->key);

        printTree(node->right, h + 1);
        
    }
 }