//一个基本的二叉树的实现，包括节点的定义、插入、遍历等操作。
// Created by 1 on 2024/10/15.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//定义二叉树的结构
typedef struct TreeNode{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
//定义树节点的栈结构
typedef struct Stack_TreeNode{
    TreeNode** frames;
    int top;//栈顶指针
    int init_size;//初始容量
    int increment_size;//扩容的增量
    int max_size;//最大容量
} Stack_TreeNode;
//声明函数
void printf_array(int* array,int array_size);
int* generate_random_array(int lower_bound, int upper_bound,int array_size);
TreeNode* create_node(int data);
TreeNode* insert_node(TreeNode* root,TreeNode* newNode);
void free_binary_tree_memory(TreeNode* root);
bool is_binary_tree_empty(TreeNode* root);
TreeNode* create_binary_tree(int* array,int array_length);
TreeNode* merge_two_binary_tree(TreeNode* left_tree,TreeNode* right_tree);
TreeNode* deleteNode(TreeNode* root,int value);
void preOrder_traversal_recursion(TreeNode* root);
void inOrder_traversal_recursion(TreeNode* root);
void postOrder_traversal_recursion(TreeNode* root);
void binary_tree_base_opertion_test_1();
Stack_TreeNode* init_treeNode_stack(int init_size,int increment_size);
int is_empty_treeNode_stack(Stack_TreeNode* stack);
int is_full_treeNode_stack(Stack_TreeNode* stack);
TreeNode* pop_treeNode_stack(Stack_TreeNode* stack);
TreeNode* peep_treeNode_stack(Stack_TreeNode* stack);
int push_treeNode_stack(Stack_TreeNode* stack,TreeNode* node);
void preOrder_traversal(TreeNode* root);
void inOrder_traversal(TreeNode* root);
void postOrder_traversal(TreeNode* root);
void destroy_treeNode_stack(Stack_TreeNode* stack);

int main(){
    binary_tree_base_opertion_test_1();

    return 0;
}
/**
 * 测试了
void preOrder_traversal_recursion(TreeNode* root);
void inOrder_traversal_recursion(TreeNode* root);
void postOrder_traversal_recursion(TreeNode* root);
TreeNode* create_node(int data);
TreeNode* insert_node(TreeNode* root,TreeNode* newNode);
 void printf_array(int* array,int array_size);
int* generate_random_array(int lower_bound, int upper_bound,int array_size);
 void free_binary_tree_memory(TreeNode* root);
 TreeNode* create_binary_tree(int* array,int array_length);
 TreeNode* merge_two_binary_tree(TreeNode* left_tree,TreeNode* right_tree);
 */
void binary_tree_base_opertion_test_1() {//生成一个随机数组
    int array_size = 15;
    int* array = generate_random_array(0,1000,array_size);
    printf_array(array,array_size);

    //将数组构造成一颗二叉树
    TreeNode* root = create_binary_tree(array,array_size);

//    //前序遍历
    printf("preOrder_traversal_recursion\n ");
    preOrder_traversal_recursion(root);
    printf("\n");

    //中序遍历
    printf("inOrder_traversal_recursion\n ");
    inOrder_traversal_recursion(root);
    printf("\n");

//    //后序遍历
    printf("postOrder_traversal_recursion\n ");
    postOrder_traversal_recursion(root);
    printf("\n");

    printf("is_binary_tree_empty %d\n",is_binary_tree_empty(root));

    //删除节点
    root = deleteNode(root,array[array_size/2]);

    printf("deleteNode %d\n",array[array_size/2]);

//    //前序遍历
    printf("preOrder_traversal\n ");
    preOrder_traversal(root);
    printf("\n");

    //中序遍历
    printf("inOrder_traversal\n ");
    inOrder_traversal(root);
    printf("\n");

    //后序遍历
    printf("postOrder_traversal\n ");
    postOrder_traversal(root);
    printf("\n");

    free_binary_tree_memory(root);
}

/**
 * 生成一个随机整数数组
 *
 * @param upper_bound 随机数的上界（不包含）
 * @param lower_bound 随机数的下界（包含）
 * @param array_size 数组的大小
 *
 * @return 返回一个指向生成的随机整数数组的指针
 *
 * 此函数用于生成一个指定大小的数组，数组中的元素为指定范围内的随机整数
 * 使用当前时间作为随机数种子，以确保每次生成的随机数序列不同
 * 动态分配数组内存，注意在使用完毕后释放内存以避免内存泄漏
 */
int* generate_random_array(int lower_bound, int upper_bound,int array_size) {
    // 使用当前时间作为随机数种子
    srand((unsigned)time(NULL));

    // 动态分配数组内存
    int* array = (int*)malloc(sizeof(int) * array_size);

    // 遍历数组，生成随机数
    for (int i = 0; i < array_size; i++) {
        // 生成指定范围内的随机数
        array[i] = rand() % (upper_bound - lower_bound) + lower_bound;
    }

    // 返回指向数组的指针
    return array;
}
/**
 * 打印数组
 * @param array
 * @param array_size
 */
void printf_array(int* array,int array_size){
    printf("array_traversal\n");
    for(int i = 0;i < array_size;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}

/**
 * 创建一个新节点
 * @param data 节点的数据
 * @return
 */
TreeNode* create_node(int data){
    //分配内存
    TreeNode *newNode = (TreeNode*) malloc(sizeof(TreeNode));

    if(newNode == NULL){
        printf("memory allocation failed \n");
    }
    //初始化
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    //返回结果
    return newNode;
}
/**
 * 插入一个新节点
 * @param root 根节点
 * @param newNode 新节点
 * @return
 */
TreeNode* insert_node(TreeNode* root,TreeNode* newNode){
    if(root == NULL){
        return newNode;
    }
    if(root->left == NULL){
        root->left = (TreeNode*) malloc(sizeof(TreeNode));
        root->left = newNode;
        return newNode;
    }
    if(root->right == NULL){
        root->right = (TreeNode*) malloc(sizeof(TreeNode));
        root->right = newNode;
        return newNode;
    }
    if(newNode->data % 2 == 0){
        return insert_node(root->left,newNode);
    }
    return insert_node(root->right,newNode);

}

/**
 * 合并两颗子树,并从两颗子树中选取一个节点来充当新的根节点
 * 普通二叉树无固定规则
 * @param left_tree 左子树的根节点指针
 * @param right_tree 右子树的根节点指针
 * @return 返回合并后的二叉树的根节点指针
 */
TreeNode* merge_two_binary_tree(TreeNode* left_tree,TreeNode* right_tree){
    // 如果左子树为空，则直接返回右子树
    if(left_tree == NULL){
        return right_tree;
    }
    // 如果右子树为空，则直接返回左子树
    if(right_tree == NULL){
        return left_tree;
    }
    // 选出根节点
    TreeNode *root;
    // 比较左右子树根节点的值，选择较大的作为新根节点
    if(left_tree->data > right_tree->data){
        root = left_tree;
        // 将较小值的子树插入到较大值的子树中
        insert_node(root,right_tree);
    }else{
        root = right_tree;
        // 将较小值的子树插入到较大值的子树中
        insert_node(root,left_tree);
    }
    // 返回合并后的树的根节点
    return root;
}

/**
 * 构建一颗二叉树
 * @param array
 * @return
 */
TreeNode* create_binary_tree(int* array,int array_length){

    //如果数据为空，返回空指针
    if(array_length == 0){
        return NULL;
    }
    //将第一个元素作为根节点
    TreeNode *root = create_node(array[0]);

    //定义一个指针，用于结束循环
    int p = 1;
    //循环插入剩余元素
    while(p < array_length){
        TreeNode* new_node = insert_node(root,create_node(*(array+p)));
        p++;
    }
    return root;
}
/**
 * 从二叉树中删除所有值为value的节点。
 * @param root 二叉树的根节点指针。
 * @param value 需要删除的节点值。
 * @return 删除节点后二叉树的根节点指针。
 */
TreeNode* deleteNode(TreeNode* root,int value){
    // 防止无限递归
    if(root == NULL){
        return NULL;
    }
    // 递归删除左子树和右子树中匹配的节点
    root->left = deleteNode(root->left,value);
    root->right = deleteNode(root->right,value);
    // 当找到需要删除的节点时，合并其左右子树，并释放该节点
    if(root->data == value){
        TreeNode *temp = root;
        root = merge_two_binary_tree(root->left,root->right);
        free(temp);
    }

    // 返回更新后的根节点
    return root;
}

/**
 * 初始化一个存储树节点的栈
 *
 * @param init_size 栈的初始大小
 * @param increment_size 栈的增量大小，即每次栈满时栈大小的增加量
 *
 * @return 返回指向初始化后的栈的指针如果初始化失败，返回NULL
 *
 * 此函数通过动态内存分配创建一个栈，用于存储树节点指针
 * 它设置了栈的初始大小和增量大小，并将栈顶指针设置为-1，表示栈为空
 */
Stack_TreeNode* init_treeNode_stack(int init_size,int increment_size){
    Stack_TreeNode* stack = (Stack_TreeNode*)malloc(sizeof(Stack_TreeNode));
    // 为栈分配初始大小的内存空间
    stack->frames = (TreeNode**)malloc(sizeof(TreeNode*) * init_size);
    // 设置栈的初始大小
    stack->init_size = init_size;
    stack->max_size = init_size;
    // 设置栈的增量大小
    stack->increment_size = increment_size;
    // 将栈顶指针设置为-1，表示栈为空
    stack->top = -1;
    //返回初始化后的栈指针
    return stack;
}

/**
 * 检查栈是否为空
 *
 * 当栈的top索引不为-1时，表示栈中存在元素，函数返回0（假）
 * 如果栈的初始化大小与最大大小不相等，表明栈尚未分配到初始大小的空间
 * 此时，将栈的空间重新分配为其初始化大小，并更新最大大小
 * 最后，函数返回1（真），表示栈为空
 *
 * @param stack 指向栈的指针
 * @return 如果栈为空返回1，否则返回0
 */
int is_empty_treeNode_stack(Stack_TreeNode* stack){
    // 检查栈是否为空
    if(stack->top != -1){
        return 0;
    }
    // 如果栈的初始化大小与当前最大大小不等，重新分配空间
    if(stack->init_size != stack->max_size){
        realloc(stack->frames,sizeof(TreeNode*)*stack->init_size);
        stack->max_size = stack->init_size;
    }
    // 栈为空，返回1
    return 1;
}

/**
 * 判断栈是否已满
 *
 * @param stack 栈的指针
 * @return 如果栈已满返回1，否则返回0
 *
 * 此函数通过比较栈的最大尺寸和当前栈顶的位置来判断栈是否已满。
 * 如果栈的最大尺寸等于栈顶位置加一，则表明栈已满，因为栈顶位置从0开始计数。
 */
int is_full_treeNode_stack(Stack_TreeNode* stack){
    // 检查栈是否已满
    if(stack->max_size == (stack->top+1)){
        return 1; // 栈已满
    }
    return 0; // 栈未满
}

/**
 * 从栈中弹出一个树节点
 *
 * @param stack 指向栈的指针
 * @return 返回弹出的树节点指针，如果栈为空则返回NULL
 *
 * 此函数的作用是从给定的栈中弹出一个树节点如果栈为空，则函数返回NULL，
 * 表示没有树节点可以弹出如果栈不为空，函数将返回栈顶的树节点，并将栈顶指针减1，
 * 以实现弹出操作
 */
TreeNode* pop_treeNode_stack(Stack_TreeNode* stack){
    //判断栈是否为空
    if(is_empty_treeNode_stack(stack)){
        return NULL;
    }
    //返回栈顶的树节点，并将栈顶指针减1
    return stack->frames[stack->top--];
}

/**
 * 函数名: peep_treeNode_stack
 * 功能描述: 查看栈顶的树节点而不移除它
 * 参数:
 *   - stack: 树节点栈的指针，用于访问栈中的元素
 * 返回值:
 *   - 如果栈为空，则返回NULL
 *   - 如果栈不为空，则返回栈顶的树节点
 */
TreeNode* peep_treeNode_stack(Stack_TreeNode* stack){
    //判断栈是否为空
    if(is_empty_treeNode_stack(stack)){
        return NULL;
    }
    //返回栈顶的树节点，并将栈顶指针减1
    return stack->frames[stack->top];
}

/**
 * 将节点压入栈中
 *
 * 当栈满时，会尝试扩大栈的空间如果扩大失败，则返回0
 *
 * @param stack 栈的指针
 * @param node 要压入栈的节点指针
 * @return 成功压入栈时返回1，否则返回0
 */
int push_treeNode_stack(Stack_TreeNode* stack,TreeNode* node){
    //判断栈是否已满
    if(is_full_treeNode_stack(stack)){
        //扩大栈空间
        TreeNode** new_frames = (TreeNode**) malloc(sizeof(TreeNode*) * stack->max_size+stack->increment_size);
        if(new_frames == NULL){
            printf("expand the stack capacity failed");
            return 0;
        }
        for(int i = 0;i < stack->max_size;i++){
            new_frames[i] = stack->frames[i];
        }
        stack->frames = new_frames;
        stack->max_size += stack->increment_size;
    }
    stack->frames[++stack->top] = node;
    return 1;
}


/**
 * 销毁并释放树栈节点的资源
 *
 * @param stack 指向树栈节点的指针
 *
 * 该函数首先释放树栈节点中的frames资源，然后释放栈树节点本身
 * 调用该函数后，传入的树栈节点指针不应再被使用，因为它所指向的内存已被释放
 */
void destroy_treeNode_stack(Stack_TreeNode* stack){
    // 释放栈树节点中的frames资源
    free(stack->frames);
    // 释放栈树节点本身
    free(stack);
}

//前序遍历(递归实现)
void preOrder_traversal_recursion(TreeNode* root){
    if(root == NULL){
        return;
    }
    //根
    printf("%d ",root->data);
    //左
    preOrder_traversal_recursion(root->left);
    //右
    preOrder_traversal_recursion(root->right);
}
/**
 * 前序遍历(非递归实现)
 * @param root 根节点指针
 */
void preOrder_traversal(TreeNode* root){
    //初始化栈
    Stack_TreeNode* stack = init_treeNode_stack(10,10);
    //若根节点为空，则直接返回
    if(root == NULL){
        return;
    }

    //根节点入栈
    push_treeNode_stack(stack,root);

    //循环遍历栈
    while(!is_empty_treeNode_stack(stack)){
        //栈顶节点
        TreeNode* node = peep_treeNode_stack(stack);
        if(node != NULL){
            //栈顶节点出栈
            node = pop_treeNode_stack(stack);
            //右
            if(node->right != NULL){
                push_treeNode_stack(stack,node->right);
            }
            //左
            if(node->left != NULL){
                push_treeNode_stack(stack,node->left);
            }
            //根
            push_treeNode_stack(stack,node);
            push_treeNode_stack(stack,NULL);
        }else{
            //弹出栈顶节点(空节点)
            pop_treeNode_stack(stack);

            //弹出待处理节点
            node = pop_treeNode_stack(stack);

            //处理逻辑
            printf("%d ",node->data);
        }
    }
    destroy_treeNode_stack(stack);
}

//中序遍历(递归实现)
void inOrder_traversal_recursion(TreeNode* root){
    if(root == NULL){
        return;
    }
    //左
    inOrder_traversal_recursion(root->left);
    //根
    printf("%d ",root->data);
    //右
    inOrder_traversal_recursion(root->right);
}

/**
 * 中序遍历(非递归实现)
 * @param root 树的根节点
 */
void inOrder_traversal(TreeNode* root){
    //初始化栈
    Stack_TreeNode* stack = init_treeNode_stack(20,10);
    //若根节点为空，则直接返回
    if(root == NULL){
        return;
    }
    //根节点入栈
    push_treeNode_stack(stack,root);
    //循环遍历栈
    while(!is_empty_treeNode_stack(stack)){
        //栈顶节点
        TreeNode* node = pop_treeNode_stack(stack);

        if(node != NULL){

            //按照"右-根-左"的顺序将节点入栈，以实现中序遍历(左-根-右)
            //右
            if(node->right != NULL){
                push_treeNode_stack(stack,node->right);
            }
            //根
            push_treeNode_stack(stack,node);
            push_treeNode_stack(stack,NULL);

            //左
            if(node->left != NULL){
                push_treeNode_stack(stack,node->left);
            }

        }else{
            //弹出待处理节点
            node = pop_treeNode_stack(stack);

            //处理逻辑(打印节点数据)
            printf("%d ",node->data);
        }
    }
    //释放栈内存
    destroy_treeNode_stack(stack);
}

//后序遍历(递归实现)
void postOrder_traversal_recursion(TreeNode* root){
    if(root == NULL){
        return;
    }
    //左
    postOrder_traversal_recursion(root->left);
    //右
    postOrder_traversal_recursion(root->right);
    //根
    printf("%d ",root->data);
}

/**
 * 后序遍历(非递归实现)
 * @param root 根节点指针
 */
void postOrder_traversal(TreeNode* root){
    //初始化栈
    Stack_TreeNode* stack = init_treeNode_stack(10,10);
    //若根节点为空，则直接返回
    if(root == NULL){
        return;
    }
    //根节点入栈
    push_treeNode_stack(stack,root);
    //循环遍历栈
    while(!is_empty_treeNode_stack(stack)){
        //栈顶节点
        TreeNode* node = peep_treeNode_stack(stack);
        if(node != NULL){
            //栈顶节点出栈
            node = pop_treeNode_stack(stack);

            //根
            push_treeNode_stack(stack,node);
            push_treeNode_stack(stack,NULL);

            //右
            if(node->right != NULL){
                push_treeNode_stack(stack,node->right);
            }

            //左
            if(node->left != NULL){
                push_treeNode_stack(stack,node->left);
            }

        }else{
            //弹出栈顶节点(空节点)
            pop_treeNode_stack(stack);

            //弹出待处理节点
            node = pop_treeNode_stack(stack);

            //处理逻辑
            printf("%d ",node->data);
        }
    }
    destroy_treeNode_stack(stack);
}

//层序遍历
void level_traversal(TreeNode* root){

}
//查找某个节点
TreeNode* search_node(TreeNode* root,int value){
    return NULL;
}
//查找二叉树中的最大值
TreeNode* search_max_node(TreeNode* root){
    return NULL;
}
//查找二叉树中的最小值
TreeNode* search_min_node(TreeNode* root){
    return NULL;
}
//获取二叉树的高度
int  get_binary_tree_height(TreeNode* root){
    return 0;
}
//计算目标节点的深度
int get_binary_tree_depth(TreeNode* root,TreeNode* target){
    return 0;
}
//计算节点数
int get_binary_tree_node_num(TreeNode* root){
    return 0;
}
/**
 * 判断二叉树是否为空
 * @param root
 * @return
 */
bool is_binary_tree_empty(TreeNode* root){
    if(root == NULL){
        return true;
    }
    return false;
}
//复制二叉树
TreeNode* copy_binary_tree(TreeNode* root){
    return NULL;
}
/**
 * 释放二叉树内存(后序遍历)
 * @param root
 */
void free_binary_tree_memory(TreeNode* root){
    if(root == NULL){
        return;
    }
    //左
    free_binary_tree_memory(root->left);
    //右
    free_binary_tree_memory(root->right);
    //根
    free(root);
}
//将一个二叉树转换成平衡二叉树
TreeNode* convert_binary_tree_to_balanced_binary_tree(TreeNode* root){
    return NULL;
}
//左旋二叉树
TreeNode* left_rotate_binary_tree(TreeNode* root){
    return NULL;
}
//右旋二叉树
TreeNode* right_rotate_binary_tree(TreeNode* root){
    return NULL;
}
//路径查找

//祖先节点查找

//子树查找

//判断二叉树是否镜像对称

//路径和

//最大路径和

//最低公共祖先

//序列化

//反序列化

//拓扑排序

//子树平均值(计算二叉树中每个节点的子树的平均值)

//子树中位数

//子树众数

//子树唯一值（判断二叉树中每个节点的子树是否只包含唯一的值）

//子树是否平衡

//路径计数：
//计算从根节点到叶子节点的所有路径的数量。


//路径长度：
//计算从根节点到叶子节点的所有路径的长度，并返回最长路径或最短路径。


//路径和统计：
//统计从根节点到叶子节点的所有路径中，路径上节点值的和满足某种条件的路径数量。

//路径节点统计：
//统计从根节点到叶子节点的所有路径中，包含特定值的路径数量。

//子树节点统计：
//统计二叉树中每个节点的子树中包含特定值的节点数量。


//子树节点类型统计：
//统计二叉树中每个节点的子树中不同类型节点的数量，例如叶子节点、内部节点等。

//子树节点值范围统计：
//统计二叉树中每个节点的子树中节点值在特定范围内的节点数量。

//子树节点值分布：
//统计二叉树中每个节点的子树中节点值的分布情况，例如值的频率分布。

//子树节点值排序：
//获取二叉树中每个节点的子树中节点值的排序结果。

//子树节点值排列：
//获取二叉树中每个节点的子树中节点值的所有排列组合。

//子树节点值组合：
//获取二叉树中每个节点的子树中节点值的所有组合。

//子树节点值子集：
//获取二叉树中每个节点的子树中节点值的所有子集。

//子树节点值幂集：
//获取二叉树中每个节点的子树中节点值的幂集（所有可能的子集）。

//子树节点值和的子集：
//查找二叉树中每个节点的子树中节点值的子集，使得子集的和满足某种条件。

//子树节点值积的子集：
//查找二叉树中每个节点的子树中节点值的子集，使得子集的积满足某种条件。

//子树节点值的最大连续子数组：
//查找二叉树中每个节点的子树中节点值的最大连续子数组。

//子树节点值的最长递增子序列：
//查找二叉树中每个节点的子树中节点值的最长递增子序列。

//子树节点值的最长递减子序列：
//查找二叉树中每个节点的子树中节点值的最长递减子序列。

//子树节点值的最长回文子序列：
//查找二叉树中每个节点的子树中节点值的最长回文子序列。

//子树节点值的最长公共子序列：
//查找二叉树中每个节点的子树中节点值与其他序列的最长公共子序列。

//子树节点值的最长公共子串：
//查找二叉树中每个节点的子树中节点值与其他序列的最长公共子串。

//子树节点值的最短公共超序列：
//查找二叉树中每个节点的子树中节点值与其他序列的最短公共超序列。

//子树节点值的编辑距离：
//计算二叉树中每个节点的子树中节点值与其他序列的编辑距离。

//子树节点值的哈希值：
//计算二叉树中每个节点的子树中节点值的哈希值。

//子树节点值的熵：
//计算二叉树中每个节点的子树中节点值的熵，用于衡量值的分布均匀性。

//子树节点值的方差：
//计算二叉树中每个节点的子树中节点值的方差，用于衡量值的离散程度。

//子树节点值的标准差：
//计算二叉树中每个节点的子树中节点值的标准差，用于衡量值的离散程度。

//子树节点值的中位数绝对偏差：
//计算二叉树中每个节点的子树中节点值的中位数绝对偏差，用于衡量值的离散程度。

//子树节点值的四分位数：
//计算二叉树中每个节点的子树中节点值的四分位数，用于描述值的分布情况。

//子树节点值的百分位数：
//计算二叉树中每个节点的子树中节点值的百分位数，用于描述值的分布情况。

