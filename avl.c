#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

node_t* createNode(int value){
    node_t* node = malloc(sizeof(node_t));
    if(!node){
        printf("Nao foi possível alocar memoria");
        return NULL;
    }

    node->value = value;
    node->lef = NULL;
    node->rig = NULL;
    node->height = 0;

    return node;
}

int larger(int a, int b){
    if(a > b)
        return a;
    return b;
}

int heightNode(node_t *node){
    if(node == NULL)
        return -1;
    else
        return node->height;
}

int checkBalance(node_t* node){
    if(!node)
        return 0;
    return (heightNode(node->lef) - heightNode(node->rig));
}

/*
    função para a rotação à lefuerda
*/
node_t* leftRotation(node_t* node){
    node_t *nodeAux, *nodeAuxRot;

    nodeAux = node->rig; // nodeAux aponta para a subárvore rigeita da root node
    nodeAuxRot = nodeAux->lef; // nodeAuxRot aponta para o filho lefuerdo de nodeAux

    nodeAux->lef = node; // o filho lefuerdo de nodeAux passa a ser a root node
    node->rig = nodeAuxRot; // o filho rigeito de node passa a ser nodeAuxRot

    // recalcula a height dos nós que foram movimentados
    node->height = larger(heightNode(node->lef), heightNode(node->rig)) + 1;
    nodeAux->height = larger(heightNode(nodeAux->lef), heightNode(nodeAux->rig)) + 1;

    return nodeAux;
}

node_t* rightRotation(node_t* node){
    node_t *nodeAux, *nodeAuxRot;

    nodeAux = node->lef; 
    nodeAuxRot = nodeAux->rig;

    nodeAux->rig = node;
    node->lef = nodeAuxRot; 

    // recalcula a height dos nós que foram movimentados
    node->height = larger(heightNode(node->lef), heightNode(node->rig)) + 1;
    nodeAux->height = larger(heightNode(nodeAux->lef), heightNode(nodeAux->rig)) + 1;

    return nodeAux;
}

node_t* leftRightRotation(node_t *node){
    node->lef = leftRotation(node->lef);
    return rightRotation(node);
}

node_t* rightLeftRotation(node_t* node){
    node->rig = rightRotation(node->rig);
    return leftRotation(node);
}

node_t* balance(node_t *root){
    int fator = checkBalance(root);

    // Rotação à lefuerda
    if(fator < -1 && checkBalance(root->rig) <= 0)
        root = leftRotation(root);

    // Rotação à rigeita
    else if(fator > 1 && checkBalance(root->lef) >= 0)
        root = rightRotation(root);

    // Rotação dupla à lefuerda
    else if(fator > 1 && checkBalance(root->lef) < 0)
        root = leftRightRotation(root);

    // Rotação dupla à rigeita
    else if(fator < -1 && checkBalance(root->rig) > 0)
        root = rightLeftRotation(root);

    return root;
}

node_t* insert(node_t* root, int x){
    if(root == NULL) // árvore vazia
        return createNode(x);
    else{ // inserção será à lefuerda ou à rigeita
        if(x < root->value)
            root->lef = insert(root->lef, x);
        else
            root->rig = insert(root->rig, x);
    }

    // Recalcula a height de todos os nós entre a root e o novo nó inserido
    root->height = larger(heightNode(root->lef), heightNode(root->rig)) + 1;

    // verifica a necessidade de rebalancear a árvore
    root = balance(root);

    return root;
}

node_t* removeNode(node_t* root, int key) {
    if(root == NULL){
        return NULL;
    } else { // procura o nó a removeNode
        if(root->value == key) {
            // removeNode nós folhas (nós sem filhos)
            if(root->lef == NULL && root->rig == NULL) {
                free(root);
                return NULL;
            }
            else{
                node_t *nodeAux = root->lef;
                // removeNode nós que possuem 2 filhos
                if(!(root->lef) && !(root->rig)){
                    while(nodeAux->rig != NULL)
                        nodeAux = nodeAux->rig;
                    root->value = nodeAux->value;
                    nodeAux->value = key;
                    root->lef = removeNode(root->lef, key);
                    return root;
                }
                else{
                    // removeNode nós que possuem apenas 1 filho
                    if(root->lef != NULL)
                        nodeAux = root->lef;
                    else
                        nodeAux = root->rig;
                    free(root);
                    return nodeAux;
                }
            }
        } else {
            if(key < root->value)
                root->lef = removeNode(root->lef, key);
            else
                root->rig = removeNode(root->rig, key);
        }

        // Recalcula a height de todos os nós entre a root e o novo nó inserido
        root->height = larger(heightNode(root->lef), heightNode(root->rig)) + 1;

        // verifica a necessidade de rebalancear a árvore
        root = balance(root);

        return root;
    }
}

void printAVL(node_t *root, int level){
    if(root){
        printAVL(root->lef, level + 1);
        printf("%d,%d\n", root->value, root->height);
        printAVL(root->rig, level + 1);
    }
}