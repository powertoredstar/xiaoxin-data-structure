//
// Created by 1 on 2024/10/15.
//
//所需要用到的标准库头文件
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//函数声明
void generate_random_array(int arr[],int size);
void printf_array(const int arr[],int size);
void radix_sort(int arr[],int size);
void radix_sort_descending(int arr[],int size);

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
//    radix_sort(array,array_size);
    radix_sort_descending(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//获取num的第digit位
int get_digit(int num,int digit){
    return (num / (int)pow(10,digit)) % 10;
}
//反转数组
void reverse_array(int array[],int size){
    for(int i = 0,j = size - 1;i < j;i++,j--){
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

//计数排序(针对基数排序0-9的)(升序)
void counting_sort(int arr[],int size,int digit){
    //创建计数数组并初始化为0
    int *count_array = (int*) malloc(sizeof(int) * 10);
    for(int i = 0;i < 10;i++){
        count_array[i] = 0;
    }

    //计算每一个元素出现的次数
    for(int i = 0;i < size;i++){
        count_array[get_digit(arr[i],digit)]++;
    }

    //累加每个元素出现的次数
    for(int i = 1;i < 10;i++){
        count_array[i] += count_array[i-1];
    }

    //创建输出数组
    int *output = (int*)malloc(sizeof(int) * size);
    //从后向前遍历，并将元素放入输出数组中
    for(int i = size-1;i >= 0;i--){
        output[--count_array[get_digit(arr[i],digit)]] = arr[i];
    }

    //将输出数组拷贝给原数组
    for(int i = 0;i < size;i++){
        arr[i] = output[i];
    }

    free(output);
}
//基数排序(降序)
void radix_sort_descending(int arr[],int size){
    //找到数组中的最大值
    int max_val = arr[0];
    for(int i = 0;i < size;i++){
        if(max_val < arr[i]){
            max_val = arr[i];
        }
    }

    //计算最大位数
    int max_digits = 0;
    while(max_val != 0){
        max_val /= 10;
        max_digits++;
    }
    //逐位排序
    for(int i = 0;i < max_digits;i++){
        counting_sort(arr,size,i);
    }
    //反转数组
    reverse_array(arr,size);
}
//基数排序(升序)
void radix_sort(int arr[],int size){
    //确定最大值
    int max_val = arr[0];
    for(int i = 0;i < size;i++){
        if(max_val <= arr[i]){
            max_val = arr[i];
        }
    }

    //确定最大值的位数
    int max_digits = 0;
    while(max_val != 0){
        max_val /= 10;
        max_digits++;
    }

    //逐位排序
    for(int i = 0; i < max_digits;i++){
        counting_sort(arr,size,i);
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
