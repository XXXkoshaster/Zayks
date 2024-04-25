#ifndef __NODE_H__
#define __NODE_H__

typedef struct Node {
    struct Node *left;
    struct Node *right;
    char key;
} Node;

#endif