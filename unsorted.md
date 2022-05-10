## 剑指 Offer II 070. 排序数组中只出现一次的数字
暴力
```
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int i = 0,len = nums.size();
        while(i < len){
            if(i+1<len&&nums[i] == nums[i+1]){
                i+=2;
                continue;
            }
            return nums[i];
        }
        return nums[0];
    }
};
```
异或
```
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int len = nums.size();
        int ans = 0;
        for(int i = 0;i < len;i++) {
            ans ^= nums[i];
        }
        return ans;
    }
};
```
联想：排序-》二分
二分
```
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int mid = 0, l = 0, r = nums.size()-1;
        if(0 == r) return nums[0];
        while(l<=r) {
            mid = l + (r-l)/2;
            if(mid%2 == 1) mid++;
            if(nums[mid] == nums[mid + 1]) 
                l = mid + 2;
            else if(nums[mid] != nums[mid+1])
                r = mid - 2;
        }
        return nums[l];
    }
};
```

## lc-1237. 找出给定方程的正整数解
提示：x，y都1000以内，函数是增函数
枚举x，二分查找y
```

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        int l = 1,r = 1000; 
        vector<vector<int> > ans;
        for(int i = 1;i<=1000;i++) {
            l = 1,r = 1000;
            while(l<=r) {
                int mid = l + (r-l)/2;
                if(customfunction.f(i,mid) == z){
                    ans.push_back({i,mid});
                    break;
                }
                else if(customfunction.f(i,mid) < z) l = mid+1;
                else r = mid-1;
            }
        }
        return ans;
    }
};
```



## lc-450. 删除二叉搜索树中的节点
如果目标节点大于当前节点值，则去右子树中删除；
如果目标节点小于当前节点值，则去左子树中删除；
如果目标节点就是当前节点，分为以下三种情况：
    其无左子：其右子顶替其位置，删除了该节点；
    其无右子：其左子顶替其位置，删除了该节点；
    其左右子节点都有：其左子树转移到其右子树的最左节点的左子树上，然后右子树顶替其位置，由此删除了该节点。

```
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(root==nullptr) return nullptr;
        if(key < root->val) root->left = deleteNode(root->left,key);
        else if(key > root->val ) root->right = deleteNode(root->right,key);
        else {
            if(root->left == nullptr) return root->right;
            if(root->right == nullptr) return root->left;
            TreeNode* node = root->right;
            while(node->left != nullptr) node = node->left;
            node->left = root->left;
            root = root->right; 
        }
        return root;
    }
};
```
时间复杂度：O（H），H是树的高度，寻找目标节点最坏情况需要O（H），删除操作最坏情况也需要O（H）；也就是是O(logN)
空间复杂度：O（H），递归栈的深度最坏情况为树的高度；


lc-48. 旋转图像
一：找规律
1 1-》1  倒数第1列
1 2-》2 倒数第1列
1 3-》3 倒数第1列
第i行第j列的数字，经过旋转，成为第j行，倒数第i列
那就是公式：
matrix[i][j]变成了matrix[j][len-1-i]
也就是：
w = j,z = len-1-i
得出：j = w,i = len-1-z
公示：
matrix_new[w][z] = matrix[len-1-z][w]
```
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        vector<vector<int> > matrix2 = matrix;
        int len = matrix.size();
        for(int i = 0;i<len;i++){
            for(int j = 0;j<len;j++){
                matrix2[i][j] = matrix[len - 1 -j][i];
            }
        }
        matrix = matrix2;
        return ;
    }
};
```
二、原地修改：
临时存一下matrix[i][j]
temp = matrix[i][j];
matrix[i][j] = matrix[len-1-j][i];
matrix[len-1-j][i] = matrix[len-1-i][len-1-j];
matrix[len-1-i][len-1-j] = matrix[j][len-1-i];
matrix[j][len-1-i] = temp;
那些位置需要旋转呢？
n*n的矩阵：
n为偶数，只需要1/4块的位置旋转，n^2/4 = (n/2)*(n/2)
n为奇数，中心不动，剩下 (n^2-1)/4 = (n+1)/2*(n-1)/2
三、矩阵转置代替旋转
只需要上下翻转，再转置即可


lc-124. 二叉树中的最大路径和
需要更新ans的
所有情况：左 右 父
        左 父
        右 父
        父
```
class Solution {
public:
    int ans = INT_MIN;//保证至少有一个点
    int findd(TreeNode* root) {
        if(!root) return 0;
        int leftt = findd(root->left);
        int rightt = findd(root->right);
        int tem = root->val + max(0,leftt) + max(0,rightt);
        ans = max(ans,tem);

        return root->val+max(max(0,leftt),max(0,rightt));
    }
    int maxPathSum(TreeNode* root) {
        findd(root);
        return ans;
    }
};
```
lc-151. 翻转字符串里的单词



lc-543. 二叉树的直径
左右子树深度只和
```
class Solution {
public:
    int ans = 0;
    int findd(TreeNode* root) {
        if(root == nullptr) return 0;
        int leftt = findd(root->left);
        int rightt = findd(root->right);
        ans = max(ans,leftt+rightt);
        return 1+max(leftt,rightt);
    }
    int diameterOfBinaryTree(TreeNode* root) {
        findd(root);
        return ans;
    }
};
```

lc-32. 最长有效括号
两周情况: "()()()" "()((()))"
动态规划: dp[i]表示以i结尾的最长有效括号长度
遇到')'，分别判断两周情况。
1、dp[i] = dp[i-2]+2                                if s[i-1]=='('
2、dp[i] = dp[i - dp[i-1] - 2] + dp[i-1] + 2        if s[i-1]==')'
```
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length(),ans = 0;
        //int dp[len+2];memset(dp,0,sizeof(int)*len);
        vector<int > dp(len+2,0);//尽量用vector，而不是数组
        for(int i = 0;i<len;i++){
            if(s[i] == ')'){
                if(i == 0) continue;
                if(s[i-1] == '('){
                    dp[i] += 2;
                    if(i-2>=0)
                        dp[i] += dp[i-2];
                }
                if(s[i-1] == ')')  {
                    if(i - dp[i-1] - 1>=0&&s[i - dp[i-1] - 1] == '('){
                        dp[i] = dp[i-1] + 2;
                        if(i - dp[i-1] - 2>=0)
                            dp[i] +=  + dp[i - dp[i-1] - 2];
                    }
                }
            }
            ans = max(ans,dp[i]);
        }
        return ans; 
    }
};
```

lc-151. 翻转字符串里的单词
```
class Solution {
public:
    string reverseWords(string s) {
        int len = s.length();
        stack<string> stk;
        int j = 0;
        for(int i = 0;i<len;i++){
            if(s[i] == ' ')continue;
            j = i;
            while(j<len&&s[j]!=' ') j++;
            stk.push(s.substr(i,j-i));
            i = j;
        }
        s = "";
        while(!stk.empty()){
            s+=stk.top();
            stk.pop();
            if(!stk.empty()) s+=" ";
        }
        return s;
    }
};
```
如果不借助额外空间，需要忽略多余空格，先翻转整个字符串，再翻转每个单词。用双指针

lc-46. 全排列
```
class Solution {
public:
    vector<vector<int > > ans;
    void trave( vector<int>& nums,vector<int >& thiss,vector<int >& rec,int len) {
        if(thiss.size() == len) {
            ans.push_back(thiss);
            return;
        }
        for(int i=0;i<len;i++) {
            if(rec[i]==0) {
                rec[i] = 1;
                thiss.push_back(nums[i]);
                trave(nums,thiss,rec,len);
                thiss.pop_back();
                rec[i] = 0;
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        //int rec[len];memset(rec, 0, sizeof(int )*len);
        vector<int> rec(len,0);
        vector<int > thiss;
        trave(nums,thiss,rec,len);
        return ans;
    }
};
```
### lc-47. 全排列 II
比46加了去重的步骤，就是先sort一下，每次选数的时候，要选的nums[i]和nums[i-1]重复，并且nums[i-1]没有使用，就跳过
```
class Solution {
public:
    int len = 0;
    void findd(vector<int> nums,int pos,vector<int>& cur,vector<vector<int>>& ans,vector<int>& vis) {
         if(pos == len) {
             ans.push_back(cur);
             return ;
         }
         if(pos>len) return;
         for(int i =0;i<len;i++) {
             if(vis[i] == 0 && !(i!= 0 &&nums[i] == nums[i-1] && vis[i-1] == 0)){
                cur[pos] = nums[i];
                vis[i] = 1;
                findd(nums,pos+1,cur,ans,vis);
                vis[i] = 0;
             }
         }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        len = nums.size();
        vector<vector<int>> ans;
        sort(nums.begin(),nums.end());
        vector<int> vec(len,0);
        vector<int> vis(len,0);
        findd(nums,0,vec,ans,vis);
        return ans;
    }
};
```


lc-560. 和为 K 的子数组
数组中找和为K的子数组的个数
枚举O(n^2)

前缀和+哈希查找

由于只关心次数，不关心具体的解，我们可以使用哈希表加速运算；
由于保存了之前相同前缀和的个数，计算区间总数的时候不是一个一个地加，时间复杂度降到了 O(N)O(N)。

```
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        map<int,int> mapp;
        mapp[0] = 1;
        int presum = 0 ,ans = 0 ,len = nums.size();
        for(int i = 0;i<len;i++) {
            presum += nums[i];
            if(mapp.count(presum - k) != 0)
                ans+=mapp[presum - k];
            mapp[presum]++;
        }
        return ans;
    }
};
```
找个数多题目-》使用map

lc-1248. 统计「优美子数组」
```
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int len = nums.size(), presum = 0,ans = 0;
        map<int ,int> mapp;
        mapp[0] = 1;
        for(int i = 0;i<len;i++) {
            if(nums[i]%2 == 1) presum++;
            if(mapp.count(presum-k)) ans+=mapp[presum-k];
            mapp[presum]++;
        }
        return ans;
    }
};
```
lc-1 两数之和

lc-454. 四数相加 II
```
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        int len1 = nums1.size(), len2 = nums2.size(), len3 = nums3.size(), len4 = nums4.size(),ans = 0,presum = 0;
        map<int,int> mapp,mapp2;
        for(int i = 0;i<len1;i++) {
            for(int j = 0;j<len2;j++) {
                mapp[(nums1[i] + nums2[j])]++;
            }
        }
        for(int i = 0;i<len3;i++){
            for(int j = 0;j<len4;j++) {
                presum = -nums3[i] - nums4[j];
                if(mapp.count(presum)) ans+=mapp[presum];
            }
        }
        return ans;
    }
};
```

## lc-109. 有序链表转换二叉搜索树
```
/**
class Solution {
public:
    ListNode* getmidd(ListNode* leftt,ListNode* rightt) {
        ListNode* sloww = leftt;
        ListNode* fastt = leftt;
        while(fastt != rightt && fastt->next != rightt) {
            fastt = fastt->next;
            fastt = fastt->next;
            sloww = sloww->next;
        }
        return sloww;
    }
    TreeNode* buildd(ListNode* leftt,ListNode* rightt) {
        if(leftt == rightt) {
            return nullptr;
        }
        ListNode* midd =   getmidd(leftt , rightt);
        TreeNode* middd = new TreeNode(midd->val);
        
        middd->left = buildd(leftt,midd);
        middd->right = buildd(midd->next,rightt);
        return middd;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        return buildd(head,nullptr);
    }
};
```

## lc-22. 括号生成
简单回溯 ，dfs
```
class Solution {
public:
    vector<string> ans;
    void findd(string tem,int llef,int rlef,int n) {
        if(llef == 0 && rlef == 0) {
            ans.push_back(tem);
        }
        if(llef > 0) {
            findd(tem+'(',llef-1,rlef,n);
        }
        if(rlef > llef) {
            findd(tem+')',llef,rlef-1,n);
        }
    }
    vector<string> generateParenthesis(int n) {
        string tem;
        findd(tem,n,n,n);
        return ans;
    }
};
```
BFS
```
struct nodee {
    int llef;
    int rlef;
    string str;
    nodee(int l,int r,string s):llef(l),rlef(r),str(s){}
};
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        queue<nodee* > que;
        vector<string> ans;
        nodee* no = new nodee(n,n,"");
        que.push(no);
        while(!que.empty()) {
            nodee* tem = que.front();
            que.pop();
            if(tem->llef == 0 && tem->rlef == 0)ans.push_back(tem->str);
            if(tem->llef > 0){
                que.push(new nodee(tem->llef-1,tem->rlef,tem->str+'('));
            }
            if(tem->rlef > tem->llef){
                que.push(new nodee(tem->llef,tem->rlef-1,tem->str+')'));
            }
        }
        return ans;
    }
};
```

## lc-11. 盛最多水的容器
```
class Solution {
public:
    int maxArea(vector<int>& height) {
        int len = height.size();
        int i = 0, j = len-1,ans = 0;
        while(i < j) {
            ans = max(ans,(j-i) * min(height[i],height[j]));
            if(height[i] < height[j]) {
                i++;
            }else {
                j--;
            }
        }
        return ans;
    }
};
```


## lc-207. 课程表
拓扑排序
有向图中，判断有没有环
把入度为0的进入队列，挨个出队遍历边，更新入度，一旦为0，入队，知道队列为空。
判断还有没有入度不为0的点
```
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        queue<int> que;
        map<int,int> into;
        vector< vector<int> > vec(numCourses);
        for(int i = 0;i<prerequisites.size();i++) {
            into[prerequisites[i][0]]++;
            vec[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        for(int i = 0;i<numCourses;i++) {
            if(into[i] == 0) {
                que.push(i);
            }
        }
        while(!que.empty()) {
            int tem = que.front();
            que.pop();
            for(int i=0;i<vec[tem].size();i++) {
                into[vec[tem][i]]--;
                if(into[vec[tem][i]] == 0) que.push(vec[tem][i]);
            }
        }
        for(int i = 0;i<numCourses;i++) {
            if(into[i] > 0)return false;
        }
        return true;
    }
};
```

## 二叉树中序遍历
一直循环放入左子树，左空了就从栈中拿出来一个，放入ans，然后右子树
```
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode* > stk;
        TreeNode* ptr = root;
        vector<int> ans;
        while(ptr || !stk.empty()) {
            while(ptr) {
                stk.push(ptr);
                ptr = ptr->left;
            }
            ptr = stk.top();
            stk.pop();
            ans.push_back(ptr->val);
            ptr = ptr->right;
        }
        return ans;
    }
};
```
## 二叉树前序遍历
和中序遍历差不多，只不过在循环左子树的时候，就放入到ans。
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode* > stk;
        TreeNode* ptr = root;
        vector<int> ans;
        while(ptr || !stk.empty()) {
            while(ptr) {
                stk.push(ptr);
                ans.push_back(ptr->val);
                ptr = ptr->left;
            }
            ptr = stk.top();
            stk.pop();
            ptr = ptr->right;
        }
        return ans;
    }
};

## 二叉树后序遍历
相比于先续遍历：中左右
我们只需要改一下左右：中右左，然后反转一下ans就行了
```
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* ptr = root;
        vector<int> ans;
        while(ptr || !stk.empty()) {
            while(ptr) {
                ans.push_back(ptr->val);
                stk.push(ptr);
                ptr = ptr->right;
            }
            ptr = stk.top();
            stk.pop();
            ptr = ptr->left;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
```
## 108. 将有序数组转换为二叉搜索树
```
class Solution {
public:
    TreeNode* numsToTree(vector<int>& nums,int l ,int r) {
        if(l>r) return nullptr;
        int mid = (l+r)/2;
        TreeNode* nodee = new TreeNode(nums[mid]);
        nodee->left = numsToTree(nums,l,mid-1);
        nodee->right = numsToTree(nums,mid+1,r);
        return nodee;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int len = nums.size();
        return numsToTree(nums,0,len-1);
    }
};
```


PMU tools
vtune




class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param matrix int整型vector<vector<>> 
     * @return int整型vector
     */
    vector<int> antiSpiralOrder(vector<vector<int> >& matrix) {
        int lenM = matrix.size(), lenN = matrix[0].size();
        vector<int> ans;
        for(int i = 0;i<lenM/2;i++) {
            for(int j = 0;j<lenN;j++)
                swap(matrix[i][j], matrix[lenM-i-1][j]);
        }
        for(int i = 0;i<lenM;i++) {
            for(int j = 0;j<i;j++)
                swap(matrix[i][j], matrix[j][i]);
        }
        
        int upp = 0, doww = lenN-1, le = 0, ri = lenM-1;
        while(1) {
            for(int i = upp;i<=doww&&i<lenN;i++)
                ans.push_back(matrix[i][le]);
            le++;
            if(le>ri)break;
            for(int i = le;i<=ri&&i<lenM;i++)
                ans.push_back(matrix[doww][i]);
            doww--;
            if(doww<upp)break;
            for(int i = doww;i>=upp&&i>=0;i--)
                ans.push_back(matrix[i][ri]);
            ri--;
            if(ri<le) break;
            for(int i= ri;i>=le&&i>=0;i--)
                ans.push_back(matrix[upp][i]);
            upp++;
            if(upp>doww)break;
        }
        return ans;
    }
};



/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param preSlice int整型vector 先序遍历结果数组
     * @return TreeNode类
     */
    TreeNode* findd(int le,int ri,vector<int> preSlicee) {
        if(le>ri) return nullptr;
        int tem = le, len = preSlicee.size();
        for(tem = le+1;tem<len;tem++) {
            if(preSlicee[tem] > preSlicee[le]) {
                break;
            }
        }
        TreeNode* root = new TreeNode(preSlicee[le]);
        root->left = findd(le+1, tem-1, preSlicee);
        root->right = findd(tem, ri, preSlicee);
        return root;
    }
    TreeNode* reConstructBST(vector<int>& preSlice) {
        int len = preSlice.size();
        return findd(0,len-1,preSlice);
    }
};


class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 整形数组
     * @return int整型
     */
    int longestGeometricSeqLength(vector<int>& nums) {
        int len = nums.size();
        int dp[len][len];
        int ans = 0;
        vector<map<int,int>> tem(len);
        for(int i = 0;i<len;i++) {
            for(int j = 0;j<i;j++){
                int ddd = nums[i]/nums[j];
                if(ddd*nums[j] != nums[i]) continue;
                if(tem[j][ddd]){
                    tem[i][ddd] = tem[j][ddd]+1;
                }else{
                    tem[i][ddd] = 2;
                }
                ans = max(ans,tem[i][ddd]);
            }
        }
        return ans;
    }
};