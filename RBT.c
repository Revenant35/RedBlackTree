#include <stdlib.h>
#include <stdio.h>

#include "RBT.h"

struct node_struct {
    Node p, left, right;
    int key, size;
    bool color;
};

struct rbt_struct {
    Node root, nil;
};

static Node createNode(int data){
    Node newNode;
    newNode = malloc(sizeof(*newNode));
    newNode->p = newNode->left = newNode->right = NULL;
    newNode->color = BLACK;
    newNode->key = data;
    newNode->size = 1;
    return newNode;
}

static int size(Node x){
    if(!x || (!x->left && !x->right))
        return 0;
    return x->size;
}

static Node OS_Select(RBT Tree, Node x, int i){
    int r = size(x->left) + 1;
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
    y->size = size(x);
    x->size = size(x->left) + size(x->right) + 1;
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
    y->size = size(x);
    x->size = size(x->left) + size(x->right) + 1;
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

static void internalInorderPrint(RBT Tree, Node head){
    if(head == Tree->nil)
        return;
    internalInorderPrint(Tree, head->left);
    printf("%d-", head->key);
    printf(head->color == BLACK ? "B; " : "R; ");
    internalInorderPrint(Tree, head->right);
}




void inorderPrint(RBT Tree){
    internalInorderPrint(Tree, Tree->root);
    printf("\n");
}
int secondHighestNum(RBT Tree){
    int i = size(Tree->root) - 1;
    Node x = OS_Select(Tree, Tree->root, i);
    return x->key;
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