#include <stdlib.h>
#include <stdio.h>

#include "RBT.h"

typedef struct node_struct *Node;

struct node_struct {
    Node p, left, right;
    int key, size;
    bool color;
};

static Node createNode(int data){
    Node newNode;
    newNode = malloc(sizeof(*newNode));
    *newNode = (struct node_struct){NULL, NULL, NULL, data, BLACK, 1};
    return newNode;
}

static int Size(Node x){
    if(!x->left && !x->right)
        return 0;
    return x->size;
}



struct rbt_struct {
    Node root, nil;
};

static Node OS_Select(RBT Tree, Node x, int i){
    int r = Size(x->left) + 1;
    if(i == r)
        return x;
    else if (i < r)
        return OS_Select(Tree, x->left, i);
    return OS_Select(Tree, x->right, i-r);
}

static void LeftRotate(RBT Tree, Node x){
    Node y = x->right;
    x->right = y->left;
    if(y->left != Tree->nil)
        y->left->p = x;
    y->p = x->p;
    if(x->p == Tree->nil)
        Tree->root = y;
    else {
        if(x == x->p->left)
            x->p->left = y;
        else
            x->p->right = y;
    }
    y->size = Size(x);
    x->size = Size(x->left) + Size(x->right) + 1;
    y->left = x;
    x->p = y;
}

static void RightRotate(RBT Tree, Node x){
    Node y = x->left;
    x->left = y->right;
    if(y->right != Tree->nil)
        y->right->p = x;
    y->p = x->p;
    if(x->p == Tree->nil)
        Tree->root = y;
    else {
        if(x == x->p->right)
            x->p->right = y;
        else
            x->p->left = y;
    }
    y->size = Size(x);
    x->size = Size(x->left) + Size(x->right) + 1;
    y->right = x;
    x->p = y;
}

static void RB_Insert_Fixup(RBT Tree, Node z){
    Node y;
    while(z->p->color == RED){
        if(z->p == z->p->p->left){
            y = z->p->p->right;
            if(y->color == RED){
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    LeftRotate(Tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                RightRotate(Tree, z->p->p);
            }
        } else {
            y = z->p->p->left;
            if(y->color == RED){
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) {
                    z = z->p;
                    RightRotate(Tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                LeftRotate(Tree, z->p->p);
            }
        }
    }
    Tree->root->color = BLACK;
}

static bool internal_RB_Search(RBT Tree, Node x, int data){
    if(x == Tree->nil)
        return false;
    if(x->key == data)
        return true;
    if(data > x->key)
        return internal_RB_Search(Tree, x->right, data);
    return internal_RB_Search(Tree, x->left, data);
}

static void internalInorderPrint(RBT Tree, Node head){
    if(head == Tree->nil)
        return;
    internalInorderPrint(Tree, head->left);
    printf("%d-", head->key);
    printf(head->color == BLACK ? "B; " : "R; ");
    internalInorderPrint(Tree, head->right);
}

static int internalGetHeight(RBT Tree, Node x){
    int lh, rh;
    if(x == Tree->nil)
        return 0;
    if(x->left == Tree->nil && x->right == Tree->nil)
        return 1;
    lh = internalGetHeight(Tree, x->left);
    rh = internalGetHeight(Tree, x->right);
    return 1 + ((lh > rh) ? lh : rh);
}

static int internalGetBlackHeight(RBT Tree, Node x){
    int lh, rh, sum = 0;

    if(x == Tree->nil)
        return 1;

    lh = internalGetBlackHeight(Tree, x->left);
    rh = internalGetBlackHeight(Tree, x->right);

    if(x->color == BLACK)
        sum = 1;

    if(lh == -1 || rh == -1 || lh != rh)
        return -1;

    return lh + sum;
}

static void internalClearRBT(RBT Tree, Node root){
    if(root == Tree->nil)
        return;
    internalClearRBT(Tree, root->left);
    internalClearRBT(Tree, root->right);
    free(root);
}



RBT RB_Create(){
    RBT Tree;
    Tree = malloc(sizeof(*Tree));
    Tree->root = Tree->nil = createNode(0);
    Tree->nil->size = 0;
    return Tree;
}

void RB_Insert(RBT Tree, int data){
    Node y = Tree->nil;
    Node x = Tree->root;
    Node z = createNode(data);
    while(x != Tree->nil){
        y = x;
        x->size++;
        if(z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->p = y;
    if(y == Tree->nil)
        Tree->root = z;
    else {
        if(z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
    z->left = Tree->nil;
    z->right = Tree->nil;
    z->color = RED;
    RB_Insert_Fixup(Tree, z);
}

bool RB_Search(RBT Tree, int data){
    return internal_RB_Search(Tree, Tree->root, data);
}

void RB_Clear(RBT Tree){
    internalClearRBT(Tree, Tree->root);
}



void formatInorderPrint(RBT Tree){
    printf("In-order traversal of the tree:");
    if(Tree->root != Tree->nil)
        printf("\n");
    internalInorderPrint(Tree, Tree->root);
    printf("\n\n");
}

void formatHeightPrint(RBT Tree){
    int height = internalGetHeight(Tree, Tree->root);
    printf("The height of the red and black tree is %d.\n\n", height);
}

void formatBlackHeightPrint(RBT Tree){
    int black_height = internalGetBlackHeight(Tree, Tree->root);
    if(black_height != -1)
        printf("The black height of the red and black tree is %d.\n\n", black_height);
}

void formatPrintNthHighestNum(RBT Tree, int n){
    int i = Size(Tree->root) - n + 1;
    printf("The second largest element of the tree is ");
    if(i > 0) {
        Node x = OS_Select(Tree, Tree->root, i);
        printf("%d", x->key);
    } else {
        printf("undefined");
    }
    printf(".\n\n");
}