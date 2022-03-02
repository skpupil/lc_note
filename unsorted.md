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