#ifndef REDBLACKTREE_RBT_H
#define REDBLACKTREE_RBT_H

#include <stdbool.h>

#define BLACK (1)
#define RED (0)

/* RBT Properties:
 *  Every node is red or black
 *  The root is black
 *  Every leaf (NULL) is black
 *  If a node is red, both of its children are black
 *  For each node, the black height on both sides is equal
 * */

typedef struct rbt_struct *RBT;

RBT RB_Create();
void RB_Insert(RBT Tree, int data);
bool RB_Search(RBT Tree, int data);
void RB_Clear(RBT Tree);
void RB_Free(RBT Tree);
void Format_Inorder_Print(RBT Tree);
void Format_Height_Print(RBT Tree);
void Format_Black_Height_Print(RBT Tree);
void Format_Print_Nth_Highest_Num(RBT Tree, int n);


#endif //REDBLACKTREE_RBT_H
