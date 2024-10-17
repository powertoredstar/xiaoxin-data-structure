//
// Created by 1 on 2024/10/15.
//
//所需要用到的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

void generate_random_array(int arr[],int size);
void printf_array(const int arr[],int size);
void bucket_sort(int arr[],int size);
void quick_sort(int array[],int left,int right);

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
    bucket_sort(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//桶排序(升序)
void bucket_sort(int arr[],int size){
    //确定桶的数量(通常为数组长度的平方根)
    int bucket_num = sqrt(size);

    //确定桶的范围
    //找出最大值和最小值
    int min_val = arr[0];
    int max_val = arr[size-1];
    for(int i = 0;i < size;i++){
        if(arr[i] < min_val){
            min_val = arr[i];
        }
        if(arr[i] > max_val){
            max_val = arr[i];
        }
    }

    //确定桶的宽度
    int bucket_width = (max_val - min_val) / bucket_num + 1;

    //创建桶数组
    int **bucket_array = (int**)malloc(bucket_num* sizeof(int*));
    for(int i = 0;i < bucket_num;i++){
        bucket_array[i] = (int*)malloc(size*sizeof(int));
    }

    //创建桶索引数组
    int *bucket_index_array = (int*) malloc(bucket_num*sizeof(int));
    for(int i = 0;i < bucket_num;i++){
        bucket_index_array[i] = 0;
    }

    //将元素装入桶中
    for(int i = 0;i < size;i++){
        int bucket_index = (arr[i]-min_val) / bucket_width;
        bucket_array[bucket_index][bucket_index_array[bucket_index]++] = arr[i];
    }

    //对各个桶进行排序并合并桶中的元素
    int point = 0;
    for(int i = 0;i < bucket_num;i++){
        //检查桶内是否有元素
        if(bucket_index_array[i] == 0){
            continue;
        }
        //对桶内元素进行排序
        quick_sort(bucket_array[i],0,bucket_index_array[i]-1);
        //合并桶中的元素
        for(int k = 0;k < bucket_index_array[i];k++){
            arr[point++] = bucket_array[i][k];
        }
    }

    //释放内存
    free(bucket_index_array);
    free(bucket_array);
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