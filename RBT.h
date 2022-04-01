
#include <stdbool.h>

/* RBT Properties:
 *  Every node is red or black
 *  The root is black
 *  Every leaf (NULL) is black
 *  If a node is red, both of its children are black
 *  For each node, the black height on both sides is equal
 * */

#ifndef REDBLACKTREE_RBT_H
#define REDBLACKTREE_RBT_H

#define BLACK (1)
#define RED (0)

typedef struct node_struct *Node;
typedef struct rbt_struct *RBT;

RBT RB_Create();
void inorderPrint(RBT Tree);
void RB_Insert(RBT Tree, int data);
int secondHighestNum(RBT Tree);

#endif //REDBLACKTREE_RBT_H
