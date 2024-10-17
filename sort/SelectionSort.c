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
void selection_sort(int array[],int size);
void selection_sort_descending(int array[],int size);


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
//    selection_sort(array,array_size);
    selection_sort_descending(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}

//选择排序(升序)
void selection_sort(int array[],int size){
    //最小元素的索引
    int min_val_index = 0;

    //逐步排序
    for(int i = 0;i < size-1;i++){
        //更新最小值索引
        min_val_index = i;

        //寻找第i个元素到数组末尾的最小值索引
        for(int k = i;k < size;k++){
            if(array[min_val_index] > array[k]){
                min_val_index = k;
            }
        }
         //将最小值与第i个元素交换
        int temp = array[i];
        array[i] = array[min_val_index];
        array[min_val_index] = temp;

    }
}
//选择排序(降序)
void selection_sort_descending(int array[],int size){
    //最大值索引
    int max_val_index = 0;

    //逐步排序
    for(int i = 0;i < size-1;i++){
        //更新最大值索引
        max_val_index = i;

        //寻找最大值
        for(int k = i;k < size;k++){
            if(array[max_val_index] < array[k]){
                max_val_index = k;
            }
        }

        //最大值与当前值交换
        int temp = array[max_val_index];
        array[max_val_index] = array[i];
        array[i] = temp;
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
