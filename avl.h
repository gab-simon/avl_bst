#ifndef __AVL__
#define __AVL__

struct node {
    int value;
    int height;
    struct node* lef;
    struct node* rig;
}; typedef struct node node_t;

node_t* createNode(int value);

int checkBalance(node_t* node);

int larger(int a, int b);

int heightNode(node_t *node);

node_t* leftRotation(node_t* node);

node_t* rightRotation(node_t* node);

node_t* leftRightRotation(node_t *node);

node_t* rightLeftRotation(node_t* node);

node_t* balance(node_t *root);

node_t* insertNode(node_t* root, int value);

node_t* removeNode(node_t* root, int key);

void printAVL(node_t *root, int level);

#endif