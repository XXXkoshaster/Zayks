#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main()
{
    int state;
    float parent_value;

    printf("Give value of root\n");
    scanf("%f", &parent_value);
    
    TreeNode *root = createNode(parent_value);
    
    printf("Choose option: 1 - add new node; 2 - delete node; 3 - print tree; 4 - get answer; 0 - exit\n");
    
    while (scanf("%d", &state))
    {
        if (state == 1) {
            stateOne(root);
        } else if (state == 2) {
            stateTwo(root);
        } else if (state == 3) {
            stateThree(root);
        } else if (state == 4) {
            stateFour(root);
        } else if (state == 0) {
            break;
        } else {
            printf("Choose option from 1 to 4\n");
        }
    }

    deleteNode(root);

    return 0;
}

TreeNode *createNode(float key) 
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Malloc returned NULL\n");             
        exit(1);
    }

    newNode->key = key;
    newNode->level = 1;
    newNode->firstChild = NULL;
    newNode->nextBrother = NULL;

    return newNode;
}

TreeNode *findNode(TreeNode *root, float key)
{
    if (root == NULL)
        return NULL;
    
    if (root->key == key)
        return root;

    TreeNode *child = root->firstChild;

    while (child) {
        TreeNode *found = findNode(child, key);
        
        if (found)
            return found;

        child = child->nextBrother;
    }
    
    return NULL;
}

void push(TreeNode *parent, float key)
{   
    if (parent == NULL) {
        printf("Error: parent node not founded\n");
        return;
    }

    TreeNode *child = createNode(key);
    child->level = parent->level + 1;
    child->parent = parent;

    if (parent->firstChild) {
        TreeNode *lastChild = parent->firstChild;
        
        while (lastChild->nextBrother) {
            lastChild = lastChild->nextBrother;
        }
        
        lastChild->nextBrother = child; 
    } else {
        parent->firstChild = child;
    }  

}

void deleteNode(TreeNode *node) {
    
    if (node == NULL) return;

    if (node->parent) {
        if (node->parent->firstChild == node) {
            node->parent->firstChild = node->nextBrother;
        } else {
            TreeNode *temp = node->parent->firstChild;
            while (temp && temp->nextBrother != node) {
                temp = temp->nextBrother;
            }
            if (temp) {
                temp->nextBrother = node->nextBrother;
            }
        }
    }

    while (node->firstChild) {
        deleteNode(node->firstChild);
    }
    
    free(node);
}

void printTree(TreeNode *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");
     
    printf("%.2f\n", root->key);

    TreeNode *child = root->firstChild;

    while(child) {
        printTree(child, level + 1);
        child = child->nextBrother;
    } 
}

int getNodeDegree(TreeNode *node)   
{
    int degree = 0;
    
    TreeNode *lastChild = node->firstChild;
    
    while (lastChild) {
        degree++;
        lastChild = lastChild->nextBrother;
    }   

    return degree;
}

int getAns(TreeNode *node)
{
    if (node == NULL)
        return 0;
    
    int counter = (node->key == (float)getNodeDegree(node)) ? 1 : 0;

    TreeNode *current = node->firstChild;

    while (current) {
        counter += getAns(current);
        current = current->nextBrother;
    }

    return counter;
}

void stateOne(TreeNode *root)
{
    float key, parent_value;

    printf("Print: parent_value child_value\n");
    scanf("%f %f", &parent_value, &key);
    
    TreeNode *parent = findNode(root, parent_value);
    push(parent, key);
    printf("Choose new option\n");
}

void stateTwo(TreeNode *root)
{
    float keyDeletedNode;
    
    printf("Print node for deleting:\n");
    scanf("%f", &keyDeletedNode);
    
    TreeNode *deletedNode = findNode(root, keyDeletedNode);
    deleteNode(deletedNode);

    printf("Choose new option\n");
}

void stateThree(TreeNode *root)
{
    printf("Your tree:\n");
    
    printTree(root, 0);

    printf("Choose new option\n");
}

void stateFour(TreeNode *root)
{
    int answer = getAns(root);
    
    printf("Answer is %d.\nChoose new option:\n", answer);   
}