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
void counting_sort(int arr[],int size);
void counting_sort_descending(int arr[],int size);
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
//    counting_sort(array,array_size);
    counting_sort(array,array_size);

    //打印排序后的数组
    printf("after sort\n");
    printf_array(array,array_size);

    //释放内存
    free(array);

    return 0;
}
//计数排序(降序)
void counting_sort_descending(int arr[],int size){
    //确定数据范围(找出最大值和最小值)
    int min_val = arr[0];
    int max_val = arr[0];
    for(int i = 0;i < size;i++){
        if(min_val > arr[i]){
            min_val = arr[i];
        }
        if(max_val < arr[i]){
            max_val = arr[i];
        }
    }
    //创建辅助计数数组并初始化为0
    int range = max_val - min_val + 1;
    int *count_array =(int*) malloc(sizeof(int)*range);
    for(int i = 0;i < range;i++){
        count_array[i] = 0;
    }
    //统计元素出现的个数
    for(int i = 0;i < size;i++){
        count_array[arr[i] - min_val]++;
    }
    //累加计数数组，确定每个数对应的排序后的位置
    for(int i = 1;i < range;i++){
        count_array[i] += count_array[i-1];
    }
    //创建输出数组
    int *output = (int*) malloc(sizeof(int) * size);
    for(int i = 0;i < size;i++){
        output[--count_array[arr[i] - min_val]] = arr[i];
    }
    //将排序后的数组复制回原数组(降序)
    for(int i = 0,j = size - 1;i < size && j >= 0;i++,j--){
        arr[i] = output[j];
    }
}
//计数排序(升序)
void counting_sort(int arr[],int size){
    //确定数据范围(找出最大值和最小值)
    int min_val = arr[0];
    int max_val = arr[0];
    for(int i = 0;i < size;i++){
        if(min_val > arr[i]){
            min_val = arr[i];
        }
        if(max_val < arr[i]){
            max_val = arr[i];
        }
    }
    int range = max_val - min_val + 1;
    //创建计数数组并初始化为0
    int *count_array = (int*) malloc(sizeof(int)*range);
    for(int i = 0;i < range;i++){
        count_array[i] = 0;
    }
    //统计元素出现的个数
    for(int i = 0;i < size;i++){
        count_array[arr[i] - min_val]++;
    }
    //累加计数数组,确定每个数对应的排序后位置
    for(int i = 1;i < range;i++){
        count_array[i] += count_array[i-1];
    }
    //创建输出数组
    int *output = (int*) malloc(sizeof(int)*size);
    //从后向前存入元素并减少相应计数
    for(int i = size-1;i >= 0;i--){
        output[--count_array[arr[i] - min_val]] = arr[i];
    }
    //将排序后的数组复制回原数组
    for(int i = 0;i < size;i++){
        arr[i] = output[i];
    }
    //释放内存
    free(count_array);
    free(output);
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
