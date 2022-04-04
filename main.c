
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <asm-generic/errno.h>
#include <errno.h>
#include "rbt.h"

#define BUFF_SIZE (64)
#define OK       (0)
#define NO_INPUT (1)
#define TOO_LONG (2)
#define NTH_LARGEST_ELEMENT (2)


void terminate(RBT Tree){
    Format_Inorder_Print(Tree);
    Format_Height_Print(Tree);
    Format_Black_Height_Print(Tree);
    Format_Print_Nth_Highest_Num(Tree, NTH_LARGEST_ELEMENT);
    RB_Clear(Tree);
    RB_Free(Tree);
}


int readLine(char *buff) {
    int ch, extra;

    if (fgets (buff, BUFF_SIZE, stdin) == NULL)
        return NO_INPUT;

    if (buff[strlen(buff)-1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    buff[strlen(buff)-1] = '\0';
    return OK;
}

bool StrToInt(char *str, int *number){
    long input;
    char *end;

    errno = 0;
    input = strtol(str, &end, 10);

    if(errno == ERANGE || input > INT_MAX || input < INT_MIN){
        fprintf(stderr, "ERROR: input out of bounds\n");
        return 0;
    }


    if(end == str || (*end && *end != '\n')){
        fprintf(stderr, "ERROR: invalid input\n");
        return 0;
    }

    *number = (int) input;
    return 1;
}

void run(){
    RBT Tree = RB_Create();
    char buf[BUFF_SIZE];
    int input;

    if(!Tree)
        return;

    printf("Enter a list of integers seperated by newlines\n");
    printf("Enter 'x' or 'X' to finish entering integers\n");

    while(true){
        switch(readLine(buf)){
            case 0:
                if(!strcmp("X", buf) || !strcmp("x", buf)) {
                    terminate(Tree);
                    return;
                }
                if(StrToInt(buf, &input)) {
                    if (!RB_Search(Tree, input)) {
                        RB_Insert(Tree, input);
                    } else {
                        fprintf(stderr, "ERROR: element %d already exists\n", input);
                    }
                }

                break;
            case 1:
                break;
            case 2:
                fprintf(stderr, "ERROR: input is too long\n");
                break;
        }
        if(!strcmp(buf, "x\0") || !strcmp(buf, "X\0")){
            terminate(Tree);
            return;
        }
    }
}

int main(void){
    run();
}