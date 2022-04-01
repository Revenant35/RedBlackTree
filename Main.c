
#include <stdio.h>
#include "RBT.h"

RBT createTreeFromArray(int *array, int size){
    RBT Tree = RB_Create();
    for(int i = 0; i < size; i++){
        RB_Insert(Tree, array[i]);
    }
    return Tree;
}

int main(void){
    int array[] = {11, 2, 1, 7, 8, 5, 14, 15};
    int size = 8;

    RBT Tree = createTreeFromArray(array, size);
    inorderPrint(Tree);
    printf("%d", secondHighestNum(Tree));
}