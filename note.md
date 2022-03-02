## lc-206
注意判断head==nullptr特殊情况
掌握递归和循环，递归不要忘了最后的元素next置nullptr<br/>
循环中，使用多指针<br/>

循环
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == nullptr)
            return head;

        ListNode* pre = nullptr;
        ListNode* curr = head;
        ListNode* nextt = curr->next;
        while(curr != nullptr){
            nextt = curr->next;
            curr->next = pre;
            pre = curr;
            curr = nextt;
        }
        return pre;
    }
};
```
递归
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {

        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode* temp = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return temp;
    }
};
```
栈
```
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<ListNode* > stk;
        ListNode* first = new ListNode(0);
        ListNode* temp = first;
        while(head){
            stk.push(head);
            head = head->next;
        }
        while(!stk.empty()){
            temp->next = stk.top();
            stk.pop();
            temp = temp->next;
        }
        temp->next = nullptr;
        return first->next;
    }
};
```

## lc-3

双指针<br/>

```
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0)
            return 0;
        int left = 0;
        int right = 0;
        int ans = 0;
        int record[256] = {0};
        while(1) {
            if(right == s.length())
                return ans ;

            if(record[ s[right ] - ' ' ] == 0) {
                record[s[right] - ' ' ] = 1;
                if(ans < right - left + 1){
                    ans = right - left + 1 ;
                }
                right++;
            }else {
                
                record[s[left] - ' ' ] = 0;
                left++;
            }


        }
        return ans ;
    }
};
//使用set
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0)
            return 0;
        int left = 0;
        int right = 0;
        int ans = 0;
        set<char > sett;
        while(1) {
            if(right == s.length())
                return ans ;
            if(sett.count(s[right])==0) {
                sett.insert(s[right]);
                ans = max(ans,right - left + 1);
                right++;
            }else {
                sett.erase(s[left]);
                left++;
            }
        }
        return ans ;
    }
};
```
时间复杂度O(N)
空间复杂度与字符集大小相关


## 146
指针要初始化为nullptr<br/>
双向链表初始化要首先设置好头尾节点
put——先通过map查找已经有了没有
get——通过map找，然后移动该节点到头
```
struct Listnode {
    Listnode* pre;
    Listnode* next;
    int key;
    int val; 
    Listnode(int _key,int _val){
        key = _key;
        val = _val;
    }

};

class LRUCache {
public:
    int cur_cap;
    int cap;
    map<int ,Listnode* > mapp;
    Listnode* head;
    Listnode* tail;
    LRUCache(int capacity) {
        cur_cap = 0;
        cap = capacity;
        head = new Listnode(0,0);
        tail = new Listnode(0,0);
        head->next = tail;
        tail->pre = head;
        head->pre = nullptr;
        tail->next = nullptr;
    }
    
    void mvtohead(Listnode* cur){
        cur->next->pre = cur->pre;
        cur->pre->next = cur->next;

        cur->next = head->next;
        cur->pre = head;
        head->next->pre = cur;
        head->next = cur;

        return;

    }

    int get(int key) {
        if(mapp.find(key) != mapp.end()){
            Listnode* found = mapp[key];
            mvtohead(found);
            return found->val;
        }else {
            return -1;
        }
    }
    
    void addtohead(int key,int value){
        struct Listnode* cur = new Listnode(key,value);
        cur->next = head->next;
        cur->pre = head;

        head->next->pre = cur;
        head->next = cur;

        mapp[key] = cur;
        return;

    }

    void rmlast(){
        Listnode* last = tail->pre;
        tail->pre = tail->pre->pre;
        tail->pre->next = tail;
        
        mapp.erase(last->key);

        last->pre = nullptr;
        last->next = nullptr;
        delete last;
    }

    void put(int key, int value) {
        if(mapp.find(key) != mapp.end()){
            Listnode* found = mapp[key];
            mvtohead(found);
            found->val = value;
            return ;
        }
        if(cur_cap < cap){
            addtohead(key,value);
            cur_cap++;
        }else {
            rmlast();
            addtohead(key,value);
        }
        return;
        
    }
};

```
时间复杂度O(1)

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
        // 建堆完成后，堆顶元素就一定是最大/小的，所以，把堆顶元素取出来，再heapify，得到有序数组
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
    if (l >= r)//这里千万不能忘记!!!!
        return;  
    
    cout<<"beofre: "<<endl;
    print_arr(arr,6);
    swap(nums[rand()%(r-l+1),nums[l]]);
    int tem = partition(arr,l,r);
    cout<<tem<<"end: "<<endl;
    print_arr(arr,6);
    fast_sort(arr,l,tem-1);
    fast_sort(arr,tem+1,r);
    
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

## lc-15
先排序
双指针，把时间复杂度O(n3)降低为O(n2)
```
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        int len = nums.size();
        if(len < 3)
            return ans;
        sort(nums.begin(),nums.end());
        int ii = 0,jj = 1,kk = len-1;
        for(;ii<len-2;ii++) {
            while(ii > 0 && ii <  len-2 && nums[ii] == nums[ii-1]) ii++;
            jj = ii+1,kk = len-1;
            while(jj<kk) {
                if(jj<kk && nums[ii] + nums[jj] + nums[kk] == 0) {
                    ans.push_back({nums[ii],nums[jj],nums[kk]});
                    while(jj+1 < len-1 && jj+1 < kk && nums[jj] == nums[jj+1]) jj++;
                    jj++;
                    while(kk -1 > jj &&  nums[kk] == nums[kk-1]) kk--;
                    kk--;
                }else if(nums[ii] + nums[jj] + nums[kk] < 0){
                    jj++;
                }else {
                    kk--;
                }
            }
        }
        return ans;
    }
};
```
## lc-1
```
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> mapp;
        int len = nums.size();
        for(int i = 0;i < len ;i++) {
            if(mapp.count(target - nums[i]) != 0)
                return {i,mapp[target-nums[i]]};
            mapp[nums[i]] = i;
        }
        return {};
    }
};
```

## lc-53
dp[i]：以nums[i]结尾的最大子串和，必定包含nums[i]。
```
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
         int len = nums.size();
         int dp[len+1],ans = nums[0];
         dp[0] = nums[0];
         for(int i = 1;i < len; i++ ) {
             if(dp[i-1] > 0)
                dp[i] = dp[i-1] + nums[i];
            else 
                dp[i] = nums[i];
            ans = max(ans,dp[i]);
         }
         return ans;
    }
};
```
贪心
```
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int tem = 0,ans = INT_MIN, len = nums.size();
        for(int i = 0;i < len;i++){
            tem += nums[i];
            ans = max(ans,tem);
            if(tem < 0)
                tem = 0;
        }
        return ans;
    }
};
```


## lc-21  合并两个有序链表
```
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* l1 = list1, *l2 = list2;
        ListNode* ans = new ListNode(0);
        ListNode* l3 = ans;
        while(l1 != nullptr && l2!= nullptr) {
            if( l1->val <= l2->val){
                l3->next = l1;
                l1 = l1->next;
            }
            else {
                l3->next = l2;
                l2 = l2->next;
            }
            l3 = l3->next;
        }
        if(l1 != nullptr)
            l3->next = l1;
        if(l2 != nullptr)
            l3->next = l2;
        return ans->next;
    }
};
```
递归
```
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if(list1 == nullptr)
            return list2;
        if(list2 == nullptr)
            return list1;
        if(list1->val < list2->val) {
            list1->next = mergeTwoLists(list1->next,list2);
            return list1;
        }else {
            list2->next = mergeTwoLists(list1,list2->next);
            return list2;
        }
    }
};
```
## lc-141 环形链表
```
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head == nullptr)
            return false;
        ListNode* loww = head, *fastt = head;
        while(fastt !=nullptr && fastt->next!=nullptr && loww!=nullptr) {
            loww = loww->next;
            fastt = fastt->next->next;
            if(loww == fastt)
                return true;
        }
        return false;
    }
};
```
## lc-142
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
## lc-102. 二叉树的层序遍历
```
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        vector<vector<int> > ans;
        queue<TreeNode* > que;
        que.push(root);
        int len = 0 ;
        while(!que.empty()) {
            ans.push_back({});//同 vector <int> ()
            len = que.size();
            for(int i = 0;i<len;i++){
                auto curnode = que.front();
                que.pop();
                ans.back().push_back(curnode->val);
                if(curnode->left != nullptr)
                    que.push(curnode->left);
                if(curnode->right != nullptr)
                    que.push(curnode->right);
            }
        }
        return ans;
    }
};
```

## lc-121. 买卖股票的最佳时机
```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int minn = prices[0],res = 0;
        for(int i = 0;i<len;i++) {
            if(prices[i] - minn > res) res = prices[i] - minn;
            minn = min(prices[i],minn);
        }
        return res;
    }
};
```

## lc-122. 买卖股票的最佳时机 II
```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, len = prices.size();
        for(int i = 1;i<len;i++){
            if(prices[i] - prices[i-1] >0)
                ans+=prices[i]-prices[i-1];
        }
        return ans;
    }
};
```

## lc-123. 买卖股票的最佳时机 III

```
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        int dp[len+1][2][3];
        dp[0][0][0] = 0;dp[0][1][0] = -prices[0];
        dp[0][0][1] = INT_MIN;dp[0][1][1] = INT_MIN;
        dp[0][0][2] = INT_MIN;
        for(int i = 1;i<len;i++) {
            dp[i][0][0] = 0;
            dp[i][1][0] = max(dp[i][0][0]-prices[i],dp[i-1][1][0]);
            
            dp[i][0][1] = max(dp[i-1][0][1],dp[i][1][0]+prices[i]);
            dp[i][1][1] = max(dp[i-1][1][1],dp[i][0][1]-prices[i]);

            dp[i][0][2] = max(dp[i-1][0][2],dp[i][1][1]+prices[i]);
        }
        return max(0,max(dp[len-1][0][2],dp[len-1][0][1]));
    }
};
```

## lc-160 相交链表
两个指针从两个表头同时走，走完一个就去走另一个，最终在相交点相遇。

```
a
- - - - -
            - - -
- - - - -      c
b
a+c+b = b+c+a

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headB==nullptr || headA == nullptr)
            return nullptr;
        
        ListNode* topB = headB ,*topA = headA;
        while(headA!=headB) {
            if(headA==nullptr&&headB==nullptr)
                return nullptr;

            if(headA == nullptr)
                headA = topB;
            else 
                headA = headA->next;
            if(headB == nullptr)
                headB = topA;
            else 
                headB = headB->next;

        }
        return headA;
    }
};
```


## lc-88. 合并两个有序数组
因为``最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。``
为了不用开辟新的数组，倒序进行合并
```
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int ii = m-1, jj = n-1;
        int tt = m+n-1;
        while(ii >= 0 && jj >= 0 ) {
            if(nums1[ii] < nums2[jj]) {
                nums1[tt--] = nums2[jj--];
                continue;
            }
            else  {
                nums1[tt--] = nums1[ii--];
                continue;
            }
        }
        if(ii < 0){
            for(;jj>=0;) {
                nums1[tt--] = nums2[jj--];
            }
        } 

        return ;
    }
};
```

## lc-103. 二叉树的锯齿形层序遍历
```
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(root == nullptr) return {};
        queue<TreeNode* > que;
        vector<vector<int>> ans;
        que.push((root));int fal = 0;
        while(!que.empty()) {
            int len = que.size();
            ans.push_back({});
            for(int i = 0;i<len;i++){
                TreeNode* node = que.front();
                que.pop();
                ans.back().push_back(node->val);
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            if(fal%2==1){
                reverse(ans.back().begin(),ans.back().end());
                fal = 0;
            } else {
                fal = 1;
            }
        }
        return ans;
    }
};
```


## lc-236. 二叉树的最近公共祖先
递归：使用了函数后就可以认为已经得出结果了
lowestCommonAncestor返回，就是已经找到p或者q了
    在左右两个子树上分别找p或者q，p和q在两个子树上，那root就是最近的父节点，返回root。
    只在一个子树上找到，那就是p和q在一个子树上，返回所在的子树。
递归终止条件：如果当前节点为空或等于 p 或 q，则返回当前节点
```
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr) return nullptr;
        if(root == p || root == q) return root;
        TreeNode* leftt = lowestCommonAncestor(root->left,p,q);
        TreeNode* rightt = lowestCommonAncestor(root->right,p,q);
        if(leftt && rightt) return root;
        if(leftt) return leftt;
        if(rightt) return rightt;
        return nullptr;
    }
};
```

## lc-20. 有效的括号
但凡调用top()之前先判断空
```
class Solution {
public:
    bool isValid(string s) {
        stack<char > stk;
        int len = s.length();
        for(int i = 0;i<len;i++) {
            if(s[i] == '(' || s[i] == '{'|| s[i] == '[') stk.push(s[i]);
            else if(s[i] == ')' && !stk.empty() && stk.top() == '(') stk.pop();
            else if( s[i] == '}' && !stk.empty()  && stk.top() == '{') stk.pop();
            else if( s[i] == ']' && !stk.empty() && stk.top() == '[')  stk.pop();
            else return false;
        }
        return stk.empty();
    }
};
```

## LC-5. 最长回文子串
substr(2,3):从2开始，长度为3
"abcdefg"
substr(2,3)结果: cde
```
class Solution {
public:
    string judge(string s,int fal,int len) {
        int i = fal-1;
        while(fal+1  < len && s[fal] == s[fal+1]) fal = fal +1;
        int j = fal + 1;
        while(i>=0&&j<len&&s[i] == s[j]){
            i--;
            j++;
        } 
        return s.substr(i+1,j-i-1);
    }
    string longestPalindrome(string s) {
        int len = s.length();
        if(len<=1)return s;
        string ans,res;
        for(int i = 0;i<len;i++) {
            if(i!=0 && s[i] == s[i-1] ) continue;
            res = judge(s,i,len);
            if(res.length() > ans.length()) ans = res;
        }
        return ans;
    }
};
```



## lc-33
将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。此时有序部分用二分法查找。无序部分再一分为二，其中一个一定有序，另一个可能有序，可能无序。就这样循环.
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
                if(nums[le] <= target && target < nums[mid])//target在mid左（如果target在mid，上面就返回了），都可以动ri 
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

## lc-200. 岛屿数量
```
class Solution {
public:
    void cover(vector<vector<char>>& grid,int i,int j,int m,int n){
        if(i<0||i>=m||j<0||j>=n)
            return ;
        if(grid[i][j] == '0')return ;
        grid[i][j] = '0';
        cover(grid,i+1,j,m,n);
        cover(grid,i-1,j,m,n);
        cover(grid,i,j+1,m,n);
        cover(grid,i,j-1,m,n);
    }
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size() ,n = grid[0].size(),ans = 0;
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(grid[i][j] == '1'){
                    ans++;
                    cover(grid,i,j,m,n);
                }
            }
        }
        return ans;
    }
};

```

## lc-463. 岛屿的周长
周长就是岛屿和水的边界个数，从1到了0就计数+1
```
class Solution {
public:
    void cover(vector<vector<int>>& grid,int i,int j,int m,int n,int& ans) {
        if(i<0||j<0||i>=m||j>=n||grid[i][j] == 0){
            ans++;
            return ;
        } 
        if(grid[i][j] ==2)return ;
        grid[i][j] = 2;
        cover(grid,i+1,j,m,n,ans);
        cover(grid,i-1,j,m,n,ans);
        cover(grid,i,j+1,m,n,ans);
        cover(grid,i,j-1,m,n,ans);
    }
    int islandPerimeter(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size(),ans = 0;
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(grid[i][j] == 1){
                    cover(grid,i,j,m,n,ans);
                }
            }
        }
        return ans;
    }
};
```
另外的思路：
计算出总的岛屿数量，因为有一对相邻两个陆地，边的总数就减2，那么在计算出相邻岛屿的数量就可以了。
result = 岛屿数量 * 4 - cover * 2;


## lc-695. 岛屿的最大面积
```
class Solution {
public:
    void cover(vector<vector<int>>& grid,int i,int j,int m,int n,int& temp){
        if(i<0||j<0||i>=m||j>=n||grid[i][j]==0)
            return ;
        temp++;
        grid[i][j] = 0;
        cover(grid,i+1,j,m,n,temp);
        cover(grid,i-1,j,m,n,temp);
        cover(grid,i,j+1,m,n,temp);
        cover(grid,i,j-1,m,n,temp);
    }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0)return 0;
        int n = grid[0].size(),ans = 0,temp = 0;
        for(int i = 0;i<m;i++){
            for(int j = 0;j<n;j++){
                if(grid[i][j] == 1){
                    temp = 0;
                    cover(grid,i,j,m,n,temp);
                    ans = max(ans,temp);
                }
            }
        }
        return ans;
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