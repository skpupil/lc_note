## lc-206
掌握递归和循环，递归不要忘了置nullptr<br/>
循环中，使用多指针<br/>
## lc-3

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
---------------------------------------------------------
    void heapify(vector<int>& nums ,int size,int k) {
        int fla = k;
        
        int ll = k*2+1;
        int rr = k*2+2;
        if(ll < size && nums[ll] > nums[fla]) {
            fla = ll;
        }
        //这里的size是必须要有的！！！
        if(rr < size && nums[rr] > nums[fla]) {
            fla = rr;
        }
        if(fla != k) {
            swap(nums[fla],nums[k]);
            heapify(nums,size,fla);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        for(int i = (len/2)-1; i >= 0; i--) {
            heapify(nums,len,i);
        }
        for(int i = len-1;i >= len-k;i--) {
            swap(nums[i],nums[0]);
            heapify(nums,i,0);
        }
        return nums[len-k];
     }

```
</details>

快排<br/>

<details>
  <summary> <code>kernel/sched/fair.c	-sched_setnuma</code> </summary>

``` C++ {.line-numbers}
#include<iostream>
using namespace std;

void print_arr(int arr[], int n){
    for(int i = 0; i < n; i++){
        cout<<arr[i]<<" ,";
    }
    cout<<endl;
}
/*
左右挖坑互填：
代码是递增的，改为递减，只需要两个地方的，>=改<=，<= 改>=。
不能漏掉=，否则会遇到相同元素的时候，会死循环

*/
int partition(int arr[],int l,int r){
    int pivot = arr[l];
    while(l < r){
        while(l < r && arr[r] >= pivot)
            r--;
        arr[l] = arr[r];
        while (l < r && arr[l] <= pivot)
            l++;
        arr[r] = arr[l];
    }
    arr[l] = pivot;
    return l;
}
/*
tem这里是标杆的位置，左都是小于，右面是大于。

*/
void fast_sort(int arr[],int l,int r){
    if (l < r)
    {
        cout<<"beofre: "<<endl;
        print_arr(arr,6);
        int tem = partition(arr,l,r);
        cout<<tem<<"end: "<<endl;
        print_arr(arr,6);
        fast_sort(arr,l,tem-1);
        fast_sort(arr,tem+1,r);
    } 
}


int main(){
    int arr[] = {3,2,1,5,6,4};
    int* arr2 = new int[9];
    int len = (int)sizeof(arr)/sizeof(arr[0]);
    print_arr(arr,len);
    fast_sort(arr,0,len-1);
    print_arr(arr,len);

    return 0;
}
```
</details>


todo :



lc-33
```
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int le = 0, ri = nums.size() - 1 , mid = 0;
        if(ri == -1) return -1;
        while(le <= ri) {
            mid = le + (ri - le)/2;//注意，两个数的时候，mid结果是le
            if(nums[mid] == target)
                return mid;
            //先判断在左段还是右段
            if(nums[le] <= nums[mid]){//这是在左段，等号是两个数的情况下，两者相等，mid是在左段
                if(nums[le] <= target && target < nums[mid])//target在mid左（target不在mid），都可以动ri 
                    ri = mid - 1;
                else //否则动le
                    le = mid + 1;
            }else {
                if(nums[mid] < target && target <= nums[ri])
                    le = mid + 1;
                else 
                    ri = mid -1;
            }
        }
        return -1;
    }
};
```

lc-142
判断链表环入口的位置。
假设两个人同时同起点开始跑步，快人是慢人的速度两倍，慢人跑完一圈，回到起点，快人跑完两圈，同时回到起点。也就是说，两人相遇的地方，一定在慢人刚跑完第一圈或者之前，不可能慢人跑超过一圈，才相遇。
上面只考虑环，这个问题，可能环之前还有一段长度。如果这样，快人率先进环，还是符合刚才的结论。
假设环入口之前的长度为a，a到第一次相遇的位置的长度为b，剩下的一段为c。
基于前面的结论，那么慢人一定是跑了(a+b),快人跑了(a+b+c+b),快人跑了是慢人两倍距离：2(a+b)=a+b+c+b.这样得出a=c。
这样，只需要第一次相遇后，快人改为从head开始，速度为1，慢人从相遇点继续，速度也为1，相遇点就是环的入口。

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head == nullptr || head->next == nullptr)
            return nullptr;
        ListNode* fastt = head, *loww = head;
        fastt = head->next->next;
        loww = head->next;
        while(1) {
            if(fastt == nullptr || loww == nullptr)
                return nullptr;
            if(fastt == loww)
                break;
            if(fastt->next != nullptr)
                fastt = fastt->next->next;
            else
                return nullptr;
            loww = loww->next;
        }
        fastt = head;
        while(fastt != loww) {
            fastt = fastt->next;
            loww = loww->next;
        }
        return loww;
    }
};
```

## lc-704
标准二分法
```
    int search(vector<int>& nums, int target) {
        int mid = 0 ,l = 0, r = nums.size()-1;
        while(l <= r) {//[l,r]，左右边界都包含，这里要写上=
            mid = l + (r-l)/2;
            if(nums[mid] == target) return mid;
            else if(nums[mid] > target) r = mid-1;
            else l = mid + 1;
        }
        return -1;
    }
```
## lc-35
找第一个大于等于target的下标
标准写法，最后返回l即可。
```
    int searchInsert(vector<int>& nums, int target) {
        int mid = 0, l = 0, r = nums.size() - 1;
        while(l <= r) {
            mid = l + (r-l)/2;
            if(target == nums[mid]) return mid;
            else if(target > nums[mid]) l = mid + 1;
            else r = mid - 1;
        }
        return l;
    }
```

## lc-300
dp[i]:以nums[i]结尾的最长上升子序列的长度。
```
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if(len == 0)return 0;
        int dp[len+1];
        dp[0] = 1;
        int ans = 1;
        for(int i=1;i<len;i++) {
            dp[i] = 1;
            for(int j = 0;j<i;j++) {
                if(nums[i] > nums[j])
                    dp[i] = max(dp[i],dp[j]+1);
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
```
二分查找法，也很简单，无非就是再新建一个数组，然后第一个数先放进去，然后第二个数和第一个数比较，如果说大于第一个数，那么就接在他后面，如果小于第一个数，那么就替换，一般的，如果有i个数，那么每进来一个新的数，都要用二分查找法来得知要替换在哪个位置的数（lc-35）。因为有个for循环，所以是O(N),在加上循环里有个二分查找，所以最后是O(NlogN)的时间复杂度。

相当于维护一个结果数组，如果当前元素比结果数组的值都大的的话，就追加在结果数组后面（相当于递增序列长度加了1）；否则的话用当前元素覆盖掉第一个比它大的元素（这样做的话后续递增序列才有可能更长，即使并没有更长，这个覆盖操作也并没有副作用哈，当然这个覆盖操作可能会让最终的结果数组值并不是最终的递增序列值，这无所谓）

```
    int lengthOfLIS(vector<int>& nums) {
        int len = nums.size();
        if(len == 0)return 0;
        int rec[len+1];
        int lenrec = 0;
        for(int i=0;i<len;i++) {
            int cur = nums[i], l = 0, r = lenrec - 1;
            while(l <= r) {
                int mid = l + (r-l)/2;
                if(rec[mid] == cur){l = mid; break;}
                else if(rec[mid] > cur) r = mid - 1;
                else l = mid + 1;
            }
            rec[l] = cur;
            if(l == lenrec) lenrec++;
        }
        return lenrec;
    }
```