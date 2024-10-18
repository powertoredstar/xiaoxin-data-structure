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
    //分配红黑树节点所需的内存空间
    RBNode *newNode =(RBNode*)malloc(sizeof(RBNode));
    //如果内存分配失败，则输出错误信息并终止程序
    if(!newNode){
        fprintf(stderr,"内存分配失败\n");
        exit(1);
    }
    //初始化节点的数据值
    newNode->data = data;
    //默认新节点的颜色为红色
    newNode->color = RED;
    //初始化节点的左右子节点和父节点指针为NULL
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    //返回新创建的节点
    return newNode;
}


/**
 * 进行红黑树的左旋操作。
 * 左旋操作是为了维护红黑树的性质，在插入或删除节点后进行的平衡调整操作。
 * 左旋操作会改变树的结构，但不会改变树中节点的值。
 *
 * @param root 指向红黑树根节点的指针。
 * @param x 需要进行左旋操作的节点。
 */
void leftRotate(RBNode **root,RBNode *x){
    // y为x的右子节点，左旋操作将y变为新的父节点
    RBNode *y = x->right;
    // 将y的左子节点变为x的右子节点
    x->right = y->left;
    // 如果y的左子节点不为空，更新其父节点为x
    if(y->left != NULL){
        y->left->parent = x;
    }
    // 更新y的父节点为x的父节点，即y将成为新的子树根节点
    y->parent = x->parent;
    // 如果x没有父节点，即x是整棵树的根节点，更新根节点为y
    if(x->parent == NULL){
        *root = y;
    // 如果x是其父节点的左子节点，更新该父节点的左子节点为y
    }else if(x == x->parent->left){
        x->parent->left = y;
    // 否则，x是其父节点的右子节点，更新该父节点的右子节点为y
    }else{
        x->parent->right = y;
    }
    // 将x变为y的左子节点，完成左旋操作
    y->left = x;
    x->parent = y;
}


/**
 * 执行右旋转操作，这是红黑树平衡调整的一部分
 * 右旋转旨在通过改变树的结构来维护红黑树的性质，而不改变中序遍历的顺序
 *
 * @param root 指向红黑树根节点的指针，通过引用修改根节点
 * @param y 需要进行右旋转的节点，即旋转前的子树根节点
 */
void rightRotate(RBNode **root,RBNode *y){
    // 保存y的左子节点为x
    RBNode  *x = y->left;
    // 将x的右子节点设置为y的左子节点
    y->left = x->right;
    // 如果x的右子节点不为空，更新其父节点为y
    if(x->right != NULL){
        x->right->parent = y;
    }
    // 更新x的父节点为y的父节点，即向上移动x
    x->parent = y->parent;
    // 如果y没有父节点，说明y是根节点，更新根节点为x
    if(y->parent == NULL){
        *root = x;
    }else if(y == y->parent->right){
        // 如果y是其父节点的右子节点，将y的位置让给x
        y->parent->right = x;
    }else{
        // 如果y是其父节点的左子节点，将y的位置让给x
        y->parent->left = x;
    }
    // 将y设置为x的右子节点，完成右旋转
    x->right = y;
    y->parent = x;
}


/**
 * 插入后的修复操作
 * @param root 红黑树的根节点指针
 * @param node 刚刚插入的节点
 *
 * 本函数用于在红黑树插入操作后修复树的性质，确保树的每个节点都符合红黑树的性质。
 * 主要通过改变节点的颜色和进行旋转操作来修复。
 */
void insertFixup(RBNode **root,RBNode *node){
    // 当新插入的节点不是根节点且其父节点颜色为红色时，进行修复操作
    while(node != *root && node->parent->color == RED){
        // 判断新插入的节点是父节点的左孩子还是右孩子
        if(node->parent == node->parent->left){
            // 叔父节点
            RBNode  *uncle = node->parent->parent->right;
            // 如果叔父节点存在且颜色为红色，进行颜色调整
            if(uncle && uncle->color == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }else{
                // 如果新插入的节点是父节点的右孩子，进行左旋转
                if(node == node->parent->right){
                    node = node->parent;
                    leftRotate(root,node);
                }
                // 进行颜色调整和右旋转
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root,node->parent->parent);
            }
        }else{
            // 叔父节点
            RBNode  *uncle = node->parent->parent->left;
            // 如果叔父节点存在且颜色为红色，进行颜色调整
            if(uncle && uncle->color == RED){
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }else{
                // 如果新插入的节点是父节点的左孩子，进行右旋转
                if(node == node->parent->left){
                    node = node->parent;
                    rightRotate(root,node);
                }
                // 进行颜色调整和左旋转
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root,node->parent->parent);
            }
        }
    }
    // 最后确保根节点的颜色为黑色
    (*root)->color = BLACK;
}

/**
 * 插入节点
 * @param root 指向根节点的指针
 * @param data 要插入节点的数据
 */
void insert(RBNode **root,int data){
    // 创建新节点
    RBNode *newNode = createNode(data);
    RBNode  * current = *root;
    RBNode *parent = NULL;
    // 遍历树找到新节点的位置
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
    // 插入节点后调整红黑树
    insertFixup(root,newNode);
}

/**
 * 中序遍历红黑树
 * @param root 根节点指针，用于开始遍历
 *
 * 该函数通过递归方式对红黑树进行中序遍历，并打印每个节点的数据和颜色。
 * 中序遍历的顺序是先访问左子树，然后访问根节点，最后访问右子树。
 * 这种遍历方式可以按照节点数据的顺序访问树中的所有节点。
 */
void in_order_traversal(RBNode * root){
    if(root != NULL){
        // 递归遍历左子树
        in_order_traversal(root->left);
        // 打印当前节点的数据和颜色
        printf("%d(%s) ",root->data,root->color == RED ? "RED" :"BLACK");
        // 递归遍历右子树
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