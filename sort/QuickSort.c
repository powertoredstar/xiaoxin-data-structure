//
// Created by 1 on 2024/10/15.
//
//所需要用到的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_random_array(int arr[],int size);
void printf_array(const int arr[],int size);
void quick_sort(int array[],int left,int right);
void quick_sort_descending(int array[],int left,int right);

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
//    quick_sort(array,0,array_size-1);
    quick_sort_descending(array,0,array_size-1);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//快速排序(降序)
void quick_sort_descending(int array[],int left,int right){
    //获取基准值索引
    int mid = left + (right - left) / 2;
    int pivot = array[mid];
    int p1 = left;
    int p2 = right;
    //左右两个指针进行partition
    while(p1 <= p2){
        //找到左边第一个小于基准值的元素
        while(p1 <= p2 && array[p1] > pivot){
            p1++;
        }
        //找到右边第一个大于基准值的元素
        while(p1 <= p2 && array[p2] < pivot){
            p2--;
        }
        //交换
        if(p1 <= p2) {
            int temp = array[p1];
            array[p1] = array[p2];
            array[p2] = temp;
            p1++;
            p2--;
        }
    }
    //递归
    if(left < p2){
        quick_sort_descending(array,left,p2);
    }
    if(p1 < right){
        quick_sort_descending(array,p1,right);
    }
}
//快速排序(升序)
void quick_sort(int array[],int left,int right){
    if(array == NULL || left > right){
        return;
    }
    //选择基准值
    int mid = left + (right - left) / 2;
    int pivot = array[mid];
    int p1 = left;
    int p2 = right;
    //左右两个指针进行partition
    while(p1 <= p2){
        //找到左边第一个大于基准值的元素
        while(p1 <= p2 && array[p1] < pivot){
            p1++;
        }
        //找到右边第一个小于基准值的元素
        while(p1 <= p2 && array[p2] > pivot){
            p2--;
        }
        //交换两个元素
        if(p1 <= p2){
            int temp = array[p1];
            array[p1] = array[p2];
            array[p2] = temp;
            p1++;
            p2--;
        }
    }
    //递归
    if(left < p2){
        quick_sort(array,left,p2);
    }
    if(p1 < right){
        quick_sort(array,p1,right);
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