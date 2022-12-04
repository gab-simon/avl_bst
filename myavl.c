#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main(){
    int value;
    char recive[300];
    node_t* root = NULL;
    
    while(fgets(recive, 100, stdin)){
        char *token = strtok(recive, " ");

        if(strcmp(token, "i") == 0){
            token = strtok(NULL, " ");
            value = atoi(token);
            root = insertNode(root, value);
        }
        else if (strcmp(token, "r") == 0) {
            token = strtok(NULL, " ");
            value = atoi(token);
            root = removeNode(root, value);
        } else {
            printf("\n Error -- opção invalida! \n");
        }
    }

    printAVL(root, 0);
    return 0;
}