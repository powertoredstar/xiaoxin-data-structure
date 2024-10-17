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
void shell_sort(int arr[],int size);
void shell_sort_descending(int array[],int size);


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
//    shell_sort(array,array_size);
    shell_sort_descending(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//希尔排序(降序)
void shell_sort_descending(int array[],int size){
    //初始化增量为数组长度的一半
    for(int gap = size / 2;gap > 0 ;gap /= 2){
        //对子序列进行插入排序
        for(int i = gap;i < size ;i++){
            int target = array[i];
            int already_sorted_index = i;
            while(already_sorted_index >= gap && array[already_sorted_index-gap] < target){
                array[already_sorted_index] = array[already_sorted_index - gap];
                already_sorted_index -= gap;
            }
            array[already_sorted_index] = target;
        }
    }
}
// 希尔排序(升序)
void shell_sort(int array[], int size) {
  //初始增量为数组长度的一半
  for(int gap = size / 2;gap > 0; gap /= 2){
      //根据增量进行插入排序
      for(int i = gap; i < size;i++){
          int target = array[i];
          int already_sorted_index = i;
          while(already_sorted_index >= gap && array[already_sorted_index-gap] > target){
              array[already_sorted_index] = array[already_sorted_index - gap];
              already_sorted_index -= gap;
          }
          array[already_sorted_index] = target;
      }
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
