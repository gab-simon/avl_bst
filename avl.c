#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

node_t* createNode(int value){
    node_t* node = malloc(sizeof(node_t));
    if(!node){
        printf("Erro ao alocar mémoria!");
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

node_t *maxNo(node_t *no) {
    node_t *current = no;

    // Percorre todo o caminho pra esquerda.
    while (current->rig != NULL)
        current = current->rig;

    return current;
}

// função para a rotação à esquerda
node_t* leftRotation(node_t* node){
    node_t *nodeAux, *nodeAuxRot;

    nodeAux = node->rig; // nodeAux aponta para a subárvore direito da root node
    nodeAuxRot = nodeAux->lef; // nodeAuxRot aponta para o filho esquerdo de nodeAux

    nodeAux->lef = node; // O filho esquerdo de nodeAux passa a ser a root node
    node->rig = nodeAuxRot; // O filho direito de node passa a ser nodeAuxRot

    // Recalcula a height dos nós que foram movimentados
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

    // Recalcula a altura dos nós que foram movimentados
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

    // Rotação à esquerda
    if(fator < -1 && checkBalance(root->rig) <= 0)
        root = leftRotation(root);

    // Rotação à direita
    else if(fator > 1 && checkBalance(root->lef) >= 0)
        root = rightRotation(root);

    // Rotação dupla à esquerda
    else if(fator > 1 && checkBalance(root->lef) < 0)
        root = leftRightRotation(root);

    // Rotação dupla à direita
    else if(fator < -1 && checkBalance(root->rig) > 0)
        root = rightLeftRotation(root);

    return root;
}

node_t* insertNode(node_t* root, int x){
    // Árvore vazia
    if(root == NULL) return createNode(x);
    // Inserção será à esquerda ou à direita
    else{ 
        if(x < root->value)
            root->lef = insertNode(root->lef, x);
        else
            root->rig = insertNode(root->rig, x);
    }

    // Recalcula a altura de todos os nós entre a root e o novo nó inserido
    root->height = larger(heightNode(root->lef), heightNode(root->rig)) + 1;

    // Verifica a necessidade de rebalancear a árvore
    root = balance(root);

    return root;
}

node_t* removeNode(node_t* root, int key) {
     if(root == NULL)
        return root;

    // Busca valor (BST)
    if(key < root->value)
        root->lef = removeNode(root->lef, key);
    else if(key > root->value)
        root->rig = removeNode(root->rig, key);
    else{ // Encontrou o valor.

        // Verifica se um dos filhos é nulo.
        if((root->lef == NULL) || (root->rig == NULL)){
            node_t *temp = NULL;
            if (root->lef != NULL)
                temp = root->lef;
            else 
                temp = root->rig;

            if (temp == NULL) {
                // Se é uma folha, ele exclui.
                temp = root;
                root = NULL;
            } 
            else{
                // Atualizando o no da root da subarvore.
                *root = *temp;
            }

            free(temp);
        }
        else{
            // Substituição pelo antecessor.
            node_t *temp = maxNo(root->lef);
            root->value = temp->value;
            root->lef = removeNode(root->lef, temp->value);
        }
    }

    if(root == NULL)
        return root;

    // Atualiza a altura do nó atual.
    root->height = larger(heightNode(root->lef), heightNode(root->rig)) + 1;

    // Verifica o fator de balanceamento entre os dois filhos do nó.
    int fator = checkBalance(root);
    if (fator > 1){
        if(checkBalance(root->lef) >= 0){
            return rightRotation(root);
        }
        else{
            root->lef = leftRotation(root->lef);
            return rightRotation(root);
        }
    }
    else if (fator < -1){
        if(checkBalance(root->rig) <= 0){
            return leftRotation(root);
        }
        else {
            root->rig = rightRotation(root->rig);
            return leftRotation(root);
        }
    }

    return root;
}

void printAVL(node_t *root, int level){
    if(root){
        printAVL(root->lef, level + 1);
        printf("%d,%d\n", root->value, level);
        printAVL(root->rig, level + 1);
    }
}