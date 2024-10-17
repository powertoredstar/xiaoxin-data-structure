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
void insertion_sort(int arr[],int size);
void insertion_sort_descending(int arr[],int size);

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
//    insertion_sort(array,array_size);
    insertion_sort_descending(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//插入排序(降序)
void insertion_sort_descending(int arr[],int size){
    //假设第一个元素已经排好序,所以从第二个元素开始
    for(int i =1 ;i < size;i++){
        int target = arr[i];
        int already_sorted = i -1;
        //从后向前扫描，找到第一个大于当前元素的值
        while(already_sorted >= 0 && arr[already_sorted] < target){
            arr[already_sorted+1] = arr[already_sorted];
            already_sorted--;
        }
        arr[already_sorted+1] = target;
    }
}
//插入排序
void insertion_sort(int arr[],int size){
    //假设第一个元素已经排好序,所以从第二个元素开始
    for(int i =1;i < size;i++){
        //已排好的最后一个元素的索引
        int already_sorted = i - 1;
        int target = arr[i];
        //从后向前扫描，找到可以插入的位置(第一个小于当前元素的元素)
        while(already_sorted > 0 && arr[already_sorted] > target){
            arr[already_sorted+1] = arr[already_sorted];
            already_sorted--;
        }
        arr[already_sorted+1] = target;
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
