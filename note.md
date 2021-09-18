## 206
掌握递归和循环，递归不要忘了置nullptr<br/>
循环中，使用多指针<br/>
## 3

双指针<br/>
## 146
指针要初始化为nullptr<br/>
## 215
如果要改vecotr的值，要传引用
堆排序<br/>
<details>
  <summary> <code>kernel/sched/fair.c	-sched_setnuma</code> </summary>

``` C++ {.line-numbers}
#include<iostream>
using namespace std;
void swap(int* a,int* b){
    int tem = *a;
    *a = *b;
    *b = tem;
}

//c++ 中，数组形参是以指针的形式传递的，无法在函数内求得数组的长度！
void forLen(int arr[]){
    int len = sizeof(arr)/sizeof(arr[0]);//打印为：2.因为指针长度为4，int为2.
    cout<<len<<endl;
}

void print_arr(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout<<arr[i]<<" ,";
    }
    cout<<endl;
}
/*
节点i的父节点：(i-1)/2
节点i的左孩子节点： 2*i+1
节点i的右孩子节点： 2*i+2

            0
        1       2
    3       4
*/
void heapify(int arr[],int n,int i);

void heapSort(int arr[],int n){
    int i;
    //从最后一个节点的父节点开始
    for(i = n/2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    for(i = n-1; i > 0; i--){
        swap(&arr[i],&arr[0]);
        heapify(arr,i,0);
    }
}
//这里如果找的是最小值，那么是递减的
//否则，递增
void heapify(int arr[],int size,int i){
    int largest = i;
    int lson = 2*i+1;
    int rson = 2*i+2;
    if(lson < size && arr[largest] < arr[lson]){//改两个大于小于，递增递减
        largest = lson;
    }
    if(rson < size && arr[largest] < arr[rson]){//改两个大于小于，递增递减
        largest = rson;
    }
    if(largest != i){
        swap(&arr[largest],&arr[i]);
        heapify(arr,size,largest);
    }
}

int main(){
    int arr[] = {3,5,2,6,8,7,9,10};
    int* arr2 = new int[9];
    forLen(arr);//打印为2
    forLen(arr2);//打印为2
    
    int len = (int)sizeof(arr)/sizeof(arr[0]);
    cout<<len<<endl;
    
    print_arr(arr,len);
    heapSort(arr,len);
    print_arr(arr,len);

    return 0;
}
```
</details>

快排<br/>

<details>
  <summary> <code>kernel/sched/fair.c	-sched_setnuma</code> </summary>

``` C++ {.line-numbers}

```
</details>


todo :<br/>

5.15