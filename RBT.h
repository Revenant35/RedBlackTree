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

RBT RB_Create(); // O(1) Time Complexity
void RB_Insert(RBT Tree, int data); // O(lg(n)) Time Complexity
bool RB_Search(RBT Tree, int data); // O(lg(n)) Time Complexity
void formatInorderPrint(RBT Tree); // O(n) Time Complexity
void formatPrintNthHighestNum(RBT Tree, int n); // O(lg(n)) Time Complexity
void formatHeightPrint(RBT Tree); // O(n) Time Complexity
void formatBlackHeightPrint(RBT Tree); // O(n) Time Complexity
void RB_Clear(RBT Tree); // O(n) Time Complexity

#endif //REDBLACKTREE_RBT_H
