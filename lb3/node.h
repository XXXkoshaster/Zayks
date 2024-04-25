#ifndef __NODE_H__
#define __NODEENT_H__

typedef struct TreeNode{
    float key;
    int level;
    struct TreeNode *parent;
    struct TreeNode *firstChild;
    struct TreeNode *nextBrother;
} TreeNode;

TreeNode *createNode(float key);

TreeNode *findNode(TreeNode *root, float key);

void push(TreeNode *parent, float key);

void deleteNode(TreeNode *node);

void printTree(TreeNode *node, int level);

int getNodeDegree(TreeNode *node); 

int getAns(TreeNode *node);  

void stateOne(TreeNode *root);

void stateTwo(TreeNode *root);

void stateThree(TreeNode *root);

void stateFour(TreeNode *root);

#endif