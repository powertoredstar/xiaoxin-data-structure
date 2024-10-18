//
// Created by 1 on 2024/10/15.
//
#include <stdio.h>
#include <stdlib.h>
//定义节点的颜色
typedef enum {
    RED,
    BLACK
}Color;
//定义红黑树节点结构
typedef struct RBNode{
    int data;
    Color color;
    struct RBNode *left,*right,*parent;
}RBNode;
//创建一个新的红黑树节点
RBNode* createNode(int data){
    RBNode *newNode =(RBNode*)malloc(sizeof(RBNode));
    if(!newNode){
        fprintf(stderr,"内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}
//左旋操作
void leftRotate(RBNode **root,RBNode *x){
    RBNode *y = x->right;
    x->right = y->left;
    if(y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        *root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}
//右旋操作
void rightRotate(RBNode **root,RBNode *y){
    RBNode  *x = y->left;
    y->left = x->right;
    if(x->right != NULL){
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL){
        *root = x;
    }else if(y == y->parent->right){
        y->parent->right = x;
    }else{
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}
//插入后的修复操作
void insertFixup(RBNode **root,RBNode *node){
    while(node != *root && node->parent->color == RED){
        if(node->parent == node->parent->left){
            RBNode  *uncle = node->parent->parent->right;
            if(uncle && uncle->color == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }else{
                if(node == node->parent->right){
                    node = node->parent;
                    leftRotate(root,node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root,node->parent->parent);
            }
        }else{
            RBNode  *uncle = node->parent->parent->left;
            if(uncle && uncle->color == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }else{
                if(node == node->parent->left){
                    node = node->parent;
                    rightRotate(root,node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root,node->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}
//插入节点
void insert(RBNode **root,int data){
    RBNode *newNode = createNode(data);
    RBNode  * current = *root;
    RBNode *parent = NULL;
    while(current != NULL){
        parent = current;
        if(newNode->data < current->data){
            current = current->left;
        }else{
            current = current->right;
        }
    }
    newNode->parent = parent;
    if(parent == NULL){
        *root = newNode;
    }else if(newNode->data < parent->data){
        parent->left = newNode;
    }else{
        parent->right = newNode;
    }
    insertFixup(root,newNode);
}
//中序遍历
void in_order_traversal(RBNode * root){
    if(root != NULL){
        in_order_traversal(root->left);
        printf("%d(%s) ",root->data,root->color == RED ? "RED" :"BLACK");
        in_order_traversal(root->right);
    }
}
int main(){
    RBNode  *root = NULL;

    //插入一些节点
    insert(&root,10);
    insert(&root,20);
    insert(&root,30);
    insert(&root,15);
    insert(&root,25);

    //中序遍历
    in_order_traversal(root);
    printf("\n");

    return 0;
}