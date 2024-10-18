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
typedef struct TreeNode_Stack{
    TreeNode** frames;//栈帧空间
    int top;//栈顶指针
    int init_size;//初始容量
    int increment_size;//扩容的增量
    int max_size;//当前的最大容量
} TreeNode_Stack;
//定义树节点的队列结构
typedef struct TreeNode_Queue{
    TreeNode** data_items;//队列数据项集合
    int front;//队头指针
    int tail;//队尾指针
    int queue_size;//队列当前容量
    int init_size;//初始容量
    int increment_size;//扩容的增量
    int max_size;//当前的最大容量
} TreeNode_Queue;
//声明函数
void printf_array(int* array,int array_size);
int* generate_random_array(int lower_bound, int upper_bound,int array_size);
TreeNode* create_node(int data);
TreeNode* insert_node(TreeNode* root,TreeNode* newNode);
void free_binary_tree_memory(TreeNode* root);
int is_binary_tree_empty(TreeNode* root);
TreeNode* create_binary_tree(int* array,int array_length);
TreeNode* merge_two_binary_tree(TreeNode* left_tree,TreeNode* right_tree);
TreeNode* deleteNode(TreeNode* root,int value);
void preOrder_traversal_recursion(TreeNode* root);
void inOrder_traversal_recursion(TreeNode* root);
void postOrder_traversal_recursion(TreeNode* root);
void binary_tree_base_operation_test_1();
TreeNode_Stack* init_treeNode_stack(int init_size,int increment_size);
int is_empty_treeNode_stack(TreeNode_Stack* stack);
int is_full_treeNode_stack(TreeNode_Stack* stack);
TreeNode* pop_treeNode_stack(TreeNode_Stack* stack);
TreeNode* peep_treeNode_stack(TreeNode_Stack* stack);
int push_treeNode_stack(TreeNode_Stack* stack,TreeNode* node);
void preOrder_traversal(TreeNode* root);
void inOrder_traversal(TreeNode* root);
void postOrder_traversal(TreeNode* root);
void destroy_treeNode_stack(TreeNode_Stack* stack);
TreeNode_Queue* init_treeNode_queue(int init_size,int increment_size);
void destroy_treeNode_queue(TreeNode_Queue* queue);
int is_full_treeNode_queue(TreeNode_Queue* queue);
int is_empty_treeNode_queue(TreeNode_Queue* queue);
void enqueue_treeNode(TreeNode_Queue* queue,TreeNode* node);
TreeNode* dequeue_treeNode(TreeNode_Queue* queue);
TreeNode* peek_treeNode_queue(TreeNode_Queue* queue);
void level_traversal(TreeNode* root);
TreeNode* search_node(TreeNode* root,int value);
TreeNode* search_max_node(TreeNode* root);
TreeNode* search_min_node(TreeNode* root);
int get_binary_tree_height(TreeNode* root,int count);
int get_binary_tree_node_num(TreeNode* root);
int get_binary_tree_depth(TreeNode* root,TreeNode* target);
TreeNode* copy_binary_tree(TreeNode* root);
void binary_tree_base_operation_test_2();

int main(){
//    binary_tree_base_operation_test_1();
    binary_tree_base_operation_test_2();

    return 0;
}
/**
 *测试了以下函数：
 TreeNode* search_node(TreeNode* root,int value);
TreeNode* search_max_node(TreeNode* root);
TreeNode* search_min_node(TreeNode* root);
int get_binary_tree_height(TreeNode* root,int count);
int get_binary_tree_node_num(TreeNode* root);
int get_binary_tree_depth(TreeNode* root,TreeNode* target);
TreeNode* copy_binary_tree(TreeNode* root);
 */
void binary_tree_base_operation_test_2() {
    int array_size = 15;
    int* array = generate_random_array(0,1000,array_size);
    printf_array(array,array_size);

    //将数组构造成一颗二叉树
    TreeNode* root = create_binary_tree(array,array_size);

    printf("search_node:array[array_size/2]\n");
    TreeNode* search_node_data = search_node(root,array[array_size/2]);
    printf("search_node_data:%d\n",search_node_data->data);

    printf("search_max_node\n");
    TreeNode* search_max_node_data = search_max_node(root);
    printf("search_max_node:%d\n",search_max_node_data->data);

    printf("search_min_node\n");
    TreeNode* search_min_node_data = search_min_node(root);
    printf("search_min_node:%d\n",search_min_node_data->data);

    printf("get_binary_tree_height\n");
    printf("height:%d\n",get_binary_tree_height(root,0));

    printf("get_binary_tree_node_num\n");
    printf("node_num:%d\n",get_binary_tree_node_num(root));

    printf("get_binary_tree_depth\n");
    printf("depth:%d\n",get_binary_tree_depth(root,search_node_data));

    printf("copy_binary_tree\n");
    TreeNode* new_root = copy_binary_tree(root);
    printf("root:\n");
    preOrder_traversal(root);
    printf("copy_binary_tree:\n");
    preOrder_traversal(new_root);
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
void binary_tree_base_operation_test_1() {//生成一个随机数组
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

    //层序遍历
    printf("level_traversal\n ");
    level_traversal(root);
    printf("\n");
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
TreeNode_Stack* init_treeNode_stack(int init_size,int increment_size){
    TreeNode_Stack* stack = (TreeNode_Stack*)malloc(sizeof(TreeNode_Stack));
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
int is_empty_treeNode_stack(TreeNode_Stack* stack){
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
int is_full_treeNode_stack(TreeNode_Stack* stack){
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
TreeNode* pop_treeNode_stack(TreeNode_Stack* stack){
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
TreeNode* peep_treeNode_stack(TreeNode_Stack* stack){
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
int push_treeNode_stack(TreeNode_Stack* stack,TreeNode* node){
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
void destroy_treeNode_stack(TreeNode_Stack* stack){
    // 释放栈树节点中的frames资源
    free(stack->frames);
    // 释放栈树节点本身
    free(stack);
}

/**
 * 前序遍历(递归实现)
 * @param root
 */
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
    TreeNode_Stack* stack = init_treeNode_stack(10,10);
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
    printf("\n");
    destroy_treeNode_stack(stack);
}

/**
 * 中序遍历(递归实现)
 * @param root
 */
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
    TreeNode_Stack* stack = init_treeNode_stack(20,10);
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

/**
 * 后序遍历(递归实现)
 * @param root
 */
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
    TreeNode_Stack* stack = init_treeNode_stack(10,10);
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

/**
 * 初始化队列
 * @param init_size 初始化队列的大小
 * @param increment_size 队列满时增加的空间大小
 * @return 返回初始化后的队列指针
 */
TreeNode_Queue* init_treeNode_queue(int init_size,int increment_size){
    //给队列分配内存
    TreeNode_Queue* queue = (TreeNode_Queue*) malloc(sizeof(TreeNode_Queue));
    //给队列数据项空间分配内存
    queue->data_items = (TreeNode**) malloc(sizeof(TreeNode*) * init_size);
    //初始化队列的初始大小
    queue->init_size = init_size;
    //初始化队列的增量大小
    queue->increment_size = increment_size;
    //初始化队列的最大大小为初始大小
    queue->max_size = init_size;
    queue->front = 0;
    queue->tail = 0;
    //返回初始化后的队列指针
    return queue;
}

/**
 * 销毁树节点队列
 *
 * 本函数负责释放与树节点队列相关的所有内存资源，包括队列中数据项的内存和队列结构本身的内存
 * 这是为了防止内存泄漏，确保在不需要队列时，所有由队列动态分配的内存都能被正确释放
 *
 * @param queue 指向树节点队列的指针如果队列为空（即NULL），则函数不执行任何操作
 *
 */
void destroy_treeNode_queue(TreeNode_Queue* queue){
    if(queue == NULL){
        return;
    }
    // 释放队列中数据项的内存
    free(queue->data_items);
    // 释放队列结构本身的内存
    free(queue);
}

/**
 * 检查TreeNode_Queue队列是否已满
 *
 * @param queue 指向TreeNode_Queue队列的指针
 * @return 如果队列已满返回1，否则返回0
 */
int is_full_treeNode_queue(TreeNode_Queue* queue){
    // 如果队列的当前大小大于等于最大容量，则队列已满
    if(queue->queue_size >= queue->max_size){
        return 1;
    }
    return 0;
}

/**
 * 判断树节点队列是否为空
 *
 * 当队列的大小大于0时，表示队列不为空，返回0
 * 如果队列的初始大小与最大大小不相等，重新分配队列的空间大小
 * 当队列为空时，返回1
 *
 * @param queue 指向树节点队列的指针
 * @return 如果队列为空，则返回1；否则返回0
 */
int is_empty_treeNode_queue(TreeNode_Queue* queue){
    // 检查队列大小是否大于0
    if(queue->queue_size > 0){
        return 0;
    }
    // 检查队列是否已经进行了初始化
    if(queue->init_size != queue->max_size){
        // 重新分配队列空间大小
        realloc(queue->data_items,queue->init_size* sizeof(TreeNode*));
    }
    // 队列为空，返回1
    return 1;
}

/**
 * 将节点添加到树节点队列中
 *
 * 当队列满时，此函数会首先检查队列是否已满如果已满，它会分配一个新的更大的数据项数组，
 * 将现有数据项从当前数组复制到新数组中，然后将新数组设置为队列的数据项数组这个过程称为扩容
 *
 * @param queue 树节点队列的指针
 * @param node 要入队的树节点的指针
 */
void enqueue_treeNode(TreeNode_Queue* queue,TreeNode* node){
    //检查队列是否已满
    if(is_full_treeNode_queue(queue)){
        //队列已满，需要扩容
        //分配新的更大的数据项数组
        TreeNode** new_data_items = (TreeNode**) malloc(sizeof(TreeNode*) * (queue->max_size+queue->increment_size));
        //复制现有数据项到新数组中
        for(int i = 0;i < queue->max_size;i++){
           new_data_items[i] = queue->data_items[(queue->front++)%queue->max_size];
        }
        //更新队列的尾部索引，前端索引和最大尺寸
        queue->tail = queue->max_size;
        queue->front= 0;
        queue->max_size += queue->increment_size;
        //将新数组设置为队列的数据项数组
        queue->data_items = new_data_items;
    }
    //将节点添加到队列中
    queue->data_items[queue->tail++] = node;
    queue->tail %= queue->max_size;
    queue->queue_size++;
}

/**
 * 出队
 * @param queue 队列指针
 * @return 出队的树节点，如果队列为空则返回NULL
 */
TreeNode* dequeue_treeNode(TreeNode_Queue* queue){
    // 检查队列是否为空，为空则返回NULL
    if(is_empty_treeNode_queue(queue)){
        return NULL;
    }
    // 获取并移动队首指针，取出队首元素
    TreeNode* node =queue->data_items[queue->front++];
    // 使用模运算确保队首指针在队列大小范围内循环
    queue->front %= queue->max_size;
    queue->queue_size--;
    // 返回出队的节点
    return node;
}

/**
 * 获取队头元素但并不出队
 * @param queue 队列指针
 * @return 返回队头的TreeNode指针，如果队列为空则返回NULL
 */
TreeNode* peek_treeNode_queue(TreeNode_Queue* queue){
    if(is_empty_treeNode_stack(queue)){
        return NULL;
    }
    return queue->data_items[queue->front];
}

/**
 * 层序遍历(广度优先遍历)
 * @param root
 */
void level_traversal(TreeNode* root){
    if(root == NULL){
        return;
    }
    //初始化队列
    TreeNode_Queue* queue = init_treeNode_queue(10,10);
    //根节点入队
    enqueue_treeNode(queue,root);
    while(!is_empty_treeNode_queue(queue)){
        int size = queue->queue_size;
        for(int i = 0;i < size;i++){
            TreeNode* node = dequeue_treeNode(queue);
            if(node->left != NULL){
                enqueue_treeNode(queue,node->left);
            }
            if(node->right != NULL){
                enqueue_treeNode(queue,node->right);
            }
            printf("%d ",node->data);
        }
    }
    destroy_treeNode_queue(queue);
}

/**
 * 查找二叉树中某个节点
 * @param root 二叉树的根节点指针
 * @param value 需要查找的节点值
 * @return 如果找到指定值的节点，则返回该节点的指针；否则返回NULL
 */
TreeNode* search_node(TreeNode* root,int value){
    // 如果根节点为空，则直接返回NULL
    if(root == NULL){
        return NULL;
    }
    // 初始化一个队列用于层序遍历二叉树
    TreeNode_Queue* queue = init_treeNode_queue(10,10);
    // 将根节点入队
    enqueue_treeNode(queue,root);
    // 当队列不为空时，继续遍历
    while(!is_empty_treeNode_queue(queue)){
        // 获取当前队列中的节点数量
        int size = queue->queue_size;
        // 遍历当前队列中的所有节点
        for(int i = 0;i < size;i++){
            // 出队一个节点并检查其值是否为目标值
            TreeNode* node = dequeue_treeNode(queue);
            // 如果找到目标值，返回该节点的指针
            if(node->data == value){
                return node;
            }
            // 如果当前节点有左子节点，将左子节点入队
            if(node->left != NULL){
                enqueue_treeNode(queue,node->left);
            }
            // 如果当前节点有右子节点，将右子节点入队
            if(node->right != NULL){
                enqueue_treeNode(queue,node->right);
            }
        }
    }
    // 如果遍历完整个二叉树后仍未找到目标值，则返回NULL
    return NULL;
}

/**
 * 查找二叉树中的最大值
 * @param root 二叉树的根节点指针
 * @return 返回指向树中最大值节点的指针，如果树为空则返回NULL
 */
TreeNode* search_max_node(TreeNode* root){
    // 如果根节点为空，说明树为空，直接返回NULL
    if(root == NULL){
        return NULL;
    }
    // 递归查找左子树中的最大值节点
    TreeNode*  left = search_max_node(root->left);
    // 递归查找右子树中的最大值节点
    TreeNode* right = search_max_node(root->right);
    // 初始化最大值节点为当前根节点
    TreeNode* max_node = root;
    // 如果左子树的最大值节点存在且大于当前最大值节点，则更新最大值节点
    if(left != NULL && max_node->data < left->data){
        max_node = left;
    }
    // 如果右子树的最大值节点存在且大于当前最大值节点，则更新最大值节点
    if(right != NULL && max_node->data < right->data){
        max_node = right;
    }
    // 返回树中的最大值节点
    return max_node;
}

/**
 * 查找二叉树中的最小值
 * @param root
 * @return
 */
TreeNode* search_min_node(TreeNode* root){
    // 如果根节点为空，说明树为空，直接返回NULL
    if(root == NULL){
        return NULL;
    }
    // 递归查找左子树中的最小值节点
    TreeNode*  left = search_min_node(root->left);
    // 递归查找右子树中的最小值节点
    TreeNode* right = search_min_node(root->right);
    // 初始化最小值节点为当前根节点
    TreeNode* min_node = root;
    // 如果左子树的最小值节点存在且小于当前最小值节点，则更新最小值节点
    if(left != NULL && min_node->data > left->data){
        min_node = left;
    }
    // 如果右子树的最小值节点存在且小于当前最小值节点，则更新最小值节点
    if(right != NULL && min_node->data > right->data){
        min_node = right;
    }
    // 返回树中的最小值节点
    return min_node;
}

/**
 * 计算二叉树的高度
 *
 * @param root 二叉树的根节点指针
 * @param count 当前遍历的层数
 * @return 返回二叉树的高度
 *
 * 该函数通过递归方式计算二叉树的高度定义如下：
 * 1. 如果根节点为空，则返回当前的层数作为高度
 * 2. 否则，递归计算左子树和右子树的高度，然后取其中较大值作为当前二叉树的高度
 */
int get_binary_tree_height(TreeNode* root,int count){
    // 判断当前节点是否为空，如果为空则返回当前层数
    if(root == NULL){
        return count;
    }
    // 当前层数加一，表示进入下一层
    count++;
    // 递归计算左子树的高度
    int left = get_binary_tree_height(root->left,count);
    // 递归计算右子树的高度
    int right = get_binary_tree_height(root->right,count);
    // 比较左子树和右子树的高度，返回较大值
    return left > right ? left : right;
}

/**
 * 计算目标节点的深度
 * @param root 二叉树的根节点
 * @param target 需要寻找的目标节点
 * @return 如果目标节点存在于树中，则返回目标节点的深度；否则返回0
 */
int get_binary_tree_depth(TreeNode* root,TreeNode* target){
    // 检查输入的根节点或目标节点是否为空，如果为空，则返回0
    if(root == NULL || target == NULL){
        return 0;
    }

    // 递归计算左子树中目标节点的深度
    int left = get_binary_tree_depth(root->left,target);
    // 递归计算右子树中目标节点的深度
    int right = get_binary_tree_depth(root->right,target);

    // 根据左右子树的深度，选择非零的深度作为当前节点的深度
    int depth = left == 0 ? right:left;

    // 如果当前节点是目标节点，或者当前节点的子树中包含目标节点，则返回当前深度加1
    if(root == target || depth != 0){
        return depth + 1;
    }

    // 如果当前节点及其子树中都不包含目标节点，则返回0
    return 0;
}

/**
 * 计算二叉树节点数
 * @param root 二叉树的根节点指针
 * @return 二叉树的节点总数
 */
int get_binary_tree_node_num(TreeNode* root){
    // 如果节点为空，则返回0，表示该子树不存在节点
    if(root == NULL){
        return 0;
    }

    // 递归计算左子树的节点数
    int left = get_binary_tree_node_num(root->left);
    // 递归计算右子树的节点数
    int right = get_binary_tree_node_num(root->right);

    // 返回左子树节点数、右子树节点数和根节点的总和
    return left + right + 1;
}

/**
 * 判断二叉树是否为空
 * @param root
 * @return
 */
int is_binary_tree_empty(TreeNode* root){
    if(root == NULL){
        return true;
    }
    return false;
}

/**
 * 复制二叉树
 * @param root 原始二叉树的根节点
 * @return 新建二叉树的根节点指针
 *
 * 该函数通过递归方式复制一个二叉树。对于给定的原始二叉树，它会创建一个新节点，
 * 然后递归地复制原始二叉树的左子树和右子树到新节点的左子树和右子树。
 */
TreeNode* copy_binary_tree(TreeNode* root){
    if(root == NULL){
        return NULL;
    }
    TreeNode* new_node = create_node(root->data);
    // 递归复制左子树
    new_node->left =copy_binary_tree(root->left);
    // 递归复制右子树
    new_node->right = copy_binary_tree(root->right);
    // 返回新节点作为当前子树的根节点
    return new_node;
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


/**
 * 左旋二叉树
 * @param root 二叉树的根节点指针
 * @return 旋转后的根节点指针
 */
TreeNode* left_rotate_binary_tree(TreeNode* root){
    //记录新的根节点
    TreeNode* right_child = root->right;
    //原根节点的右子树变为新根节点的左子树
    root->right = right_child->left;
    //原根节点变为新根节点的左子树的根节点
    right_child->left = root;
    //返回新的根节点
    return right_child;
}

/**
 * 右旋二叉树
 * @param root
 * @return
 */
TreeNode* right_rotate_binary_tree(TreeNode* root){
    //记录新的根节点
    TreeNode* left_child = root->left;
    //原根节点的左子树变成新根节点的右子树
    root->left = left_child->right;
    //原根节点变为新根节点的右子树的根节点
    left_child->right = root;
    //返回新的根节点
    return left_child;
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

