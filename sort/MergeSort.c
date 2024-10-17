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
void merge_sort(int arr[],int left,int right);
void merge_sort_descending(int arr[],int left ,int right);

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
//    merge_sort(array,0,array_size-1);
    merge_sort_descending(array,0,array_size-1);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//合并(降序)
void merge_descending(int arr[],int left,int mid ,int right){
    //确定两个子数组各自的大小
    int array_left_size = mid - left + 1;
    int array_right_size = right - mid;

    //创建两个临时数组来存放两个子数组
    int *L = (int*) malloc(array_left_size * sizeof(int));
    int *R = (int*) malloc(array_right_size * sizeof(int));

    for(int i = 0;i < array_left_size;i++){
        L[i] = arr[left + i];
    }
    for(int i = 0;i < array_right_size ;i++){
        R[i] = arr[mid + 1 + i];
    }

    //两个临时数组的索引
    int array_left_index = 0;
    int array_right_index = 0;
    int array_index = left;

    //将两个临时有序子数组合并成一个有序数组
    while(array_left_index < array_left_size && array_right_index < array_right_size){
        if(L[array_left_index] >= R[array_right_index]){
            arr[array_index++] = L[array_left_index++];
        }else{
            arr[array_index++] = R[array_right_index++];
        }
    }

    //将剩余的数据合并到数组中
    while(array_left_index < array_left_size){
        arr[array_index++] = L[array_left_index++];
    }
    while(array_right_index < array_right_size){
        arr[array_index++] = R[array_right_index++];
    }
}
//归并排序(降序)
void merge_sort_descending(int arr[],int left ,int right){
    if(left < right){
        //确定中间索引
        int mid = left + (right - left) / 2;
        //将数组分成两部分进行排序，再合并
        merge_sort_descending(arr,left,mid);
        merge_sort_descending(arr,mid+1,right);

        //合并
        merge_descending(arr,left,mid,right);
    }
}
//合并(将两个有序的子数组合并成一个有序的子数组)
void merge(int arr[],int left,int mid,int right){
    //确定两个有序子数组各自的数量
    int array_left_size = mid - left + 1;
    int array_right_size = right - mid;

    //创建两个临时数组存放两个有序的子数组
    int *L = (int*) malloc(sizeof(int)*array_left_size);
    int *R = (int*)malloc(sizeof(int)* array_right_size);

    //将子数组的数据存放到临时数组中
    for(int i = 0;i < array_left_size;i++){
        L[i] = arr[left + i];
    }
    for(int i = 0;i < array_right_size;i++){
        R[i] = arr[mid + 1 + i];
    }
    //两个临时数组的索引
    int left_index = 0;
    int right_index = 0;
    int array_index = left;
    //合并两个子数组
    while(left_index < array_left_size && right_index < array_right_size){
        if(L[left_index] <= R[right_index]){
            arr[array_index++] = L[left_index++];
        }else{
            arr[array_index++] = R[right_index++];
        }
    }
    //将剩余的数组合并到数组中
    while(left_index < array_left_size){
        arr[array_index++] = L[left_index++];
    }
    while(right_index < array_right_size){
        arr[array_index++] = R[right_index++];
    }
}
//归并排序(升序)(负责将数组分成两半，递归对每一半进行排序，然后再将它们合并)
void merge_sort(int arr[],int left,int right){
    //计算中间索引
    if(left < right){
        int mid = left + (right - left) / 2;

        //递归将数组分成两半
        merge_sort(arr,left,mid);
        merge_sort(arr,mid + 1,right);

        //合并两个有序的子数组
        merge(arr,left,mid,right);
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
