//
// Created by 1 on 2024/10/15.
//
//所需要用到的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//函数声明
void generate_random_array(int arr[],int size);
void printf_array(const int arr[],int size);
void heap_sort(int arr[],int size);
void heap_sort_descending(int arr[],int size);

int main(){
    //定义数组大小
    int array_size = 10;

    //动态分配数组
    int *array = (int*)malloc(array_size*sizeof(int));

    //随机生成数组
    generate_random_array(array,array_size);

    //打印排序前的数组
    printf("before sort\n");
    printf_array(array,array_size);


    //对数组进行排序
//    heap_sort(array,array_size);
    heap_sort_descending(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//调整堆(降序)
void heapify_descending(int arr[],int size,int rootIndex){
    int minIndex = rootIndex; //最小值索引
    int left = rootIndex * 2 + 1;//左子节点
    int right = rootIndex * 2 + 2;//右子节点

    //找出最小值
    if(left < size && arr[left] < arr[minIndex]){
        minIndex = left;
    }
    if(right < size && arr[right] < arr[minIndex]){
        minIndex = right;
    }

    //如果根节点不是最小值,交换并调整堆
    if(minIndex != rootIndex){
        int temp = arr[minIndex];
        arr[minIndex] = arr[rootIndex];
        arr[rootIndex] = temp;

        //递归调整受影响的子树
        heapify_descending(arr,size,minIndex);
    }

}
//调整堆(升序)
void heapify(int arr[],int size,int rootIndex){
    int largest = rootIndex;//最大值索引
    int left = 2 * rootIndex + 1;//左子节点
    int right = 2 * rootIndex + 2;//右子节点

    //判断左子节点是否大于根节点
    if(left < size && arr[left] > arr[largest]){
        largest = left;
    }
    //判断右子节点是否大于根节点
    if(right < size && arr[right] > arr[largest]){
        largest = right;
    }
    //判断根节点是否为最大值,如果不是，则交换并调整堆
    if(largest != rootIndex){
        int temp = arr[largest];
        arr[largest] = arr[rootIndex];
        arr[rootIndex] = temp;

        //递归调整子树
        heapify(arr,size,largest);
    }
}
//堆排序(升序)
void heap_sort(int arr[],int size){
    //构造堆
    for(int i = size / 2 - 1;i >= 0;i--){
        heapify(arr,size,i);
    }
    //从堆中取出最大值并调整堆
    for(int i = size -1 ;i >= 0;i--){
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        //调整堆
        heapify(arr,i,0);
    }
}
//堆排序(降序)
void heap_sort_descending(int arr[],int size){
    //构造堆
    for(int i = size / 2 - 1;i >= 0;i--){
        heapify_descending(arr,size,i);
    }

    //从堆中取出最小值，并调整堆
    for(int i = size-1;i >= 0;i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        //调整堆
        heapify_descending(arr,i,0);
    }
}
//生成指定大小的随机整数数组
void generate_random_array(int arr[],int size){
    //设置随机种子
    srand((unsigned int)time(NULL));
    for(int i = 0;i < size;i++){
        arr[i] = rand() % 100;//生成0到99之间的随机数
    }
}
//打印数组内容
void printf_array(const int arr[],int size){
    for(int i = 0;i < size;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}