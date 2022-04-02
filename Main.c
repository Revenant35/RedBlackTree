
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBT.h"


void terminate(RBT Tree){
    formatInorderPrint(Tree);
    formatHeightPrint(Tree);
    formatBlackHeightPrint(Tree);
    formatPrintNthHighestNum(Tree, 2);
    RB_Clear(Tree);
    free(Tree);
}

void run(){
    RBT Tree = RB_Create();
    char buf[8], *err;
    int input;

    if(!Tree)
        return;

    while(true){
        scanf("%[^\n]8s", buf);
        if(!strcmp(buf, "x\0") || !strcmp(buf, "X\0")){
            terminate(Tree);
            return;
        }
        input = (int)strtol(buf, &err, 10);
        if(strlen(err) == 0){
            if(!RB_Search(Tree, input))
                RB_Insert(Tree, input);
        } else {
            fprintf(stderr, "ERROR: INVALID INPUT\n");
        }
        fflush(stdin);
    }
}

int main(void){
    run();
}