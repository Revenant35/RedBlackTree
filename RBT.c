#include <stdlib.h>
#include <stdio.h>

#include "RBT.h"

#define Safe_Free(address) Internal_Safe_Free((void **) &(address))

typedef struct node_struct *Node;

struct node_struct {
    Node p, left, right;
    int key, size;
    bool color;
};

struct rbt_struct {
    Node root, nil;
};

static void Internal_Safe_Free(void ** address){
    if(address != NULL && *address != NULL){
        free(*address);
        *address = NULL;
    }
}

static Node Create_Node(int data){
    Node newNode;
    newNode = malloc(sizeof(*newNode));
    *newNode = (struct node_struct){NULL, NULL, NULL, data, BLACK, 1};
    return newNode;
}


static Node OS_Select(RBT Tree, Node x, int i){
    int r = x->left->size + 1;
    if(i == r)
        return x;
    else if (i < r)
        return OS_Select(Tree, x->left, i);
    return OS_Select(Tree, x->right, i-r);
}

static void Left_Rotate(RBT Tree, Node x){
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    y->left = x;
    x->p = y;
}

static void Right_Rotate(RBT Tree, Node x){
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
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
                    Left_Rotate(Tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                Right_Rotate(Tree, z->p->p);
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
                    Right_Rotate(Tree, z);
                }
                z->p->color = BLACK;
                z->p->p->color = RED;
                Left_Rotate(Tree, z->p->p);
            }
        }
    }
    Tree->root->color = BLACK;
}

static bool Internal_RB_Search(RBT Tree, Node x, int data){
    if(x == Tree->nil)
        return false;
    if(x->key == data)
        return true;
    if(data > x->key)
        return Internal_RB_Search(Tree, x->right, data);
    return Internal_RB_Search(Tree, x->left, data);
}

static void Internal_Inorder_Print(RBT Tree, Node head){
    if(head == Tree->nil)
        return;
    Internal_Inorder_Print(Tree, head->left);
    printf("%d-", head->key);
    printf(head->color == BLACK ? "B; " : "R; ");
    Internal_Inorder_Print(Tree, head->right);
}

static int Internal_Get_Height(RBT Tree, Node x){
    int lh, rh;
    if(x == Tree->nil)
        return 0;
    if(x->left == Tree->nil && x->right == Tree->nil)
        return 1;
    lh = Internal_Get_Height(Tree, x->left);
    rh = Internal_Get_Height(Tree, x->right);
    return 1 + ((lh > rh) ? lh : rh);
}

static int Internal_Get_Black_Height(RBT Tree, Node x){
    int lh, rh, sum = 0;

    if(x == Tree->nil)
        return 0;

    lh = Internal_Get_Black_Height(Tree, x->left);
    rh = Internal_Get_Black_Height(Tree, x->right);

    if(x->color == BLACK)
        sum = 1;

    if(lh == -1 || rh == -1 || lh != rh)
        return -1;

    return lh + sum;
}

static void Internal_Clear_RBT(RBT Tree, Node root){
    if(root == Tree->nil)
        return;
    Internal_Clear_RBT(Tree, root->left);
    Internal_Clear_RBT(Tree, root->right);
    free(root);
}



RBT RB_Create(){
    RBT Tree;
    Tree = malloc(sizeof(*Tree));
    Tree->root = Tree->nil = Create_Node(0);
    Tree->nil->size = 0;
    return Tree;
}

void RB_Insert(RBT Tree, int data){
    Node y = Tree->nil;
    Node x = Tree->root;
    Node z = Create_Node(data);
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
    return Internal_RB_Search(Tree, Tree->root, data);
}

void RB_Clear(RBT Tree){
    Internal_Clear_RBT(Tree, Tree->root);
    Tree->root = Tree->nil;
}

void RB_Free(RBT Tree){
    Internal_Clear_RBT(Tree, Tree->root);
    Safe_Free(Tree->nil);
    Safe_Free(Tree);
}



void Format_Inorder_Print(RBT Tree){
    printf("In-order traversal of the tree:");
    if(Tree->root != Tree->nil)
        printf("\n");
    Internal_Inorder_Print(Tree, Tree->root);
    printf("\n\n");
}

void Format_Height_Print(RBT Tree){
    int height = Internal_Get_Height(Tree, Tree->root);
    printf("The height of the red and black tree is %d.\n\n", height);
}

void Format_Black_Height_Print(RBT Tree){
    int black_height = Internal_Get_Black_Height(Tree, Tree->root);
    if(black_height != -1)
        printf("The black height of the red and black tree is %d.\n\n", black_height);
}

void Format_Print_Nth_Highest_Num(RBT Tree, int n){
    char *ordinal;

    switch(n % 10){
        case 1:
            ordinal = "st";
            break;
        case 2:
            ordinal = "nd";
            break;
        case 3:
            ordinal = "rd";
            break;
        default:
            ordinal = "th";
            break;
    }

    int i = Tree->root->size - n + 1;

    printf("The %d%s largest element of the tree is ", n, ordinal);

    if(i > 0) {
        Node x = OS_Select(Tree, Tree->root, i);
        printf("%d", x->key);
    } else {
        printf("undefined");
    }

    printf(".\n");
}