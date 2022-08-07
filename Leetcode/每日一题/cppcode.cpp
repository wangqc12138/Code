#include "head.h"
/*
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
27
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    	//双指针
    	int j=0;
    	for(int i=0;i<nums.size();i++){
    		if(nums[i]!=val){
    			nums[j++]=nums[i];
    		}
    	}
    	return j;

    }
};
/*
实现 strStr() 函数。
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。
KMP算法
*/
class Solution {
public:
    int strStr(string haystack, string needle) {
        int m=needle.size(),n=haystack.size(),j=0,i=1;
        vector<int> next(m,0);
        //填入next数组
        for(;i<m;i++){
            while(needle[i]!=needle[j]){
                if(j==0){
                    next[i]=0;
                    break;
                }else{
                    j=next[j-1];
                }
            }
            if(needle[i]==needle[j]){
                next[i]=++j;
            }
        }
        //利用next数组比较
        i=0,j=0;
        while(i<n&&j<m){
            if(needle[j]==haystack[i]){
                i++;
                j++;
            }else if(j==0){
                i++;
            }
            else{
                j=next[j-1];
            } 
        }
        return j!=m?-1:i-m;
    }
};
/*
一条包含字母 A-Z 的消息通过以下映射进行了 编码 ：

'A' -> 1
'B' -> 2
...
'Z' -> 26

要 解码 已编码的消息，所有数字必须基于上述映射的方法，反向映射回字母（可能有多种方法）。例如，"11106" 可以映射为：

    "AAJF" ，将消息分组为 (1 1 10 6)
    "KJF" ，将消息分组为 (11 10 6)

注意，消息不能分组为  (1 11 06) ，因为 "06" 不能映射为 "F" ，这是由于 "6" 和 "06" 在映射中并不等价。

给你一个只含数字的 非空 字符串 s ，请计算并返回 解码 方法的 总数 。

题目数据保证答案肯定是一个 32 位 的整数。
91
*/
class Solution {
public:
    int numDecodings(string s) {
        int n=s.size();
        vector<int> dp(n+1);//下标可以理解为字符串长度
        dp[0]=1;//空字符有一种解码方法
        for(int i=1;i<=n;i++){
            if(s[i-1]!='0'){//当前所指不为‘0’，则为前一个长度的总数
                dp[i]=dp[i-1];
            }
            if(i>1&&s[i-2]!='0'&&10*(s[i-2]-'0')+s[i-1]-'0'<=26){//可以与前一个字符映射
                dp[i]+=dp[i-2];
            }
        }
        return dp[n];
    }
};

/*
给你一个 m x n 的矩阵 matrix 和一个整数 k ，找出并返回矩阵内部矩形区域的不超过 k 的最大数值和。

题目数据保证总会存在一个数值和不超过 k 的矩形区域。
363
*/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int m=matrix.size(),n=matrix[0].size(),res=INT_MIN;
        int sumMatrix[m][n];
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i>0&&j>0){
                    sumMatrix[i][j]=sumMatrix[i-1][j]+sumMatrix[i][j-1]-sumMatrix[i-1][j-1]+matrix[i][j];
                }else if(i>0){
                    sumMatrix[i][j]=sumMatrix[i-1][j]+matrix[i][j];
                }else if(j>0){
                    sumMatrix[i][j]=sumMatrix[i][j-1]+matrix[i][j];
                }else{
                    sumMatrix[i][j]=matrix[i][j];
                }
            }
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                for(int a=i;a<m;a++){
                    for(int b=j;b<n;b++){
                        int sum=0;
                        if(i==0&&j==0){
                            sum=sumMatrix[a][b];
                        }else if(i==0){
                            sum=sumMatrix[a][b]-sumMatrix[a][j-1];
                        }else if(j==0){
                            sum=sumMatrix[a][b]-sumMatrix[i-1][b];
                        }else{
                            sum=sumMatrix[a][b]-sumMatrix[a][j-1]-sumMatrix[i-1][b]+sumMatrix[i-1][j-1];
                        }
                        if(sum<k){
                            res=max(res,sum);
                        }else if(sum==k){
                            return k;
                        }
                    }
                }
            }
        }
        return res;
    }
};
/*
给你一个由 无重复 正整数组成的集合 nums ，请你找出并返回其中最大的整除子集 answer ，子集中每一元素对 (answer[i], answer[j]) 都应当满足：

    answer[i] % answer[j] == 0 ，或
    answer[j] % answer[i] == 0

如果存在多个有效解子集，返回其中任何一个均可。
368
*/
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n=nums.size(),maxVal,maxSize=1;
        vector<int> dp(n,1),res;
        sort(nums.begin(),nums.end());
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(nums[i]%nums[j]==0){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
            if(dp[i]>maxSize){
                maxSize=dp[i];
                maxVal=nums[i];
            }
        }
        if(maxSize==1){
            return vector<int>{nums[0]};
        }
        for(int i=n-1;i>=0&&maxSize>0;i--){
            if(dp[i]==maxSize&&maxVal%nums[i]==0){
                res.push_back(nums[i]);
                maxSize--;
                maxVal=nums[i];
            }
        }
        return res;
    }
};
//20210424
/*
给你一个由不同整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
377
*/
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        
    }
};
//20210425
/*
给你一棵二叉搜索树，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。
897
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* dum=new TreeNode(0);
    TreeNode* increasingBST(TreeNode* root) {
        TreeNode* res=dum; 
        inorder(root);
        return res->right;
    }
    void inorder(TreeNode *root){
        if(root==nullptr){
            return;
        }
        inorder(root->left);
        dum->right=root;
        root->left=nullptr;
        dum=root;
        inorder(root->right);
    }
};
//20210426
/*
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
1011
*/
//二分
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n=weights.size();
        int left=*max_element(weights.begin(),weights.end());
        int right=accumulate(weights.begin(),weights.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int temp=0,day=1;
            for(int w:weights){
                temp+=w;
                if(temp>mid){
                    day++;
                    temp=w;
                }
            }
            if(day>D){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/*
给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。
938
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int res=0;
    int rangeSumBST(TreeNode* root, int low, int high) {
        inorder(root,low,high);
        return res;
    }
    void inorder(TreeNode* root,int low, int high){
        if(root==nullptr){
            return;
        }
        inorder(root,low,high);
        if(root->val>=low&&root->val<=high){
            res+=root->val;
        }
        inorder(root,low,high);
    }
};
/* 
给定一个非负整数 c ，你要判断是否存在两个整数 a 和 b，使得 a2 + b2 = c 。
633
0 <= c <= 231 - 1
不能用int 会超出int范围
相当于在一个矩阵中找值
矩阵行递增，列递增
*/
class Solution {
public:
    bool judgeSquareSum(int c) {
        long long left=0,right=(int)sqrt(c);
        while(left<=right){
            long long tmp=left*left+right*right;
            if(tmp==c){
                return true;
            }else if(tmp>c){
                right--;
            }else{
                left++;
            }
        }
        return false;
    }
};
/* 
你的面前有一堵矩形的、由 n 行砖块组成的砖墙。这些砖块高度相同（也就是一个单位高）但是宽度不同。每一行砖块的宽度之和相等。

你现在要画一条 自顶向下 的、穿过 最少 砖块的垂线。如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。

给你一个二维数组 wall ，该数组包含这堵墙的相关信息。其中，wall[i] 是一个代表从左至右每块砖的宽度的数组。
你需要找出怎样画才能使这条线 穿过的砖块数量最少 ，并且返回 穿过的砖块数量 。
554
 */
class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        map<int,int> m;
        int n=wall.size();
        for(auto vec:wall){
            int k=0;
            for(auto i:vec){
                k+=i;
                m[k]++;
            }
            m.erase(k);
        }
        int res=n;
        /* for(auto [i,j]:m){
            //min函数不能包含size()?
            res=min(res,n-j);
        } */
        for(auto itr:m){
            res=min(res,n-itr.second);
        }
        return res;
    }
};
/* 
给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。

如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
假设环境不允许存储 64 位整数（有符号或无符号）。
7
 */
class Solution {
public:
    int reverse(int x) {
        long long res=0;
        while(x){
            res=res*10+x%10;
            x/=10;
        }
        return res==(int)res?res:0;
    }
};
/* 
给你一个整数数组 nums ，你可以对它进行一些操作。
每次操作中，选择任意一个 nums[i] ，删除它并获得 nums[i] 的点数。之后，你必须删除 所有 等于 nums[i] - 1 和 nums[i] + 1 的元素。
开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。
740
    1 <= nums.length <= 2 * 104
    1 <= nums[i] <= 104
 */
// 打家劫舍的变种，即选择抢一家就不能抢邻居
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int k=*max_element(nums.begin(),nums.end());
        vector<int> vec(k+1,0);
        for(int i:nums){
            vec[i]=i;
        }
        vector<int> dp(k+1);
        for(int i=2;i<k+1;i++){
            if(i==0){
                dp[i]=nums[i];
            }else if(i==1){
                dp[i]=max(dp[0],dp[1]);
            }else{
                dp[i]=max(dp[i-1],dp[i-2]+nums[i]);
            }
        }
        return dp[k];
    }
};
/* 
给你两个整数，n 和 start 。

数组 nums 定义为：nums[i] = start + 2*i（下标从 0 开始）且 n == nums.length 。

请返回 nums 中所有元素按位异或（XOR）后得到的结果。
1486
 */
class Solution {
public:
    int xorOperation(int n, int start) {
        int res=start;
        for(int i=1;i<n;i++){
            res^=(start+2*i);
        }
        return res;
    }
};
/* 
给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。
请你将这些工作分配给 k 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。
工人的 工作时间 是完成分配给他们的所有工作花费时间的总和。请你设计一套最佳的工作分配方案，使工人的最大工作时间得以最小化 。
返回分配方案中尽可能最小的最大工作时间 。
1723
 */
class Solution {
public:
    int minimumTimeRequired(vector<int>& jobs, int k) {
        sort(jobs.begin(),jobs.end());
        int left=jobs.back();
		int right=accumulate(jobs.begin(),jobs.end(),0);
		while(left<right){
			int mid=left+(right-left)/2;
			if(!check(jobs,mid,k)){
				left=mid+1;
			}else{
				right=mid;
			}
		}
		return left;
    }
	bool check(vector<int>& jobs,int target,int k){
		vector<int> works(k,0);
		return dfs(jobs,works,target,0);
	}
	bool dfs(vector<int>& jobs,vector<int> &works,int target,int index){
		if(index>=jobs.size()){
			return true;
		}
		int cur=jobs[index];
		for(auto &work:works){
			if(work+cur<=target){
				work+=cur;
				if(dfs(jobs,works,target,index+1)){
                    return true;
                }
				work-=cur;
			}
			if(work==0){
				break;
			}
		}
		return false;
	}
};
//以下为两个子问题
/*
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
1011
*/
//二分
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n=weights.size();
        int left=*max_element(weights.begin(),weights.end());
        int right=accumulate(weights.begin(),weights.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int temp=0,day=1;
            for(int w:weights){
                temp+=w;
                if(temp>mid){
                    day++;
                    temp=w;
                }
            }
            if(day>D){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/* 
给定一个整数数组  nums 和一个正整数 k，找出是否有可能把这个数组分成 k 个非空子集，其总和都相等。
698
 */
class Solution {
public:
	vector<int> visit;
	bool res=false;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int sum=accumulate(nums.begin(),nums.end(),0);
		if(sum%k){
			return false;
		}
		visit.resize(nums.size());
		dfs(nums,k,sum/k,0,0);
		return res;
    }
	void dfs(vector<int>& nums,int k,int target,int sum,int index){
		if(k==1){
			res=true;
			return;
		}
		if(target==sum){
			dfs(nums,k-1,target,0,0);
		}
		for(int i=index;i<nums.size();i++){
            //剪枝，去除与前一个相同但是前一个没取过的。去重
            if(i>0&&nums[i]==nums[i-1]&&visit[i-1]==0){
                continue;
            }
			if(visit[i]==0&&sum+nums[i]<=target){
				visit[i]=1;
				dfs(nums,k,target,sum+nums[i],i+1);
				visit[i]=0;
			}
		}
	}
};

/* 
给你一个整数数组 bloomDay，以及两个整数 m 和 k 。

现需要制作 m 束花。制作花束时，需要使用花园中 相邻的 k 朵花 。

花园中有 n 朵花，第 i 朵花会在 bloomDay[i] 时盛开，恰好 可以用于 一束 花中。

请你返回从花园中摘 m 束花需要等待的最少的天数。如果不能摘到 m 束花则返回 -1 。
1482
bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n
 */
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if(m*k>bloomDay.size()){
            return -1;
        }
        int left=1,right=*max_element(bloomDay.begin(),bloomDay.end());
        auto check=[&](int n){
            vector<int> now(bloomDay.size());
            for(int i=0;i<bloomDay.size();++i){
                now[i]=bloomDay[i]<=n?1:0;
            }
            int l=0,ans=0;
            for(int i:now){
                if(i==1){
                    l++;
                }else{
                    l=0;
                }
                if(l==k){
                    ans++;
                    l=0;
                }
            }
            //当可以拿到的花大于m也行
            return ans>=m;
        };
        while(left<right){
            int mid=left+(right-left)/2;
            if(check(mid)){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};

/* 
请考虑一棵二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。
如果有两棵二叉树的叶值序列是相同，那么我们就认为它们是 叶相似 的。
如果给定的两个根结点分别为 root1 和 root2 的树是叶相似的，则返回 true；否则返回 false 。
 */
class Solution {
public:
    bool leafSimilar(TreeNode* root1, TreeNode* root2) {
        vector<int> l1;
		getleaf(root1,l1);
		for(int i:l1){
			cout<<i<<" ";
		}
		return 0;
    }
	void getleaf(TreeNode* root,vector<int> &vec){
		if(root->left==nullptr&&root->right==nullptr){
			vec.push_back(root->val);
		}
		if(root==nullptr){
			return;
		}
		getleaf(root->left,vec);
		getleaf(root->right,vec);
	}
};
/* 
给你一个整数数组 perm ，它是前 n 个正整数的排列，且 n 是个 奇数 。
它被加密成另一个长度为 n - 1 的整数数组 encoded ，满足 encoded[i] = perm[i] XOR perm[i + 1] 。
比方说，如果 perm = [1,3,2] ，那么 encoded = [2,1] 。
给你 encoded 数组，请你返回原始数组 perm 。题目保证答案存在且唯一。
1734
 */
class Solution {
public:
    vector<int> decode(vector<int>& encoded) {
		int n=encoded.size()+1;
		int t;
		for(int i=1;i<=n;i++){
			t^=i;
		}
		for(int i=1;i<n-1;i+=2){
			t^=encoded[i];
		}
		vector<int> res(n,t);
		for(int i=1;i<n;i++){
			res[i]=encoded[i-1]^res[i-1];
		}
		return res;
    }
};
/* 
有一个正整数数组 arr，现给你一个对应的查询数组 queries，其中 queries[i] = [Li, Ri]。

对于每个查询 i，请你计算从 Li 到 Ri 的 XOR 值（即 arr[Li] xor arr[Li+1] xor ... xor arr[Ri]）作为本次查询的结果。

并返回一个包含给定查询 queries 所有结果的数组。
1310
 */
class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        vector<int> prefix;
        vector<int> res;
        int t=0;
        for(int i:arr){
            prefix.push_back(t^=i);
        }
        for(auto vec:queries){
            if(vec[0]==0){
                res.push_back(prefix[vec[1]]);
            }else{
                res.push_back(prefix[vec[1]]^prefix[vec[0]-1]);
            }
        }
        return res;
    }
};
/* 
有一个长度为 arrLen 的数组，开始有一个指针在索引 0 处。
每一步操作中，你可以将指针向左或向右移动 1 步，或者停在原地（指针不能被移动到数组范围外）。
给你两个整数 steps 和 arrLen ，请你计算并返回：在恰好执行 steps 次操作以后，指针仍然指向索引 0 处的方案数。
由于答案可能会很大，请返回方案数 模 10^9 + 7 后的结果。
1269
 */
class Solution {
public:
    int numWays(int steps, int arrLen) {
		int maxLen=min(steps,arrLen-1);
		vector<vector<int>> dp(steps+1,vector<int>(maxLen+1));
		dp[0][0]=1;
		for(int i=1;i<=steps;i++){
			for(int j=0;j<=maxLen;j++){
				if(j==0){
					dp[i][j]=dp[i-1][j]+dp[i-1][j+1];
				}else if(j==arrLen-1){
					dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
				}else{
					dp[i][j]=dp[i-1][j-1]+dp[i-1][j]+dp[i-1][j+1];
				}
				
			}
		}
		return dp[steps][0];
    }
};
/* 
罗马数字包含以下七种字符： I， V， X， L，C，D 和 M。
通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。
数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
    I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
    X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
    C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给你一个整数，将其转为罗马数字。
1 <= num <= 3999
12
 */
class Solution {
public:
    string intToRoman(int num) {
		string res;
		vector<string> str={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
		vector<int> nums={1000,900,500,400,100,90,50,40,10,9,5,4,1};
		for(int i=0;i<nums.size();i++){
			while(num){
				if(num>=nums[i]){
					res+=str[i];
					num-=nums[i];
				}else{
					break;
				}
			}
		}
		return res;
    }
};
/* 
罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
13
 */
class Solution {
public:
    int romanToInt(string s) {
        int n=0,pre=0,res=0;
        for(auto c:s){
            switch(c){
                case 'I': n=1; break;
                case 'V': n=5; break;
                case 'X': n=10; break;
                case 'L': n=50; break;
                case 'C': n=100; break;
                case 'D': n=500; break;
                case 'M': n=1000; break;
            }
            if(n>pre){
                res-=2*pre;
            }
            res+=n;
            pre=n;
        }
        return res;
    }
};
/* 
给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j < n 。
进阶：你可以在 O(n) 的时间解决这个问题吗？
421
字典树--0、1
*/
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
		int res=0;
		Trie* root=new Trie();
		for(int i:nums){
			root->add(i);
			int m=root->getMaxXor(i);
			res=max(res,m);
		}
		return res;
    }
};
class Trie{
public:
	Trie(){
		next.clear();
		next.resize(2);
		isEnd=false;
	}
	void add(int n){
		Trie *root=this;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;//获取最低位
			if(root->next[k]==nullptr){
				Trie* node=new Trie;
				root->next[k]=node;
			}
			root=root->next[k];
		}
		root->isEnd=true;
	}
	int getMaxXor(int n){
		Trie *root=this;
		int res=0;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k==0){
				if(root->next[1]!=nullptr){
					root=root->next[1];
					res+=(1<<i);
				}else{
					root=root->next[0];
				}
			}else{
				if(root->next[0]!=nullptr){
					root=root->next[0];
					res+=(1<<i);
				}else{
					root=root->next[1];
				}
			}
		}
		return res;
	}
private:
	vector<Trie*> next;
	bool isEnd;
};
/*
在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。
如果二叉树的两个节点深度相同，但 父节点不同 ，则它们是一对堂兄弟节点。
我们给出了具有唯一值的二叉树的根节点 root ，以及树中两个不同节点的值 x 和 y 。
只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true 。否则，返回 false。
993
*/
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
		int xf,yf,xd,yd,d=0;
        dfs(root,x,y,xf,xd,yf,yd,d);
		return xf!=yf&&xd==yd;
    }
	void dfs(TreeNode* root,int x,int y,int& xf,int& xd,int& yf,int& yd,int d){
		if(root==nullptr){
			return;
		}
		d++;
		if(root->left){
			if(root->left->val==x){
				xf=root->val;
				xd=d;
			}
			if(root->left->val==y){
				yf=root->val;
				yd=d;
			}
			dfs(root->left,x,y,xf,xd,yf,yd,d);
		}
		if(root->right){
			if(root->right->val==x){
				xf=root->val;
				xd=d;
			}
			if(root->right->val==y){
				yf=root->val;
				yd=d;
			}
			dfs(root->right,x,y,xf,xd,yf,yd,d);
		}

	}
};
//BFS
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        queue<TreeNode*> q;
		q.push(root);
		while(!q.empty()){
			int n=q.size(),index=-1;
			bool flag=false;
			for(int i=0;i<n;i++){
				TreeNode* node=q.front();
				q.pop();
				if(node==nullptr){
					continue;
				}
				if(node->val==x||node->val==y){
					if(index==-1){
						index=i;
					}else if(i-index>1||(i==index+1&&i%2==0)){
						return true;
					}
				}
				q.push(node->left);
				q.push(node->right);
			}
			if(index==1){
				return false;
			}	
		}
		return false;
    }
};
/* 
给你一个整数数组 arr 。
现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。
a 和 b 定义如下：
    a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
    b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
注意：^ 表示 按位异或 操作。
请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。
 */
//前缀异或
class Solution {
public:
    int countTriplets(vector<int>& arr) {
		int res=0;
		vector<int> preXor(arr.size()+1,0);
		for(int i=0;i<arr.size();i++){
			preXor[i+1]=preXor[i]^arr[i];
		}
		for(int i=0;i<arr.size();i++){
			for(int j=i+1;j<arr.size();j++){
				for(int k=j;k<arr.size();k++){
					if(preXor[i]==preXor[k+1]){
						res++;
					}
				}
			}
		}
		return res;
    }
};
class Solution {
public:
    int countTriplets(vector<int>& arr) {
		int res=0;
		vector<int> preXor(arr.size()+1,0);
		for(int i=0;i<arr.size();i++){
			preXor[i+1]=preXor[i]^arr[i];
		}
		for(int i=0;i<arr.size();i++){
			for(int k=i+1;k<arr.size();k++){
				if(preXor[i]==preXor[k+1]){
					res+=k-i;
				}
			}
		}
		return res;
    }
};
//还有一重循环的，！
/* 
给你一个二维矩阵 matrix 和一个整数 k ，矩阵大小为 m x n 由非负整数组成。

矩阵中坐标 (a, b) 的 值 可由对所有满足 0 <= i <= a < m 且 0 <= j <= b < n 的元素 matrix[i][j]（下标从 0 开始计数）执行异或运算得到。

请你找出 matrix 的所有坐标中第 k 大的值（k 的值从 1 开始计数）。
1738
 */
class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
		int m=matrix.size(),n=matrix[0].size();
		vector<vector<int>> preXor(m,vector<int>(n,0));
		priority_queue<int,vector<int>,greater<int>> pq;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(i==0&&j==0){
					preXor[i][j]=matrix[i][j];
				}else if(i==0){
					preXor[i][j]=matrix[i][j]^preXor[i][j-1];
				}else if(j==0){
					preXor[i][j]=matrix[i][j]^preXor[i-1][j];
				}else{
					preXor[i][j]=matrix[i][j]^preXor[i-1][j]^preXor[i][j-1]^preXor[i-1][j-1];
				}
				pq.push(preXor[i][j]);
			}
		}
		for(int i=1;i<k;i++){
			pq.pop();
		}
		return pq.top();
    }
};
/* 
给一非空的单词列表，返回前 k 个出现次数最多的单词。

返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率，按字母顺序排序。
692
 */
class Solution {
public:
	class node{
	public:
		string word;
		int cnt;
		node(string w,int i):word(w),cnt(i){}
		bool operator<(const node &i)const{
			if(cnt<i.cnt){
				return true;
			}
			if(cnt==i.cnt){
				return word>i.word;
			}
            return false;
		}
	};
    vector<string> topKFrequent(vector<string>& words, int k) {
		priority_queue<node> mpq;
		map<string,int> m;
		for(auto word:words){
			m[word]++;
		}
		for(auto [x,y]:m){
			mpq.push(node(x,y));
		}
		vector<string> res;
		for(int i=0;i<k;i++){
			res.push_back(mpq.top().word);
            mpq.pop();
		}
		return res;
    }
};
/* 
在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。

现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j] 的直线，这些直线需要同时满足满足：

     nums1[i] == nums2[j]
    且绘制的直线不与任何其他连线（非水平线）相交。

请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。

以这种方法绘制线条，并返回可以绘制的最大连线数。
1035
 */
//披着皮的最长公共子序列
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
		int m=nums1.size(),n=nums2.size();
		vector<vector<int>> dp(m+1,vector<int>(n+1,0));
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++){
				dp[i][j]=nums1[i-1]==nums2[j-1]?dp[i-1][j-1]+1:max(dp[i-1][j],dp[i][j-1]);
			}
		}
		return dp[m][n];
    }
};
/* 
黑板上写着一个非负整数数组 nums[i] 。Alice 和 Bob 轮流从黑板上擦掉一个数字，Alice 先手。
如果擦除一个数字后，剩余的所有数字按位异或运算得出的结果等于 0 的话，当前玩家游戏失败。
(另外，如果只剩一个数字，按位异或运算得到它本身；如果无数字剩余，按位异或运算结果为 0。）
并且，轮到某个玩家时，如果当前黑板上所有数字按位异或运算结果等于 0，这个玩家获胜。
假设两个玩家每步都使用最优解，当且仅当 Alice 获胜时返回 true。
810
 */
class Solution {
public:
    bool xorGame(vector<int>& nums) {
		if(nums.size()%2==0){
			return true;
		}
		int res=0;
		for(int n:nums){
			res^=n;
		}
		return res==0;
    }
};
/* 
给你一个由非负整数组成的数组 nums 。另有一个查询数组 queries ，其中 queries[i] = [xi, mi] 。

第 i 个查询的答案是 xi 和任何 nums 数组中不超过 mi 的元素按位异或（XOR）得到的最大值。
换句话说，答案是 max(nums[j] XOR xi) ，其中所有 j 均满足 nums[j] <= mi 。如果 nums 中的所有元素都大于 mi，最终答案就是 -1 。

返回一个整数数组 answer 作为查询的答案，其中 answer.length == queries.length 且 answer[i] 是第 i 个查询的答案。
1707
 */
class Trie{
public:
	Trie(){
		next.clear();
		next.resize(2);
	}
	void add(int n){
		Trie* root=this;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(root->next[k]==nullptr){
				root->next[k]=new Trie();
			}
			root=root->next[k];
		}
	}
	int getMaxXor(int n){
		Trie* root=this;
		if(!root->next[0]&&!root->next[1]){
			return -1;
		}
		int res=0;
		for(int i=31;i>=0;i--){
			int k=(n>>i)&1;
			if(k==0){
				if(root->next[1]!=nullptr){
					root=root->next[1];
					res+=(1<<i);
				}else{
					root=root->next[0];
				}
			}else{
				if(root->next[0]!=nullptr){
					root=root->next[0];
					res+=(1<<i);
				}else{
					root=root->next[1];
				}
			}
		}
		return res;
	}
private:
	vector<Trie*> next;
};
class Solution {
public:
    vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
		int i=0;
		for(auto &q:queries){
			q.push_back(i++);
		}
		sort(nums.begin(),nums.end());
		sort(queries.begin(),queries.end(),[](auto &x,auto &y){return x[1]<y[1];});
		vector<int> res(queries.size());
		Trie* root=new Trie();
		i=0;
		for(auto vec:queries){
			int xi=vec[0],mi=vec[1],j=vec[2];
			for(;i<nums.size()&&nums[i]<=mi;i++){
				root->add(nums[i]);
			}
			res[j]=root->getMaxXor(xi);
		}
		return res;
    }
};
/* 
有台奇怪的打印机有以下两个特殊要求：

    打印机每次只能打印由 同一个字符 组成的序列。
    每次可以在任意起始和结束位置打印新字符，并且会覆盖掉原来已有的字符。

给你一个字符串 s ，你的任务是计算这个打印机打印它需要的最少打印次数。
664
 */
class Solution {
public:
    int strangePrinter(string s) {
		int n=s.size();
		vector<vector<int>> dp(n,vector<int>(n,1));
		for(int i=n-1;i>=0;i--){
			for(int j=i+1;j<n;j++){
				if(s[i]==s[j]){
					dp[i][j]=dp[i][j-1];
				}else{
                    dp[i][j]=INT_MAX;
					for(int k=i;k<j;k++){
						dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
					}
				}
			}
		}
		return dp[0][n-1];
    }
};
//20210526未完成
/* 
给出一个字符串 s（仅含有小写英文字母和括号）。
请你按照从括号内到外的顺序，逐层反转每对匹配括号中的字符串，并返回最终的结果。
注意，您的结果中 不应 包含任何括号
1190
 */
class Solution {
public:
    string reverseParentheses(string s) {
		stack<char> sk;
		queue<char> qe;
		for(char c:s){
			if(c!=')'){
				sk.push(c);
			}else{
				while(!sk.empty()&&sk.top()!='('){
					qe.push(sk.top());
					sk.pop();
				}
				if(!sk.empty()&&sk.top()=='('){
					sk.pop();
				}
				while(!qe.empty()){
					sk.push(qe.front());
					qe.pop();
				}
			}
		}
		string res;
		while(!sk.empty()){
			res+=sk.top();
			sk.pop();
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
两个整数之间的汉明距离指的是这两个数字对应二进制位不同的位置的数目。
给出两个整数 x 和 y，计算它们之间的汉明距离。
461
 */
class Solution {
public:
    int hammingDistance(int x, int y) {
		int res=0;
        for(int i=0;i<32;i++){
			int x1=(x>>i)&1;
			int y1=(y>>i)&1;
			res+=x1==y1?0:1;
		}
		return res;
    }
};
/* 
两个整数的 汉明距离 指的是这两个数字的二进制数对应位不同的数量。
计算一个数组中，任意两个数之间汉明距离的总和。
477
 */
class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int res=0,n=nums.size();
        for(int i=0;i<32;i++){
            int c=0;
            for(int j:nums){
                c+=(j>>i)&1;
            }
            res+=c*(n-c);
        }
        return res;
    }
};
/* 
给你一个下标从 0 开始的正整数数组 candiesCount ，其中 candiesCount[i] 表示你拥有的第 i 类糖果的数目。
同时给你一个二维数组 queries ，其中 queries[i] = [favoriteTypei, favoriteDayi, dailyCapi] 。

你按照如下规则进行一场游戏：

    你从第 0 天开始吃糖果。
    你在吃完 所有 第 i - 1 类糖果之前，不能 吃任何一颗第 i 类糖果。
    在吃完所有糖果之前，你必须每天 至少 吃 一颗 糖果。

请你构建一个布尔型数组 answer ，满足 answer.length == queries.length 。
answer[i] 为 true 的条件是：在每天吃 不超过 dailyCapi 颗糖果的前提下，你可以在第 favoriteDayi 天吃到第 favoriteTypei 类糖果；
否则 answer[i] 为 false 。
注意，只要满足上面 3 条规则中的第二条规则，你就可以在同一天吃不同类型的糖果。

请你返回得到的数组 answer 。
输入：candiesCount = [5,2,6,4,1], queries = [[3,1,2],[4,10,3],[3,10,100],[4,100,30],[1,3,1]]
输出：[false,true,true,false,false]
1744
 */
class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
		vector<long long> sum(candiesCount.size()+1);
		sum[0]=0;
		for(int i=0;i<candiesCount.size();i++){
			sum[i+1]=sum[i]+candiesCount[i];
		}
		vector<bool> res;
		for(auto vec:queries){
			long long mineat=vec[1];
			long long maxeat=(long long)vec[1]*vec[2];
			int d=vec[0];
			if(mineat<=sum[d+1]&&mineat>=sum[d]||maxeat<=sum[d+1]&&maxeat>=sum[d]){
				res.push_back(true);
			}else{
				res.push_back(false);
			}
		}
		return res;
    }
};
/*
给你一个整数数组 nums 和一个整数 k ，编写一个函数来判断该数组是否含有同时满足下述条件的连续子数组：

    子数组大小 至少为 2 ，且
    子数组元素总和为 k 的倍数。

如果存在，返回 true ；否则，返回 false 。

如果存在一个整数 n ，令整数 x 符合 x = n * k ，则称 x 是 k 的一个倍数。
523
  */
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        long sum=0;
        map<long,int> m;
        m[0]=-1;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            long tmp=(sum%k+k)%k;
            if(m.count(tmp)){
                if(i-m[tmp]>=2){
                    return true;
                }
            }
            if(!m.count(tmp)){
                m[tmp]=i;
            }
            
        }
        return false;
        /*
        数组总和不小于2 
        int sum=0,res=0;
        map<int,vector<int>> m;
        m[0].push_back(0);
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            int tmp=(sum%k+k)%k;
            if(m.count(tmp)){
                for(int s:m[tmp]){
                    if(sum-s>=2){
                        return true;
                    }
                }
            }
            m[tmp].push_back(sum);
        }
        return false; */
    }
};
/* 
符合下列属性的数组 arr 称为 山脉数组 ：

    arr.length >= 3
    存在 i（0 < i < arr.length - 1）使得：
        arr[0] < arr[1] < ... arr[i-1] < arr[i]
        arr[i] > arr[i+1] > ... > arr[arr.length - 1]

给你由整数组成的山脉数组 arr ，
返回任何满足 arr[0] < arr[1] < ... arr[i - 1] < arr[i] > arr[i + 1] > ... > arr[arr.length - 1] 的下标 i 。
852
 */
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
		int left=0,right=arr.size()-1;
		while(left<right){
			int mid=left+(right-left)/2;
			if(arr[mid]>arr[mid+1]){//mid不可能是0
				right=mid;
			}else{
				left=mid+1;
			}
		}
		return left;
    }
};
/* 
给定一个字符串数组 arr，字符串 s 是将 arr 某一子序列字符串连接所得的字符串，如果 s 中的每一个字符都只出现过一次，那么它就是一个可行解。

请返回所有可行解 s 中最长长度。
1239
 */
class Solution {
public:
    int maxLength(vector<string>& arr) {
		
    }
};
/* 
一个王国里住着国王、他的孩子们、他的孙子们等等。每一个时间点，这个家庭里有人出生也有人死亡。

这个王国有一个明确规定的皇位继承顺序，第一继承人总是国王自己。
我们定义递归函数 Successor(x, curOrder) ，给定一个人 x 和当前的继承顺序，该函数返回 x 的下一继承人。

Successor(x, curOrder):
    如果 x 没有孩子或者所有 x 的孩子都在 curOrder 中：
        如果 x 是国王，那么返回 null
        否则，返回 Successor(x 的父亲, curOrder)
    否则，返回 x 不在 curOrder 中最年长的孩子

比方说，假设王国由国王，他的孩子 Alice 和 Bob （Alice 比 Bob 年长）和 Alice 的孩子 Jack 组成。

    一开始， curOrder 为 ["king"].
    调用 Successor(king, curOrder) ，返回 Alice ，所以我们将 Alice 放入 curOrder 中，得到 ["king", "Alice"] 。
    调用 Successor(Alice, curOrder) ，返回 Jack ，所以我们将 Jack 放入 curOrder 中，得到 ["king", "Alice", "Jack"] 。
    调用 Successor(Jack, curOrder) ，返回 Bob ，所以我们将 Bob 放入 curOrder 中，得到 ["king", "Alice", "Jack", "Bob"] 。
    调用 Successor(Bob, curOrder) ，返回 null 。最终得到继承顺序为 ["king", "Alice", "Jack", "Bob"] 。

通过以上的函数，我们总是能得到一个唯一的继承顺序。

请你实现 ThroneInheritance 类：

    ThroneInheritance(string kingName) 初始化一个 ThroneInheritance 类的对象。国王的名字作为构造函数的参数传入。
    void birth(string parentName, string childName) 表示 parentName 新拥有了一个名为 childName 的孩子。
    void death(string name) 表示名为 name 的人死亡。一个人的死亡不会影响 Successor 函数，也不会影响当前的继承顺序。
	你可以只将这个人标记为死亡状态。
    string[] getInheritanceOrder() 返回 除去 死亡人员的当前继承顺序列表。
1600
多叉树的前序遍历
 */
class ThroneInheritance {
public:
    ThroneInheritance(string kingName) {
		next.emplace(kingName,vector<string>{});
		king=kingName;
    }
    
    void birth(string parentName, string childName) {
		next[parentName].emplace_back(childName);
    }
    
    void death(string name) {
		dead.emplace(name);
    }
    
    vector<string> getInheritanceOrder() {
		vector<string> curOrder;
		function<void(const string&)> preorder=[&](const string& name){
			if(!dead.count(name)){
				curOrder.emplace_back(name);
			}
			for(string str:next[name]){
				preorder(str);
			}
		};
		preorder(king);
		return curOrder;
    }
private:
	string king;
	unordered_map<string,vector<string>> next;
	unordered_set<string> dead;
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */
/* 
二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）。每个 LED 代表一个 0 或 1，最低位在右侧。
给你一个整数 turnedOn ，表示当前亮着的 LED 的数量，返回二进制手表可以表示的所有可能时间。你可以 按任意顺序 返回答案。
小时不会以零开头：
    例如，"01:00" 是无效的时间，正确的写法应该是 "1:00" 。
分钟必须由两位数组成，可能会以零开头：
    例如，"10:2" 是无效的时间，正确的写法应该是 "10:02" 。
401
 */
class Solution {
public:
	vector<string> res;
	int hour,min;
    vector<string> readBinaryWatch(int turnedOn) {
		dfs(turnedOn,1);
		return res;
    }
	void dfs(int turnedOn,int index){
		if(turnedOn==0){
			if(hour<=11&&min<=59){
				string temp=to_string(hour);
				temp+=":";
				if(min<10){
					temp+="0";
				}
				temp+=to_string(min);
				res.emplace_back(temp);
			}
			return;
		}
		for(int i=index;i<=10;i++){
			if(i>4){
				min+=pow(2,i-5);
			}else{
				hour+=pow(2,i-1);
			}
			dfs(turnedOn-1,i+1);
			if(i>4){
				min-=pow(2,i-5);
			}else{
				hour-=pow(2,i-1);
			}
		}
	}
};
/* 
输入一个字符串，打印出该字符串中字符的所有排列。

你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。
剑指38
求排列就知道大概率是回溯
 */
class Solution {
public:
	vector<string> res;
	string temp;
	vector<int> visit;
    vector<string> permutation(string s) {
		visit.resize(s.size());
		sort(s.begin(),s.end());
		dfs(s);
		return res;
    }
	void dfs(string s){
		if(temp.size()==s.size()){
			res.emplace_back(temp);
			return;
		}
		for(int i=0;i<s.size();i++){
			if(visit[i]==1||i>0&&s[i]==s[i-1]&&visit[i-1]==0){
				continue;
			}
			visit[i]=1;
			temp+=s[i];
			dfs(s);
			visit[i]=0;
			temp.pop_back();
		}
	}
};
/*
编写一个函数，输入是一个无符号整数（以二进制串的形式），返回其二进制表达式中数字位数为 '1' 的个数（也被称为汉明重量）。
191
*/
class Solution {
public:
    int hammingWeight(uint32_t n) {
		int res=0;
		for(int i=0;i<31;i++){
			if((n>>i)&&1){
				res++;
			}
		}
		return res;
    }
};
/* 
给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点。求最多有多少个点在同一条直线上。
149
 */
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
		int res=-1;
		int n=points.size();
		for(int i=0;i<n;i++){
			int a=points[i][0];
			int b=points[i][1];
			map<double,int> m;	
			int maxk=1;		
			for(int j=0;j<n;j++){
				if(i==j){
					continue;
				}
				int c=points[j][0];
				int d=points[j][1];
				if((b-d)==0){
					maxk++;
				}else{
					double k=double(a-c)/(b-d);
                    m[k]++;
				}
			}
			for(auto [x,y]:m){
				res=max(res,y+1);
			}
			res=max(res,maxk);
		}
		return res;
    }
};
/* 
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' 。
每个拨轮可以自由旋转：例如把 '9' 变为  '0'，'0' 变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。

锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。

列表 deadends 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。

字符串 target 代表可以解锁的数字，你需要给出最小的旋转次数，如果无论如何不能解锁，返回 -1。
752
 */
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
		unordered_set<string> dead(deadends.begin(),deadends.end()),visit;
        if(dead.count("0000")){
            return -1;
        }
		queue<string> mq;
		mq.emplace("0000");
		int res=0;
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				string str=mq.front();
				if(str==target){
					return res;
				}
				mq.pop();
				for(int j=0;j<4;j++){
					for(int k=-1;k<=1;k+=2){
						string temp=str;
						temp[j]=(temp[j]-'0'+k+10)%10+'0';
						if(!dead.count(temp)&&!visit.count(temp)){
							mq.emplace(temp);
							visit.emplace(temp);
						}
					}
				}
			}
			res++;
		}
		return -1;
    }
};
/* 
在一个 2 x 3 的板上（board）有 5 块砖瓦，用数字 1~5 来表示, 以及一块空缺用 0 来表示.

一次移动定义为选择 0 与一个相邻的数字（上下左右）进行交换.

最终当板 board 的结果是 [[1,2,3],[4,5,0]] 谜板被解开。

给出一个谜板的初始状态，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回 -1 。
773
将每个状态设为点，交换可以得到的就存在到达的边
 */
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
		queue<vector<vector<int>>> mq;
		mq.emplace(board);
		set<vector<vector<int>>> visit;
		visit.emplace(board);
		int res=0;
		vector<vector<int>> target={{1,2,3},{4,5,0}};
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				auto k=mq.front();
				mq.pop();
				if(k==target){
					return res;
				}
				int x=0,y=0;
				for(int a=0;a<k.size();a++){
					for(int b=0;b<k[0].size();b++){
						if(k[a][b]==0){
							x=a,y=b;
						}
					}
				}
				vector<vector<int>> dir={{0,-1},{-1,0},{1,0},{0,1}};
				for(auto d:dir){
					int a=x+d[0],b=y+d[1];
					if(a<0||b<0||a>=2||b>=3){
						continue;
					}
					auto temp=k;
					temp[a][b]=0;
					temp[x][y]=k[a][b];
					if(!visit.count(temp)){
						visit.emplace(temp);
						mq.emplace(temp);
					}
				}
			}
            res++;
		}
		return -1;
    }
};
/* 
N x N 的棋盘 board 上，按从 1 到 N*N 的数字给方格编号，编号 从左下角开始，每一行交替方向。

r 行 c 列的棋盘，按前述方法编号，棋盘格中可能存在 “蛇” 或 “梯子”；如果 board[r][c] != -1，那个蛇或梯子的目的地将会是 board[r][c]。

玩家从棋盘上的方格 1 （总是在最后一行、第一列）开始出发。

每一回合，玩家需要从当前方格 x 开始出发，按下述要求前进：

    选定目标方格：选择从编号 x+1，x+2，x+3，x+4，x+5，或者 x+6 的方格中选出一个目标方格 s ，目标方格的编号 <= N*N。
        该选择模拟了掷骰子的情景，无论棋盘大小如何，你的目的地范围也只能处于区间 [x+1, x+6] 之间。
    传送玩家：如果目标方格 S 处存在蛇或梯子，那么玩家会传送到蛇或梯子的目的地。否则，玩家传送到目标方格 S。 

注意，玩家在每回合的前进过程中最多只能爬过蛇或梯子一次：就算目的地是另一条蛇或梯子的起点，你也不会继续移动。

返回达到方格 N*N 所需的最少移动次数，如果不可能，则返回 -1。
909
 */
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
		int n=board.size(),res=0;
		auto nums=board;
		unordered_map<int,pair<int,int>> ump;
		vector<int> visit(n*n+1,0);
		setnum(nums,ump);
		queue<int> mq;
		mq.emplace(1);
		visit[1]=1;
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int k=mq.front();
				if(k==n*n){
					return res;
				}
				mq.pop();
				for(int j=1;j<=6;j++){
					if(k+j>n*n){
						break;
					}
					if(visit[k+j]){
						continue;
					}
					visit[k+j]=1;
					int x=ump[k+j].first,y=ump[k+j].second;
					if(board[x][y]!=-1){
						mq.emplace(board[x][y]);
						//visit[board[x][y]]=1;//不可以加，如果下一个也能跳，等下次通过+1遍历到时就是已经访问过了，导致无法跳跃
					}else{
						mq.emplace(k+j);
					}
				}
			}
			res++;
		}
		return -1;
    }
	void setnum(vector<vector<int>>& nums,unordered_map<int,pair<int,int>>& ump){
		int k=1;
		bool flag=true;
		for(int i=nums.size()-1;i>=0;i--){
			if(flag){
				for(int j=0;j<nums[0].size();j++){
					ump[k++]={i,j};
				}
			}else{
				for(int j=nums[0].size()-1;j>=0;j--){
					ump[k++]={i,j};
				}
			}
			flag=!flag;
		}
	}
};
/* 
给你一个数组 routes ，表示一系列公交线路，其中每个 routes[i] 表示一条公交线路，第 i 辆公交车将会在上面循环行驶。

    例如，路线 routes[0] = [1, 5, 7] 表示第 0 辆公交车会一直按序列 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... 这样的车站路线行驶。

现在从 source 车站出发（初始时不在公交车上），要前往 target 车站。 期间仅可乘坐公交车。

求出 最少乘坐的公交车数量 。如果不可能到达终点车站，返回 -1 。
815
 */
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
		if(target==source){
			return 0;
		}
		unordered_map<int,vector<int>> ump;
		unordered_set<int> visit;//不再以车站为访问记录，会超时，需要以线路为访问记录
		queue<int> mq;
		int res=1;
		for(int i=0;i<routes.size();i++){
			for(int j=0;j<routes[i].size();j++){
				ump[routes[i][j]].emplace_back(i);
			}
		}
		mq.emplace(source);
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int k=mq.front();
				mq.pop();
				for(int n:ump[k]){
					if(visit.count(n)){//如果这个线路是已经被访问过的，直接跳过
						continue;
					}
					for(int j:routes[n]){
						if(visit.count(j)){
							continue;
						}
						if(j==target){
							return res;
						}
						mq.emplace(j);
					}
					visit.emplace(n);
				}
			}
			res++;
		}
		return -1;
    }
};
//以车站为访问记录-超内存！
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
		if(target==source){
			return 0;
		}
		unordered_map<int,vector<int>> next;
		unordered_set<int> visit;
		queue<int> mq;
		int res=1;
		mq.emplace(source);
		visit.emplace(source);
		for(auto vec:routes){
			for(int i=0;i<vec.size();i++){
				next[vec[i]].insert(next[vec[i]].end(),vec.begin(),vec.end());
			}
		}
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int k=mq.front();
				mq.pop();
				for(int n:next[k]){
					if(n==target){
						return res;
					}
					if(visit.count(n)){
						continue;
					}
					visit.emplace(n);
					mq.emplace(n);
				}
			}
			res++;
		}
		return -1;
    }
};
/* 
给定一个正整数，返回它在 Excel 表中相对应的列名称。
168
实质上是转换为26进制的问题，注意的是没有0多个26！
 */
class Solution {
public:
    string convertToTitle(int columnNumber) {
		int n=columnNumber;
		string res;
		while(n){
			int k=(n-1)%26+1;
			res+=k-1+'A';
			n=(n-1)/26;
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
请实现两个函数，分别用来序列化和反序列化二叉树。

你需要设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，
你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
剑指37
 */
//前序遍历实现序列化
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        preorder(root);
		return str;
    }
	void preorder(TreeNode* root) {
        if(root==nullptr){
			str+="#,";
			return;
		}
		str+=to_string(root->val);
		str+=",";
		preorder(root->left);
		preorder(root->right);
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> vec;
		splite(data,vec);
		return depreorder(vec,0);
	}
	TreeNode* depreorder(vector<string>& vec,int i){
		if(i>=vec.size()||vec[i]=="#"){
			return nullptr;
		}
		int val=stoi(vec[i]);
		TreeNode* root=new TreeNode(val);
		root->left=depreorder(vec,i+1);
		root->right=depreorder(vec,i+2);
		return root;
	}
	void splite(string& data,vector<string>& vec){
		int i=0;
		while(i<data.size()){
			int n=data.find(',',i);
			vec.emplace_back(data.substr(i,n-i));
			i=n+1;
		}
	}
private:
	string str;
};
/* 
小朋友 A 在和 ta 的小伙伴们玩传信息游戏，游戏规则如下：

    有 n 名玩家，所有玩家编号分别为 0 ～ n-1，其中小朋友 A 的编号为 0
    每个玩家都有固定的若干个可传信息的其他玩家（也可能没有）。传信息的关系是单向的（比如 A 可以向 B 传信息，但 B 不能向 A 传信息）。
    每轮信息必须需要传递给另一个人，且信息可重复经过同一个人

给定总玩家数 n，以及按 [玩家编号,对应可传递玩家编号] 关系组成的二维数组 relation。
返回信息从小 A (编号 0 ) 经过 k 轮传递到编号为 n-1 的小伙伴处的方案数；若不能到达，返回 0。

示例 1：

    输入：n = 5, relation = [[0,2],[2,1],[3,4],[2,3],[1,4],[2,0],[0,4]], k = 3

    输出：3

    解释：信息从小 A 编号 0 处开始，经 3 轮传递，到达编号 4。共有 3 种方案，分别是 0->2->0->4， 0->2->1->4， 0->2->3->4。

示例 2：

    输入：n = 3, relation = [[0,2],[2,1]], k = 2

    输出：0

    解释：信息不能从小 A 处经过 2 轮传递到编号 2

限制：

    2 <= n <= 10
    1 <= k <= 5
    1 <= relation.length <= 90, 且 relation[i].length == 2
    0 <= relation[i][0],relation[i][1] < n 且 relation[i][0] != relation[i][1]
LCP 07
 */
class Solution {
public:
    int numWays(int n, vector<vector<int>>& relation, int k) {
		vector<vector<int>> next(n);
		for(auto vec:relation){
			next[vec[0]].emplace_back(vec[1]);
		}
		queue<int> mq;
		mq.emplace(0);
		while(!mq.empty()&&k-->0){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int j=mq.front();
				mq.pop();
				for(int l:next[j]){
					mq.emplace(l);
				}
			}
		}
		int res=0;
		while(!mq.empty()){
			if(mq.front()==n-1){
				res++;
			}
            mq.pop();
		}
		return res;
    }
};
/* 
夏日炎炎，小男孩 Tony 想买一些雪糕消消暑。

商店中新到 n 支雪糕，用长度为 n 的数组 costs 表示雪糕的定价，其中 costs[i] 表示第 i 支雪糕的现金价格。
Tony 一共有 coins 现金可以用于消费，他想要买尽可能多的雪糕。

给你价格数组 costs 和现金量 coins ，请你计算并返回 Tony 用 coins 现金能够买到的雪糕的 最大数量 。
1833
 */
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
		int res=0;
		sort(costs.begin(),costs.end());
		for(int i:costs){
			if(coins>=i){
				res++;
				coins-=i;
			}
		}
		return res;
    }
};
/*
给定一个化学式formula（作为字符串），返回每种原子的数量。

原子总是以一个大写字母开始，接着跟随0个或任意个小写字母，表示原子的名字。

如果数量大于 1，原子后会跟着数字表示原子的数量。如果数量等于 1 则不会跟数字。例如，H2O 和 H2O2 是可行的，但 H1O2 这个表达是不可行的。

两个化学式连在一起是新的化学式。例如 H2O2He3Mg4 也是化学式。

一个括号中的化学式和数字（可选择性添加）也是化学式。例如 (H2O2) 和 (H2O2)3 是化学式。

给定一个化学式，输出所有原子的数量。
格式为：第一个（按字典序）原子的名子，跟着它的数量（如果数量大于 1），然后是第二个原子的名字（按字典序），跟着它的数量（如果数量大于 1），以此类推。
726 ---------------------------
 */
class Solution {
public:
    string countOfAtoms(string formula) {
        int i = 0, n = formula.length();

        auto parseAtom = [&]() -> string {
            string atom;
            atom += formula[i++]; // 扫描首字母
            while (i < n && islower(formula[i])) {
                atom += formula[i++]; // 扫描首字母后的小写字母
            }
            return atom;
        };

        auto parseNum = [&]() -> int {
            if (i == n || !isdigit(formula[i])) {
                return 1; // 不是数字，视作 1
            }
            int num = 0;
            while (i < n && isdigit(formula[i])) {
                num = num * 10 + int(formula[i++] - '0'); // 扫描数字
            }
            return num;
        };

        stack<unordered_map<string, int>> stk;
        stk.push({});
        while (i < n) {
            char ch = formula[i];
            if (ch == '(') {
                i++;
                stk.push({}); // 将一个空的哈希表压入栈中，准备统计括号内的原子数量
            } else if (ch == ')') {
                i++;
                int num = parseNum(); // 括号右侧数字
                auto atomNum = stk.top();
                stk.pop(); // 弹出括号内的原子数量
                for (auto &[atom, v] : atomNum) {
                    stk.top()[atom] += v * num; // 将括号内的原子数量乘上 num，加到上一层的原子数量中
                }
            } else {
                string atom = parseAtom();
                int num = parseNum();
                stk.top()[atom] += num; // 统计原子数量
            }
        }

        auto &atomNum = stk.top();
        vector<pair<string, int>> pairs;
        for (auto &[atom, v] : atomNum) {
            pairs.emplace_back(atom, v);
        }
        sort(pairs.begin(), pairs.end());

        string ans;
        for (auto &p : pairs) {
            ans += p.first;
            if (p.second > 1) {
                ans += to_string(p.second);
            }
        }
        return ans;
    }
};
/* 
给你一个数组 orders，表示客户在餐厅中完成的订单，确切地说， orders[i]=[customerNamei,tableNumberi,foodItemi] ，
其中 customerNamei 是客户的姓名，tableNumberi 是客户所在餐桌的桌号，而 foodItemi 是客户点的餐品名称。

请你返回该餐厅的 点菜展示表 。在这张表中，表中第一行为标题，其第一列为餐桌桌号 “Table” ，后面每一列都是按字母顺序排列的餐品名称。
接下来每一行中的项则表示每张餐桌订购的相应餐品数量，第一列应当填对应的桌号，后面依次填写下单的餐品数量。

注意：客户姓名不是点菜展示表的一部分。此外，表中的数据行应该按餐桌桌号升序排列。
1418
 */
class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
		map<int,map<string,int>> mp;
		set<string> st;
		for(auto vec:orders){
			mp[stoi(vec[1])][vec[2]]++;
			st.emplace(vec[2]);
		}
		vector<vector<string>> res(mp.size()+1);
		res[0].emplace_back("Table");
		for(auto str:st){
			res[0].emplace_back(str);
		}
		int i=1;
		for(auto [k,m]:mp){
			res[i].emplace_back(to_string(k));
			for(int j=1;j<res[0].size();j++){
				res[i].emplace_back(to_string(m[res[0][j]]));
			}
			i++;
		}
		return res;
    }
};
/* 
大餐 是指 恰好包含两道不同餐品 的一餐，其美味程度之和等于 2 的幂。

你可以搭配 任意 两道餐品做一顿大餐。

给你一个整数数组 deliciousness ，其中 deliciousness[i] 是第 i​​​​​​​​​​​​​​ 道餐品的美味程度，返回你可以用数组中的餐品做出的不同 大餐 的数量。
结果需要对 109 + 7 取余。

注意，只要餐品下标不同，就可以认为是不同的餐品，即便它们的美味程度相同。
1711

    1 <= deliciousness.length <= 105
    0 <= deliciousness[i] <= 220
进阶版的二数之和
 */
class Solution {
public:
    int countPairs(vector<int>& deliciousness) {
		unordered_map<int,int> ump;
		int res=0;
		for(int num:deliciousness){
			for(int i=0;i<=21;i++){
				int sum=pow(2,i);
				if(ump.count(sum-num)){
					res+=ump[sum-num];
				}
				res%=1000000007;
			}
			ump[num]++;
		}
		return res;
    }
};
/* 
给你一个二元数组 nums ，和一个整数 goal ，请你统计并返回有多少个和为 goal 的 非空 子数组。

子数组 是数组的一段连续部分。
930
求这种子数组为固定值的一般是前缀和做
 */
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
		int sum=0,res=0;
		unordered_map<int,int> ump;
		ump.emplace(0,1);
		for(int num:nums){
			sum+=num;
			if(ump.count(sum-goal)){
				res+=ump[sum-goal];
			}
			ump[sum]++;
		}
		return res;
    }
};
/* 
给定一位研究者论文被引用次数的数组（被引用次数是非负整数）。编写一个方法，计算出研究者的 h 指数。

h 指数的定义：h 代表“高引用次数”（high citations），
一名科研人员的 h 指数是指他（她）的 （N 篇论文中）总共有 h 篇论文分别被引用了至少 h 次。
且其余的 N - h 篇论文每篇被引用次数 不超过 h 次。

例如：某人的 h 指数是 20，这表示他已发表的论文中，每篇被引用了至少 20 次的论文总共有 20 篇。
274
百度可得：让其按被引次数从高到低排列，往下核对，直到某篇论文的序号大于该论文被引次数，那个序号减去1就是h指数
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
		sort(citations.begin(),citations.end(),greater<int>());
		int i=1;
		for(;i<=citations.size();i++){
			if(i>citations[i-1]){
				break;
			}
		}
		return i-1;
    }
};
/* 
给定一位研究者论文被引用次数的数组（被引用次数是非负整数），数组已经按照 升序排列 。编写一个方法，计算出研究者的 h 指数。

h 指数的定义: “h 代表“高引用次数”（high citations），
一名科研人员的 h 指数是指他（她）的 （N 篇论文中）总共有 h 篇论文分别被引用了至少 h 次。
（其余的 N - h 篇论文每篇被引用次数不多于 h 次。）"
275
 */
class Solution {
public:
    int hIndex(vector<int>& citations) {
		reverse(citations.begin(),citations.end());
		int i=1;
		for(;i<=citations.size();i++){
			if(i>citations[i-1]){
				break;
			}
		}
		return i-1;
    }
};
//二分--感觉是强行二分
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int l=0,r=citations.size();
        while(l<r){
            int mid=l+r+1>>1;
            if(citations[citations.size()-mid]>=mid) l=mid;
            else r=mid-1;
        }
        return r;
    }
};
/* 
给你两个正整数数组 nums1 和 nums2 ，数组的长度都是 n 。

数组 nums1 和 nums2 的 绝对差值和 定义为所有 |nums1[i] - nums2[i]|（0 <= i < n）的 总和（下标从 0 开始）。

你可以选用 nums1 中的 任意一个 元素来替换 nums1 中的 至多 一个元素，以 最小化 绝对差值和。

在替换数组 nums1 中最多一个元素 之后 ，返回最小绝对差值和。因为答案可能很大，所以需要对 109 + 7 取余 后返回。

|x| 定义为：

    如果 x >= 0 ，值为 x ，或者
    如果 x <= 0 ，值为 -x
1818
 */
class Solution {
public:
    int minAbsoluteSumDiff(vector<int>& nums1, vector<int>& nums2) {
		
    }
};
/* 
元素的 频数 是该元素在一个数组中出现的次数。

给你一个整数数组 nums 和一个整数 k 。在一步操作中，你可以选择 nums 的一个下标，并将该下标对应元素的值增加 1 。

执行最多 k 次操作后，返回数组中最高频元素的 最大可能频数 。
1838
 */
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
		int n=nums.size();
		sort(nums.begin(),nums.end());
		int left=0,right=1,res=0;
        long long temp=0;
		while(right<n){
			while(right<n&&temp+(long long)(nums[right]-nums[right-1])*(right-left)<=k){
				temp+=(long long)(nums[right]-nums[right-1])*(right-left);
				right++;
				res=max(res,right-left);
			}
			while(temp>k){
				temp-=nums[right-1]-nums[left];
				left++;
			}
		}
		return res;
    }
};
class Solution {
public:
    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        long long total = 0;
        int l = 0, res = 1;
        for (int r = 1; r < n; ++r) {
            total += (long long)(nums[r] - nums[r - 1]) * (r - l);
            while (total > k) {
                total -= nums[r] - nums[l];
                ++l;
            }
            cout<<l<<" "<<r<<" "<<total<<endl;
            res = max(res, r - l + 1);
        }
        return res;
    }
};
/* 
在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 逐行 依次按 “之” 字形进行标记。

如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；

而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记

给你树上某一个节点的标号 label，请你返回从根节点到该标号为 label 节点的路径，该路径是由途经的节点标号所组成的。
1104
 */
class Solution {
public:
    vector<int> pathInZigZagTree(int label) {
		int n=1;
		vector<int> res;
		while(pow(2,++n)-1<label){}
		while(n-->=1){
            res.emplace_back(label);
			label=pow(2,n)-1-(label/2-pow(2,n-1));
		}
        sort(res.begin(),res.end());
		return res;
    }
};
/* 
给定一个包含非负整数的数组，你的任务是统计其中可以组成三角形三条边的三元组个数。
611
 */
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
		int n=nums.size(),res=0;
		for(int i=0;i<n-2;i++){
			for(int j=i+1;j<n-1;j++){
				int left=j+1,right=n-1;
				while(left<right){
					//向上取整
					int mid=left+(right-left+1)/2;
					if(nums[mid]>=nums[i]+nums[j]){
						right=mid-1;
					}else{
						left=mid;
					}
				}
				//当跳出二分时，其实不知道left是否合适的
                if(nums[left]<nums[i]+nums[j]){
                    res+=left-j;
                }
			}
		}
		return res;
    }
};
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
		//双指针
		int n=nums.size(),res=0;
		sort(nums.begin(),nums.end());
		for(int i=n-1;i>=2;i--){
			int l=0,r=i-1;
			while(l<r){
				if(nums[l]+nums[r]<=nums[i]){
					l++;
				}else{
					res+=r-l;
					r--;
				}
			}
		}
		return res;
    }
};
/* 
如果一个数列 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该数列为等差数列。

    例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列。

给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。

子数组 是数组中的一个连续序列。
413
本题可以使用dp，类似于递增子数组的做法
还可以使用双指针
 */
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        if(nums.size()<3){
            return 0;
        }
		int n=nums.size(),res=0,diff=nums[1]-nums[0];
		vector<int> dp(n,0);
		for(int i=2;i<n;i++){
			if(nums[i]-nums[i-1]==diff){
				dp[i]=dp[i-1]+1;
				res+=dp[i];
			}else{
				diff=nums[i]-nums[i-1];
			}
		}
		return res;
    }
};
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
		if(nums.size()<3){
            return 0;
        }
		int n=nums.size(),res=0,diff,len=0;
		for(int i=0;i<n-2;i+=len){
			diff=nums[i+1]-nums[i],len=1;
			for(int j=i+1;j<n&&nums[j+1]-nums[j]==diff;j++){
				len++;
			}
			if(len>=3){
				res+=(len-2)*(len-1)/2;
			}
		}
		return res;
    }
};
/* 
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
516
 */
class Solution {
public:
    int longestPalindromeSubseq(string s) {
		int n=s.size();
		vector<vector<int>> dp(n,vector<int>(n,0));
		for(int i=0;i<n;i++){
			dp[i][i]=1;
			for(int j=i-1;j>=0;j--){
				if(s[i]==s[j]){
					dp[j][i]=dp[j+1][i-1]+2;
				}else{
					dp[j][i]=max(dp[j+1][i],dp[j][i-1]);
				}
			}
		}
		return dp[0][n-1];
    }
};
/* 
给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。
233
 */
class Solution {
public:
    int countDigitOne(int n) {
		int high,low,cur,res=0;
        long long digit;
		for(int i=0;;i++){
			digit=pow(10,i);
            if(digit>n){
                break;
            }
			high=n/(digit*10);
			low=n%digit;
			cur=(n/digit)%10;
			if(cur==0){
				res+=high*digit;
			}else if(cur==1){
				res+=high*digit+low+1;
			}else{
				res+=(high+1)*digit;
			}
		}
		return res;
    }
};
/* 
假设有从 1 到 N 的 N 个整数，如果从这 N 个数字中成功构造出一个数组，
使得数组的第 i 位 (1 <= i <= N) 满足如下两个条件中的一个，我们就称这个数组为一个优美的排列。条件：

    第 i 位的数字能被 i 整除
    i 能被第 i 位上的数字整除
i%num[i]==0||num[i]%i==0
现在给定一个整数 N，请问可以构造多少个优美的排列？
526
 */
class Solution {
public:
	int res=0;
	vector<int> visit;
    int countArrangement(int n) {
		visit.resize(n+1);
		dfs(1,n);
		return res;
    }
	void dfs(int index,int n){
		if(index==n+1){
			res++;
            return;
		}
		for(int i=1;i<=n;i++){
			if(index%i!=0&&i%index!=0||visit[i]==1){
				continue;
			}
			visit[i]=1;
			dfs(index+1,n);
			visit[i]=0;
		}
	}
};
/* 
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。
50
快速幂，周赛碰到没算出来！
 */
class Solution {
public:
    double myPow(double x, int n) {
		long N=n;
		return N>=0?getPow(x,N):1.0/getPow(x,-N);
    }
	//递归
	double getPow(double x,int N){
		if(N==0){
			return 1.0;
		}
		double y=getPow(x,N/2);
		return N%2==0?y*y:y*y*x;
	}
};
/* 
给定平面上 n 对 互不相同 的点 points ，其中 points[i] = [xi, yi] 。回旋镖 是由点 (i, j, k) 表示的元组 ，其中 i 和 j 之间的距离和 i 和 k 之间的距离相等（需要考虑元组的顺序）。

返回平面上所有回旋镖的数量。
447
 */
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        if(points.size()<3){
			return 0;
		}
		int res=0;
		int n=points.size();
		map<int,int> mp;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				int len=pow(points[i][0]-points[j][0],2)+pow(points[i][1]-points[j][1],2);
				mp[len]++;
			}
			for(auto [i,j]:mp){
				if(j>=2){
					res+=(j-1)*j;
				}
			}
			mp.clear();
		}
		return res;
    }
};
/* 
给你一个字符串 s 和一个字符串数组 dictionary 作为字典，找出并返回字典中最长的字符串，该字符串可以通过删除 s 中的某些字符得到。

如果答案不止一个，返回长度最长且字典序最小的字符串。如果答案不存在，则返回空字符串。
524
 */
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
		string res;
		auto cmp=[](auto i,auto j){
			if(i.size()==j.size()){
				return i<j;
			}
			return i.size()>j.size();
		};
		sort(dictionary.begin(),dictionary.end(),cmp);
		for(auto str:dictionary){
			if(str.size()>s.size()){
				continue;
			}
			int i=0,j=0;
			for(;i<s.size()&&j<str.size();i++){
				if(str[j]==s[i]){
					j++;
				}
			}
			if(j==str.size()){
				res=str;
				break;
			}
		}
		return res;
    }
};
/* 
给定一个 m x n 二维字符网格 board 和一个单词（字符串）列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过 相邻的单元格 内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母在一个单词中不允许被重复使用。
212
 */
class Solution {
public:
	vector<vector<int>> dir={{-1,0},{1,0},{0,-1},{0,1}};
	bool dfs(vector<vector<char>>& board, string str, int index, int i, int j){
		if(index==str.size()){
			return true;
		}
		if(i<0||j<0||i>=board.size()||j>=board[0].size()||board[i][j]!=str[index]){
			return false;
		}
		board[i][j]='#';
		for(auto vec:dir){
			if(dfs(board,str,index+1,i+vec[0],j+vec[1])){
				board[i][j]=str[index];
				return true;
			}
		}
		board[i][j]=str[index];
		return false;
	}
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> res;
		map<char,int> mp;
		for(auto vec:board){
			for(auto i:vec){
				mp[i]++;
			}
		}
		for(auto str:words){
			auto tp=mp;
			bool flag=true;
			for(auto i:str){
				if(--tp[i]<0){
					flag=false;
					break;
				}
			}
			for(int i=0;i<board.size()&&flag;i++){
				for(int j=0;j<board[0].size()&&flag;j++){
					if(dfs(board,str,0,i,j)){
						res.emplace_back(str);
						flag=false;
					}
				}
			}
		}
		return res;
    }
};
/* 
请你判断一个 9x9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。

    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）

数独部分空格内已填入了数字，空白格用 '.' 表示。

注意：

    一个有效的数独（部分已被填充）不一定是可解的。
    只需要根据以上规则，验证已经填入的数字是否有效即可。
36
*/
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
		int m=board.size(),n=board[0].size();
		vector<set<int>> vs(10); 
		for(int i=0;i<9;i++){
            set<char> s1,s2;
			for(int j=0;j<9;j++){
				int index=(i/3)*3+j/3;
				if(board[i][j]!='.'&&vs[index].count(board[i][j])){
					return false;
				}
				vs[index].emplace(board[i][j]);
                if(board[i][j]!='.'&&s1.count(board[i][j])){
					return false;
				}
				s1.emplace(board[i][j]);
				if(board[j][i]!='.'&&s2.count(board[j][i])){
					return false;
				}
				s2.emplace(board[j][i]);
			}
		}
		return true;
    }
};
/* 
给你一个头结点为 head 的单链表和一个整数 k ，请你设计一个算法将链表分隔为 k 个连续的部分。

每部分的长度应该尽可能的相等：任意两部分的长度差距不能超过 1 。这可能会导致有些部分为 null 。

这 k 个部分应该按照在链表中出现的顺序排列，并且排在前面的部分的长度应该大于或等于排在后面的长度。

返回一个由上述 k 部分组成的数组。
725
 */
class Solution {
public:
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
		int n=0;
		ListNode* ptr=head;
		while(ptr){
			n++;
			ptr=ptr->next;
		}
		vector<ListNode*> res;
		int m=n/k,r=n%k;
        //cout<<m<<" "<<r<<endl;
		ptr=head;
		for(int i=0;i<k;i++){
			ListNode* dst=ptr;
			ListNode* tmp;
			for(int j=1;j<m&&ptr;j++){
				ptr=ptr->next;
			}
			if(m&&r!=0&&ptr){
                r--;
				ptr=ptr->next;
			}
			if(ptr){
				tmp=ptr->next;
				ptr->next=nullptr;
				res.emplace_back(dst);
			}else{
				tmp=nullptr;
				res.emplace_back(dst);
			}
			ptr=tmp;
		}
		return res;
    }
};
/* 
多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。
这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的示例所示。

给你位于列表第一级的头节点，请你扁平化列表，使所有结点出现在单级双链表中。
430
 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/
/* class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
class Solution {
public:
    Node* flatten(Node* head) {
        Node* p=head;
		stack<Node*> n;
		while(p){
			if(p->child){
				n.emplace(p->next);
				p->next=p->child;
				p->child=nullptr;
			}
			if(p->next==nullptr){
				if(n.size()){
					Node* tmp=n.top();
					n.pop();
					p->next=tmp;
				}
			}
			p=p->next;
		}
		return head;
    }
}; */
/* 
给你两个整数 a 和 b ，不使用 运算符 + 和 - ​​​​​​​，计算并返回两整数之和。
371
 */
class Solution {
public:
    int getSum(int a, int b) {
        unsigned int c=-1,d=-1;
		while(d){
			c=a^b;
			d=a&b;
			d<<1;
			a=c;
			b=d;
		}
		return a;
    }
};
/* 
一条包含字母 A-Z 的消息通过以下的方式进行了编码：

'A' -> 1
'B' -> 2
...
'Z' -> 26

要 解码 一条已编码的消息，所有的数字都必须分组，然后按原来的编码方案反向映射回字母（可能存在多种方式）。例如，"11106" 可以映射为：

    "AAJF" 对应分组 (1 1 10 6)
    "KJF" 对应分组 (11 10 6)

注意，像 (1 11 06) 这样的分组是无效的，因为 "06" 不可以映射为 'F' ，因为 "6" 与 "06" 不同。

除了 上面描述的数字字母映射方案，编码消息中可能包含 '*' 字符，可以表示从 '1' 到 '9' 的任一数字（不包括 '0'）。
例如，编码字符串 "1*" 可以表示 "11"、"12"、"13"、"14"、"15"、"16"、"17"、"18" 或 "19" 中的任意一条消息。
对 "1*" 进行解码，相当于解码该字符串可以表示的任何编码消息。

给你一个字符串 s ，由数字和 '*' 字符组成，返回 解码 该字符串的方法 数目 。

由于答案数目可能非常大，返回对 109 + 7 取余 的结果。
639
// 大概率回溯
回溯大概率超时
 */
class Solution {
public:
	long long res=0,temp=1;
    int numDecodings(string s) {
		dfs(s,0);
		return res;
    }
	void dfs(string s,int index){
        //temp%=1000000007;
		if(index>=s.size()){
            //cout<<temp<<endl;
            res%=1000000007;
			res+=temp;
			return;
		}
		if(s[index]=='1'){
			dfs(s,index+1);
			if(index!=s.size()-1){
				if(s[index+1]=='*'){
					temp*=9;
					dfs(s,index+2);
					temp/=9;
				}else{
					dfs(s,index+2);
				}
			}
		}else if(s[index]=='2'){
			dfs(s,index+1);
			if(index!=s.size()-1){
				if(s[index+1]=='*'){
					temp*=6;
					dfs(s,index+2);
					temp/=6;
				}else if(s[index+1]-'0'<=6){
					dfs(s,index+2);
				}
			}
		}else if(s[index]=='*'){
			temp*=9;
			dfs(s,index+1);
			temp/=9;
			if(index!=s.size()-1){
				if(s[index+1]!='*'){
					if(s[index+1]-'0'<=6){
						temp*=2;
						dfs(s,index+2);
						temp/=2;
					}else{
						dfs(s,index+2);
					}
				}else{
					temp*=15;
					dfs(s,index+2);
					temp/=15;
				}
			}
		}else if(s[index]=='0'){
			return;
		}else{
			dfs(s,index+1);
		}
	}
};

/* 
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
437
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    unordered_map<int, int> prefix;

    int dfs(TreeNode *root, long long curr, int targetSum) {
        if (!root) {
            return 0;
        }

        int ret = 0;
        curr += root->val;
        if (prefix.count(curr - targetSum)) {
            ret = prefix[curr - targetSum];
        }

        prefix[curr]++;
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--;

        return ret;
    }

    int pathSum(TreeNode* root, int targetSum) {
        prefix[0] = 1;
        return dfs(root, 0, targetSum);
    }
};
/* 
给你一份旅游线路图，该线路图中的旅行线路用数组 paths 表示，
其中 paths[i] = [cityAi, cityBi] 表示该线路将会从 cityAi 直接前往 cityBi 。
请你找出这次旅行的终点站，即没有任何可以通往其他城市的线路的城市。

题目数据保证线路图会形成一条不存在循环的线路，因此恰有一个旅行终点站。
1436
 */
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
		unordered_set<string> f,s;
		for(auto vec:paths){
			f.emplace(vec[0]);
			s.emplace(vec[1]);
		}
		for(auto i:s){
			if(!f.count(i)){
				return i;
			}
		}
		return "";
    }
};
/* 
给定一个整数，编写一个算法将这个数转换为十六进制数。对于负整数，我们通常使用 补码运算 方法。

注意:

    十六进制中所有字母(a-f)都必须是小写。
    十六进制字符串中不能包含多余的前导零。
	如果要转化的数为0，那么以单个字符'0'来表示；对于其他情况，十六进制字符串中的第一个字符将不会是0字符。 
    给定的数确保在32位有符号整数范围内。
    不能使用任何由库提供的将数字直接转换或格式化为十六进制的方法。
405
 */
class Solution {
public:
    string toHex(int num) {
		string res;
		if(num>0){
			while(num){
				int i=num%16;
				if(i>=10){
					res+='a'+i-10;
				}else{
					res+='0'+i;
				}
				num/=16;
			}
		}
		reverse(res.begin(),res.end());
		return res;
    }
};
/* 
给定两个整数，分别表示分数的分子 numerator 和分母 denominator，以 字符串形式返回小数 。

如果小数部分为循环小数，则将循环的部分括在括号内。

如果存在多个答案，只需返回 任意一个 。

对于所有给定的输入，保证 答案字符串的长度小于 104 。
166
 */
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {

    }
};
/* 
有一个密钥字符串 S ，只包含字母，数字以及 '-'（破折号）。其中， N 个 '-' 将字符串分成了 N+1 组。

给你一个数字 K，请你重新格式化字符串，使每个分组恰好包含 K 个字符。
特别地，第一个分组包含的字符个数必须小于等于 K，但至少要包含 1 个字符。
两个分组之间需要用 '-'（破折号）隔开，并且将所有的小写字母转换为大写字母。

给定非空字符串 S 和数字 K，按照上面描述的规则进行格式化。
482
 */
class Solution {
public:
    string licenseKeyFormatting(string s, int k) {
		string str;
		for(auto i:s){
			if(i=='_'){
				continue;
			}
			if(i>='a'&&i<='z'){
				i-=32;
			}
			str+=i;
		}
		reverse(str.begin(),str.end());
		string res;
		for(int i=0;i<str.size();i++){
			if(i!=0&&i%k==0){
				res+='_';
			}
			res+=str[i];
		}
		reverse(res.begin(),res.end());
		return res;
	}
};
/* 
请你设计一个迭代器，除了支持 hasNext 和 next 操作外，还支持 peek 操作。

实现 PeekingIterator 类：

    PeekingIterator(int[] nums) 使用指定整数数组 nums 初始化迭代器。
    int next() 返回数组中的下一个元素，并将指针移动到下个元素处。
    bool hasNext() 如果数组中存在下一个元素，返回 true ；否则，返回 false 。
    int peek() 返回数组中的下一个元素，但 不 移动指针。
284
 */

/*  Below is the interface for Iterator, which is already defined for you.
 **DO NOT** modify the interface for Iterator. */

class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
		// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	    flag=Iterator::hasNext();
		if(flag){
			nextele=Iterator::next();
		}
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() {
        return nextele;
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		int res=nextele;
	    flag=Iterator::hasNext();
		if(flag){
			nextele=Iterator::next();
		}
		return res;
	}
	
	bool hasNext() const {
	    return flag;
	}
private:
	int nextele;
	bool flag;
};
/* 
给你一个非空数组，返回此数组中 第三大的数 。如果不存在，则返回数组中最大的数。
414
 */
class Solution {
public:
    int thirdMax(vector<int>& nums) {
		priority_queue<int> mpq;
		for(int i:nums){
			mpq.emplace(i);
		}
		int max=mpq.top();
		int temp=max-1;
		int index=0;
		while(!mpq.empty()){
			if(mpq.top()==temp){
				mpq.pop();
				continue;
			}
			temp=mpq.top();
			index++;
			if(index==3){
				break;
			}
		}
		return index==3?temp:max;
    }
};
/*
统计字符串中的单词个数，这里的单词指的是连续的不是空格的字符。

请注意，你可以假定字符串里不包括任何不可打印的字符。
434 
 */
class Solution {
public:
    int countSegments(string s) {
		int res=0;
		int i=1;
		for(int i=1;i<s.size();i++){
			if(s[i]==' '&&s[i-1]!=' '){
				res++;
			}
		}
		if(s.size()>0&&s.back()!=' '){
			res++;
		}
		return res;
    }
};
/* 
所有 DNA 都由一系列缩写为 'A'，'C'，'G' 和 'T' 的核苷酸组成，例如："ACGAATTCCG"。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。

编写一个函数来找出所有目标子串，目标子串的长度为 10，且在 DNA 字符串 s 中出现次数超过一次。
187
 */
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
		string tmp;
		unordered_map<string,int> ump;
		vector<string> res;
		for(int i=0;i<s.size()-10;i++){
			tmp=s.substr(i,10);
			if(ump.count(tmp)&&ump[tmp]==1){
				res.emplace_back(tmp);
			}
			ump[tmp]++;
		}
		return res;
    }
};
/* 
将非负整数 num 转换为其对应的英文表示。
273
 */
class Solution {
public:
    string numberToWords(int num) {
        if(num==0){
            return "Zero";
        }
		vector<int> vec;
        string res="";
		while(num){
            //cout<<num%1000<<endl;
			vec.emplace_back(num%1000);
			num/=1000;
		}
		vector<string> str1={"","Thousand","Million","Billion"};
		vector<string> str2={"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
		vector<string> str3={"", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
		vector<string> str4={"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
		for(int i=vec.size()-1;i>=0;i--){
            if(vec[i]==0){
                continue;
            }
			if(vec[i]/100==0){
                if(i!=vec.size()-1){
                    res+=" ";
                }
				if(vec[i]/10){
					if(vec[i]/10==1){
						res+=str4[vec[i]%10];
					}else{
						res+=str3[(vec[i]/10)%10]+" "+str2[vec[i]%10];
					}
				}else{
					res+=str2[vec[i]%10];
				}
				while(res.back()==' '){
                    res.pop_back();
                }
			}else{
                if(i!=vec.size()-1){
                    res+=" ";
                }
				if((vec[i]/10)%10==1){
					res+=str2[vec[i]/100]+" Hundred "+str4[vec[i]%10];
				}else{
                    if((vec[i]/10)%10){
                        res+=str2[vec[i]/100]+" Hundred "+str3[(vec[i]/10)%10]+" "+str2[vec[i]%10];
                    }else{
                        res+=str2[vec[i]/100]+" Hundred "+str2[vec[i]%10];
                    }
				}
                while(res.back()==' '){
                    res.pop_back();
                }
			}
            if(i>0){
                res+=" "+str1[i];
            }
		}
		return res;
    }	
};
/*
给定一个正整数 n ，输出外观数列的第 n 项。

「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。

你可以将其视作是由递归公式定义的数字字符串序列：

    countAndSay(1) = "1"
    countAndSay(n) 是对 countAndSay(n-1) 的描述，然后转换成另一个数字字符串。
38
 */
class Solution {
public:
    string countAndSay(int n) {
		string res="1",temp="1";
		for(int i=1;i<n;i++){
			res="";
			char c=temp[0];
			int k=1;
			for(int j=1;j<temp.size();j++){
				if(temp[j]==c){
					k++;
				}else{
                    string str=k==0?"0":"";
                    while(k){
                        str+=k%10+'0';
                        k/=10;
                    }
                    reverse(str.begin(),str.end());
					res+=str;
					res+=c;
					c=temp[j];
                    k=1;
				}
			}
			string str=k==0?"0":"";
            while(k){
                str+=k%10+'0';
                k/=10;
            }
            reverse(str.begin(),str.end());
			res+=str;
            res+=c;
			temp=res;
		}
		return res;
    }
};
/* 
请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

实现词典类 WordDictionary ：

    WordDictionary() 初始化词典对象
    void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
    bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；
	否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
211
 */
class WordDictionary {
public:
    WordDictionary() {

    }
    
    void addWord(string word) {

    }
    
    bool search(string word) {

    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
 /* 
给你一个由若干括号和字母组成的字符串 s ，删除最小数量的无效括号，使得输入的字符串有效。
返回所有可能的结果。答案可以按 任意顺序 返回。
301
输入：s = "()())()"
输出：["(())()","()()()"]
*/
class Solution {
public:
	int maxn=0,t=0;
	unordered_set<string> res;
	string tmp="";
    vector<string> removeInvalidParentheses(string s) {
        int l=0,r=0;
		for(auto i:s){
			if(i!=')'&&i!='('){
				t++;
			}else if(i=='('){
				l++;
			}else{
				r++;
			}
		}
		t+=2*min(l,r);
		dfs(s,0);
		return vector<string>(res.begin(),res.end());
	}
	void dfs(string &s,int index){
		if(index>s.size()||tmp.size()>t){
			return;
		}
		if(isTrue(tmp)){
			if(tmp.size()>maxn){
				maxn=tmp.size();
				res.clear();
				res.emplace(tmp);
			}else if(tmp.size()==maxn){
				res.emplace(tmp);
			}
		}
		tmp+=s[index];
		dfs(s,index+1);
		tmp.pop_back();
		dfs(s,index+1);
	}
	bool isTrue(string &s){
		int l=0,r=0;
		for(auto i:s){
			if(i=='('){
				l++;
			}
			if(i==')'){
				r++;
				if(r>l){
					return false;
				}
			}
		}
		return l==r;
	}
};
/* 
给定正整数 N ，我们按任何顺序（包括原始顺序）将数字重新排序，注意其前导数字不能为零。

如果我们可以通过上述方式得到 2 的幂，返回 true；否则，返回 false
869
 */
class Solution {
public:
	string tmp;
	int visit[11]={0};
    bool reorderedPowerOf2(int n) {
		string s=to_string(n);
		return dfs(s,0);
    }
	bool dfs(string &s,int index){
        //cout<<tmp<<endl;
		if(index==s.size()){
            //cout<<tmp<<endl;
			int k=atoi(tmp.c_str());
			if(k&(k-1)){
				return false;
			}else{
				return true;
			} 
		}
		for(int i=0;i<s.size();i++){
			if(index==0&&s[i]=='0'||visit[i]==1){
				continue;
			}
			visit[i]=1;
			tmp+=s[i];
			if(dfs(s,index+1)){
                return true;
            }
			tmp.pop_back();
			visit[i]=0;
		}
        return false;
	}
};
/* 
给你一个整数数组 distance 。

从 X-Y 平面上的点 (0,0) 开始，
先向北移动 distance[0] 米，然后向西移动 distance[1] 米，向南移动 distance[2] 米，向东移动 distance[3] 米，持续移动。
也就是说，每次移动后你的方位会发生逆时针变化。

判断你所经过的路径是否相交。如果相交，返回 true ；否则，返回 false 。
335
 */
class Solution {
public:
    bool isSelfCrossing(vector<int>& distance) {
		int n=distance.size();
		
    }
};
/* 
给你一个整数数组 arr 和一个整数 difference，请你找出并返回 arr 中最长等差子序列的长度，该子序列中相邻元素之间的差等于 difference 。

子序列 是指在不改变其余元素顺序的情况下，通过删除一些元素或不删除任何元素而从 arr 派生出来的序列。
1218
 */
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
		unordered_map<int,int> mmp;
        int res=1;
		for(int i:arr){
			mmp[i]=max(mmp[i-difference]+1,mmp[i]);
			res=max(mmp[i],res);
		}
		return res;
    }
};
/* 
你在和朋友一起玩 猜数字（Bulls and Cows）游戏，该游戏规则如下：

写出一个秘密数字，并请朋友猜这个数字是多少。朋友每猜测一次，你就会给他一个包含下述信息的提示：

    猜测数字中有多少位属于数字和确切位置都猜对了（称为 "Bulls", 公牛），
    有多少位属于数字猜对了但是位置不对（称为 "Cows", 奶牛）。也就是说，这次猜测中有多少位非公牛数字可以通过重新排列转换成公牛数字。

给你一个秘密数字 secret 和朋友猜测的数字 guess ，请你返回对朋友这次猜测的提示。

提示的格式为 "xAyB" ，x 是公牛个数， y 是奶牛个数，A 表示公牛，B 表示奶牛。

请注意秘密数字和朋友猜测的数字都可能含有重复数字。
299
 */
class Solution {
public:
    string getHint(string secret, string guess) {
		int A=0,B=0,n=secret.size();
		vector<int> t1(26,0),t2(26,0);
		for(int i=0;i<n;i++){
			t1[secret[i]-'a']++;
			t2[guess[i]-'a']++;
		}
		for(int i=0;i<26;i++){
			B+=min(t1[i],t2[i]);
		}
		for(int i=0;i<n;i++){
			if(secret[i]==guess[i]){
				A++;
				B--;
			}
		}
    }
};
/* 
给出两个整数 n 和 k，找出所有包含从 1 到 n 的数字，且恰好拥有 k 个逆序对的不同的数组的个数。

逆序对的定义如下：对于数组的第i个和第 j个元素，如果满i < j且 a[i] > a[j]，则其为一个逆序对；否则不是。

由于答案可能很大，只需要返回 答案 mod 109 + 7 的值。
 */
class Solution {
public:
    int kInversePairs(int n, int k) {
					
    }
};
/* 
我们正在玩一个猜数游戏，游戏规则如下：

    我从 1 到 n 之间选择一个数字。
    你来猜我选了哪个数字。
    如果你猜到正确的数字，就会 赢得游戏 。
    如果你猜错了，那么我会告诉你，我选的数字比你的 更大或者更小 ，并且你需要继续猜数。
    每当你猜了数字 x 并且猜错了的时候，你需要支付金额为 x 的现金。如果你花光了钱，就会 输掉游戏 。

给你一个特定的数字 n ，返回能够 确保你获胜 的最小现金数，不管我选择那个数字 。
375
 */
class Solution {
public:
    int getMoneyAmount(int n) {

    }
};
/* 
给你一个数组 rectangles ，其中 rectangles[i] = [xi, yi, ai, bi] 表示一个坐标轴平行的矩形。这个矩形的左下顶点是 (xi, yi) ，右上顶点是 (ai, bi) 。

如果所有矩形一起精确覆盖了某个矩形区域，则返回 true ；否则，返回 false 。
391
 */
class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {

    }
};
/* 
给定一个字符串数组 words，找到 length(word[i]) * length(word[j]) 的最大值，并且这两个单词不含有公共字母。
你可以认为每个单词只包含小写字母。如果不存在这样的两个单词，返回 0。
318
 */
class Solution {
public:
    int maxProduct(vector<string>& words) {
		int n=words.size();
		vector<int> vec;
		for(auto i:words){
			int t=0;
			for(auto c:i){
				t|=(1<<(c-'a'));	
			}
			vec.emplace_back(t);
		}
		int res=0;
		for(int i=0;i<n;i++){
			for(int j=i+1;j<n;j++){
				if((vec[i]&vec[j])==0){
                    int len=words[i].size()*words[j].size();
                    res=max(len,res);
                }
			}
		}
		return res;
    }
};
/* 
给定一个二叉树，计算 整个树 的坡度 。

一个树的 节点的坡度 定义即为，该节点左子树的节点之和和右子树节点之和的 差的绝对值 。
如果没有左子树的话，左子树的节点之和为 0 ；没有右子树的话也是一样。空结点的坡度是 0 。

整个树 的坡度就是其所有节点的坡度之和。
563
 */
class Solution {
public:
	int res=0;
    int findTilt(TreeNode* root) {
		dfs(root);
		return res;
    }
	int dfs(TreeNode* root){
		if(root==nullptr){
			return 0;
		}
		int l=0,r=0;
		if(root->left){
			l=dfs(root->left);
		}
		if(root->right){
			r=dfs(root->right);
		}
		res+=abs(l-r);
		return l+r+root->val;
	}
};
/* 
给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。

实现 Solution class:

    Solution(int[] nums) 使用整数数组 nums 初始化对象
    int[] reset() 重设数组到它的初始状态并返回
    int[] shuffle() 返回数组随机打乱后的结果

384
 */
class Solution {
public:
    Solution(vector<int>& nums) {
		vec=nums;
		now=nums;
    }
    
    vector<int> reset() {
		return vec;
    }
    
    vector<int> shuffle() {
		
    }
	map<int,int> mp;
	vector<int> vec,now;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
 /* 
 我们定义，在以下情况时，单词的大写用法是正确的：

    全部字母都是大写，比如 "USA" 。
    单词中所有字母都不是大写，比如 "leetcode" 。
    如果单词不只含有一个字母，只有首字母大写， 比如 "Google" 。

给你一个字符串 word 。如果大写用法正确，返回 true ；否则，返回 false 。
520
  */
class Solution {
public:
    bool detectCapitalUse(string word) {
		if(word[0]>='a'){
            //首字母小写
			for(int i=1;i<word.size();i++){
				if(word[i]<'a'){
					return false;
				}
			}
		}else if(word.size()>1){
			if(word[1]>='a'){
				for(int i=2;i<word.size();i++){
					if(word[i]<'a'){
						return false;
					}
				}
			}else{
				for(int i=2;i<word.size();i++){
					if(word[i]>='a'){
						return false;
					}
				}
			}
		}
		return true;
    }
};
/* 
给你一个字符串 s ，其中包含字母顺序打乱的用英文单词表示的若干数字（0-9）。按 升序 返回原始的数字
423
 */
class Solution {
public:
	string temp;
	vector<int> res;
	vector<string> vsrc={"zero","one","two","three","four","five","six","seven","eight","nine"};
    string originalDigits(string s) {
        vector<int> visit(s.size(),0);
		dfs(s,0,visit);
        sort(res.begin(),res.end());
        string ans="";
        for(int i:res){
            ans+=i+'0';
        }
		return ans;
    }
	void dfs(string s,int index,vector<int> &visit){
		if(temp.size()>0){
			if(temp[0]!='z'&&temp[0]!='o'&&temp[0]!='t'&&temp[0]!='f'&&temp[0]!='s'&&temp[0]!='e'&&temp[0]!='n'){
				return;
			}
		}
		if(temp.size()>=3&&temp.size()<=5){
			int i=0;
			for(;i<10;i++){
				if(vsrc[i]==temp){
                    //cout<<temp<<" ";
					res.emplace_back(i);
					temp="";
					break;
				}
			}
		}
        if(temp.size()>5){
            return;
        }
		if(index==s.size()){
			return;
		}
		for(int i=0;i<s.size();i++){
            if(visit[i]==1){
                continue;
            }
            visit[i]=1;
			temp+=s[i];
			dfs(s,index+1,visit);
            if(temp.empty()){
                break;
            }else{
                temp.pop_back();
            }
            visit[i]=0;
		}
	}
};
/* 
有 buckets 桶液体，其中 正好 有一桶含有毒药，其余装的都是水。它们从外观看起来都一样。
为了弄清楚哪只水桶含有毒药，你可以喂一些猪喝，通过观察猪是否会死进行判断。
不幸的是，你只有 minutesToTest 分钟时间来确定哪桶液体是有毒的。

喂猪的规则如下：

    选择若干活猪进行喂养
    可以允许小猪同时饮用任意数量的桶中的水，并且该过程不需要时间。
    小猪喝完水后，必须有 minutesToDie 分钟的冷却时间。在这段时间里，你只能观察，而不允许继续喂猪。
    过了 minutesToDie 分钟后，所有喝到毒药的猪都会死去，其他所有猪都会活下来。
    重复这一过程，直到时间用完。

给你桶的数目 buckets ，minutesToDie 和 minutesToTest ，返回在规定时间内判断哪个桶有毒所需的 最小 猪数。
458
 */
class Solution {
public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
		int n=minutesToTest/minutesToDie+1;
		int pig=1;
		while(pow(buckets,pig)>n){
			pig++;
		}
		return pig;
    }
};
/* 
给你一个按递增顺序排序的数组 arr 和一个整数 k 。数组 arr 由 1 和若干 素数  组成，且其中所有整数互不相同。

对于每对满足 0 < i < j < arr.length 的 i 和 j ，可以得到分数 arr[i] / arr[j] 。

那么第 k 个最小的分数是多少呢?  以长度为 2 的整数数组返回你的答案, 这里 answer[0] == arr[i] 且 answer[1] == arr[j] 。
786
 */
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
		
    }
};
/* 
给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...] 中找出并返回第 n 位数字。
400
 */
class Solution {
public:
    int findNthDigit(int n) {
		/* 
		1-9      9
		10-99    180
		100-999  2700
		1000-9999 36000
		 */
		int k=9;
		int t=1;
		while(n>k*t){
			n-=k*t;
			k*=10;
			t++;
		}
		int m=pow(10,t-1);
		while(n>=t){
			m++;
			n-=t;
		}
		k=pow(10,n);
		return m/n;
    }
};
/* 
有一组 n 个人作为实验对象，从 0 到 n - 1 编号，其中每个人都有不同数目的钱，以及不同程度的安静值（quietness）。
为了方便起见，我们将编号为 x 的人简称为 "person x "。

给你一个数组 richer ，其中 richer[i] = [ai, bi] 表示 person ai 比 person bi 更有钱。
另给你一个整数数组 quiet ，其中 quiet[i] 是 person i 的安静值。richer 中所给出的数据 逻辑自恰
（也就是说，在 person x 比 person y 更有钱的同时，不会出现 person y 比 person x 更有钱的情况 ）。

现在，返回一个整数数组 answer 作为答案，其中 answer[x] = y 的前提是，
在所有拥有的钱肯定不少于 person x 的人中，person y 是最安静的人（也就是安静值 quiet[y] 最小的人）。
851
 */
class Solution {
public:
	map<int,vector<int>> next;
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {	
		int n=quiet.size();
		vector<int> head(n,1),res(n,n);
		for(auto vec:richer){
			next[vec[1]].emplace_back(vec[0]);
			head[vec[1]]=0;
		}
		for(int i=0;i<n;i++){
			if(head[i]==1){
				dfs(i,quiet,res);
			}
		}
		map<int,int> help;
		for(int i=0;i<n;i++){
			help[quiet[i]]=i;
		} 
		for(int i=0;i<n;i++){
			res[i]=help[res[i]];
		}
		return res;
    }
	int dfs(int i,vector<int> &quiet,vector<int> &res){
		int m=quiet[i];
		for(auto j:next[i]){
			m=min(dfs(j,quiet,res),m);
		}
		res[i]=min(m,res[i]);
		return m;
	}
};
/* 
冬季已经来临。 你的任务是设计一个有固定加热半径的供暖器向所有房屋供暖。

在加热器的加热半径范围内的每个房屋都可以获得供暖。

现在，给出位于一条水平线上的房屋 houses 和供暖器 heaters 的位置，请你找出并返回可以覆盖所有房屋的最小加热半径。

说明：所有供暖器都遵循你的半径标准，加热的半径也一样。
475
 */
class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters) {
		
    }
};
/* 
有一棵特殊的苹果树，一连 n 天，每天都可以长出若干个苹果。
在第 i 天，树上会长出 apples[i] 个苹果，这些苹果将会在 days[i] 天后（也就是说，第 i + days[i] 天时）腐烂，变得无法食用。
也可能有那么几天，树上不会长出新的苹果，此时用 apples[i] == 0 且 days[i] == 0 表示。

你打算每天 最多 吃一个苹果来保证营养均衡。注意，你可以在这 n 天之后继续吃苹果。

给你两个长度为 n 的整数数组 days 和 apples ，返回你可以吃掉的苹果的最大数目。
1705
 */
using PII=pair<int,int>;
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
		auto cmp=[](PII A,PII B){
			return A.first>B.first;
		};
		priority_queue<PII,vector<PII>,decltype(cmp)> mpq(cmp);
		int n=apples.size(),res=0,i=0;
		for(;i<n;i++){
			if(apples[i]==0&&days[i]==0){

			}else{
				mpq.emplace(i+days[i],apples[i]);
			}
			while(!mpq.empty()&&(mpq.top().first<=i||mpq.top().second<=0)){
				mpq.pop();
			}
			if(!mpq.empty()){
				auto t=mpq.top();
				mpq.pop();
				if(--t.second>0){
					mpq.emplace(t);
				}
				res++;
			}
		}
		while(!mpq.empty()){
			while(!mpq.empty()&&(mpq.top().first<=i||mpq.top().second<=0)){
				mpq.pop();
			}
			if(!mpq.empty()){
				auto t=mpq.top();
				mpq.pop();
				if(--t.second>0){
					mpq.emplace(t);
				}
				res++;
			}
			i++;
		}
		return res;
    }
};
/* 
在社交媒体网站上有 n 个用户。给你一个整数数组 ages ，其中 ages[i] 是第 i 个用户的年龄。

如果下述任意一个条件为真，那么用户 x 将不会向用户 y（x != y）发送好友请求：

    age[y] <= 0.5 * age[x] + 7
    age[y] > age[x]
    age[y] > 100 && age[x] < 100

否则，x 将会向 y 发送一条好友请求。

注意，如果 x 向 y 发送一条好友请求，y 不必也向 x 发送一条好友请求。另外，用户不会向自己发送好友请求。

返回在该社交媒体网站上产生的好友请求总数。
825
 */
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
		sort(ages.begin(),ages.end(),greater<int>());
		int res=0;
		for(int i=0;i<ages.size();i++){
			for(int j=i+1;j<ages.size();j++){
				if(ages[j]<=0.5*ages[i]+7){
					break;
				}
				if(ages[i]<100&&ages[j]>100){
					continue;
				}
				res++;
			}
		}
		return res;
    }
};
/* 
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

    The path starts with a single slash '/'.
    Any two directories are separated by a single slash '/'.
    The path does not end with a trailing '/'.
    The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')

Return the simplified canonical path.
71
 */
class Solution {
public:
    string simplifyPath(string path) {
		stack<string> sk;
		int n=path.size();
		for(int i=0;i<n;i++){
			if(path[i]!='/'){
				string temp="";
				int j=i;
				for(;j<n&&path[j]!='/';j++){
					temp+=path[j];
				}
				if(temp==".."){
					if(!sk.empty()){
						sk.pop();
					}
				}else if(temp!="."){
					sk.emplace(temp);
				}
				i=j;
			}
		}
		string res="";
		stack<string> temp;
		while(!sk.empty()){
			temp.emplace(sk.top());
			sk.pop();
		}
		while(!temp.empty()){
			res+='/'+temp.top();
			temp.pop();
		}
		return res==""?"/":res;
    }
};
/* 
给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。

请你找出并返回只出现一次的那个数。

你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。
540
 */
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
		int n=nums.size(),left=0,right=n-1;
		while(left<right){
			int mid=left+(right-left)/2;
			if(mid%2==1){
				mid--;
			}
			if(nums[mid]!=nums[mid+1]){
				right=mid;
			}else{
				left=mid+2;
			}
		}
		return left;
    }
};
/* 
n 张多米诺骨牌排成一行，将每张多米诺骨牌垂直竖立。在开始时，同时把一些多米诺骨牌向左或向右推。

每过一秒，倒向左边的多米诺骨牌会推动其左侧相邻的多米诺骨牌。同样地，倒向右边的多米诺骨牌也会推动竖立在其右侧的相邻多米诺骨牌。

如果一张垂直竖立的多米诺骨牌的两侧同时有多米诺骨牌倒下时，由于受力平衡， 该骨牌仍然保持不变。

就这个问题而言，我们会认为一张正在倒下的多米诺骨牌不会对其它正在倒下或已经倒下的多米诺骨牌施加额外的力。

给你一个字符串 dominoes 表示这一行多米诺骨牌的初始状态，其中：

    dominoes[i] = 'L'，表示第 i 张多米诺骨牌被推向左侧，
    dominoes[i] = 'R'，表示第 i 张多米诺骨牌被推向右侧，
    dominoes[i] = '.'，表示没有推动第 i 张多米诺骨牌。

返回表示最终状态的字符串。
838
 */
/*
每一秒，每一秒，BFS 
 */
class Solution {
public:
    string pushDominoes(string dominoes) {
		int n=dominoes.size();
		string temp=dominoes,res=temp;
		queue<int> mq;
		for(int i=0;i<n;i++){
			if(dominoes[i]!='.'){
				mq.emplace(i);
			}
		}
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				int f=mq.front();
				mq.pop();
				if(res[f]=='L'){
					if(f>0){
						if(res[f-1]=='.'){
							res[f-1]='L';
							mq.emplace(f-1);
						}
						if(res[f-1]=='R'&&temp[f-1]=='.'){
							res[f-1]='.';
						}
					}
				}else if(res[f]=='R'){
					if(f<n-1){
						if(res[f+1]=='.'){
							res[f+1]='R';
							mq.emplace(f+1);
						}
						if(res[f+1]=='L'&&temp[f+1]=='.'){
							res[f-1]='.';
						}
					}
				}
			}
            //cout<<res<<endl;
			temp=res;
		}
		return res;
    }
};
/* 
用一个大小为 m x n 的二维网格 grid 表示一个箱子。你有 n 颗球。箱子的顶部和底部都是开着的。

箱子中的每个单元格都有一个对角线挡板，跨过单元格的两个角，可以将球导向左侧或者右侧。

    将球导向右侧的挡板跨过左上角和右下角，在网格中用 1 表示。
    将球导向左侧的挡板跨过右上角和左下角，在网格中用 -1 表示。

在箱子每一列的顶端各放一颗球。每颗球都可能卡在箱子里或从底部掉出来。
如果球恰好卡在两块挡板之间的 "V" 形图案，或者被一块挡导向到箱子的任意一侧边上，就会卡住。

返回一个大小为 n 的数组 answer ，其中 answer[i] 是球放在顶部的第 i 列后从底部掉出来的那一列对应的下标，如果球卡在盒子里，则返回 -1 。
1706
 */
class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {

    }
};
/* 
复数 可以用字符串表示，遵循 "实部+虚部i" 的形式，并满足下述条件：

    实部 是一个整数，取值范围是 [-100, 100]
    虚部 也是一个整数，取值范围是 [-100, 100]
    i2 == -1

给你两个字符串表示的复数 num1 和 num2 ，请你遵循复数表示形式，返回表示它们乘积的字符串。
537
 */
/* 
给定一个表示整数的字符串 n ，返回与它最近的回文整数（不包括自身）。如果不止一个，返回较小的那个。

“最近的”定义为两个整数差的绝对值最小。
564
5种情况:
前半部分回，
前半部分+1回
前半部分-1回
99999
10000001
 */
class Solution {
public:
    string nearestPalindromic(string n) {
		long long t=stoll(n);
		if(t<10||to_string(t-1).size()<n.size()){
			return to_string(t-1);
		}
		long long k=stoll(n.substr(0,(n.size()+1)/2));
		long long r1=-1,r2=-1,r3=-1,r4=-1,r5=-1;
		vector<pair<long long,long long>> vec;
		if(to_string(t+1).size()>n.size()){
			r1=t+2;
			vec.emplace_back(2,t+2);
		}
		if(to_string(t-2).size()<n.size()){
			r2=t-2;
			vec.emplace_back(2,t-2);
		}
		string str;
		if(n.size()%2==0){
			str=to_string(k);
		}else{
			str=to_string(k/10);
		}
		reverse(str.begin(),str.end());
		r3=stoll(to_string(k)+str);
        if(r3!=t){
           vec.emplace_back(abs(r3-t),r3); 
        }
		if(n.size()%2==0){
			str=to_string(k+1);
		}else{
			str=to_string((k+1)/10);
		}
		reverse(str.begin(),str.end());
		r4=stoll(to_string(k+1)+str);
		vec.emplace_back(abs(r4-t),r4);
		if(n.size()%2==0){
			str=to_string(k-1);
		}else{
			str=to_string((k-1)/10);
		}
		reverse(str.begin(),str.end());
		r5=stoll(to_string(k-1)+str);
		vec.emplace_back(abs(r5-t),r5);
		auto cmp=[](auto p1,auto p2){
			if(p1.first<p2.first){
				return true;
			}else if(p1.first==p2.first){
				return p1.second<p2.second;
			}
			return false;
		};
		sort(vec.begin(),vec.end(),cmp);
		return to_string(vec[0].second);
    }
};
/* 
给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。返回这个结果。
258
 */
class Solution {
public:
    int addDigits(int num) {
		while(num/10){
			string str=to_string(num);
			num=0;
			for(auto c:str){
				num+=c-'0';
			}
		}
		return num;
    }
};
/* 
给你一个长桌子，桌子上盘子和蜡烛排成一列。给你一个下标从 0 开始的字符串 s ，
它只包含字符 '*' 和 '|' ，其中 '*' 表示一个 盘子 ，'|' 表示一支 蜡烛 。

同时给你一个下标从 0 开始的二维整数数组 queries ，
其中 queries[i] = [lefti, righti] 表示 子字符串 s[lefti...righti] （包含左右端点的字符）。
对于每个查询，你需要找到 子字符串中 在 两支蜡烛之间 的盘子的 数目 。
如果一个盘子在 子字符串中 左边和右边 都 至少有一支蜡烛，那么这个盘子满足在 两支蜡烛之间 。

    比方说，s = "||**||**|*" ，查询 [3, 8] ，表示的是子字符串 "*||**|" 。
	子字符串中在两支蜡烛之间的盘子数目为 2 ，子字符串中右边两个盘子在它们左边和右边 都 至少有一支蜡烛。

请你返回一个整数数组 answer ，其中 answer[i] 是第 i 个查询的答案。
2055
 */
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
		map<int,int> pre;
		vector<int> vec;
		for(int i=0;i<s.size();i++){
			if(s[i]=='|'){
				if(!vec.empty()){
					pre[i]+=pre[vec.back()]+i-vec.back()-1;
				}else{
					pre[i]=0;
				}
				vec.emplace_back(i);
			}
		}
        // for(auto [x,y]:pre){
        //     cout<<x<<" "<<y<<endl;
        // }
        // for(auto i:vec){
        //     cout<<i<<endl;
        // }
		vector<int> res;
		for(auto v:queries){
			if(vec.empty()||v[0]>=vec.back()||v[1]<=vec[0]){
				res.emplace_back(0);
				continue;
			}
			auto l=lower_bound(vec.begin(),vec.end(),v[0])-vec.begin();
			auto r=upper_bound(vec.begin(),vec.end(),v[1])-vec.begin()-1;
            //cout<<vec[l]<<" "<<vec[r]<<endl;
            if(l>=r){
                res.emplace_back(0);
                continue;
            }
			res.emplace_back(pre[vec[r]]-pre[vec[l]]);
		}
		return res;
    }
};
class Solution {
public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
		int n=s.size();
		vector<int> Left(n),Right(n),pre(n);
		int L=-1,R=-1;
		for(int i=0,j=n-1;i<n;i++,j--){
			if(s[i]=='*'){
				pre[i]=i==0?1:pre[i-1]+1;
			}else{
				L=i;
				pre[i]=i==0?0:pre[i-1];
			}
			if(s[j]=='|'){
				R=j;
			}
			Left[i]=L;
			Right[j]=R;
		}
		vector<int> res;
		for(auto vec:queries){
            L=Right[vec[0]],R=Left[vec[1]];
			if(L==-1||R==-1||R<=L){
				res.emplace_back(0);
			}else{
				res.emplace_back(pre[R]-pre[L]);
			}
		}
		return res;
    }
};
/* 
给你一棵根节点为 0 的 二叉树 ，它总共有 n 个节点，节点编号为 0 到 n - 1 。
同时给你一个下标从 0 开始的整数数组 parents 表示这棵树，其中 parents[i] 是节点 i 的父节点。由于节点 0 是根，所以 parents[0] == -1 。

一个子树的 大小 为这个子树内节点的数目。每个节点都有一个与之关联的 分数 。
求出某个节点分数的方法是，将这个节点和与它相连的边全部 删除 ，剩余部分是若干个 非空 子树，这个节点的 分数 为所有这些子树 大小的乘积 。

请你返回有 最高得分 节点的 数目 。
2049
 */
class Solution {
public:
	map<int,vector<int>> childnum;
    int countHighestScoreNodes(vector<int>& parents) {
		int n=parents.size();
		vector<vector<int>> tree(n);
		for(int i=0;i<n;i++){
			tree[i].emplace_back(parents[i]);
		}
		dfs(tree,0);
		int res=0,maxn=0;
		for(int i=0;i<n;i++){
			int f=n,t=1;
			for(int j:childnum[i]){
				f-=j;
				t*=j;
			}
			if(f!=0){
				t*=f;
			}
			if(t>maxn){
				res=1;
				maxn=t;
			}else if(t==maxn){
				res++;
			}
		}
		return res;
    }
	int dfs(vector<vector<int>> &tree,int root){
		int sum=1;
		for(int child:tree[root]){
			int cnum=dfs(tree,child);
			childnum[root].emplace_back(cnum);
			sum+=cnum;
		}
		return sum;
	}
};
/* 
388. 文件的最长绝对路径
如果是代码表示，上面的文件系统可以写为 "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" 。'\n' 和 '\t' 分别是换行符和制表符。

文件系统中的每个文件和文件夹都有一个唯一的 绝对路径 ，即必须打开才能到达文件/目录所在位置的目录顺序，所有路径用 '/' 连接。上面例子中，
指向 file2.ext 的 绝对路径 是 "dir/subdir2/subsubdir2/file2.ext" 。
每个目录名由字母、数字和/或空格组成，每个文件名遵循 name.extension 的格式，其中 name 和 extension由字母、数字和/或空格组成。

给定一个以上述格式表示文件系统的字符串 input ，返回文件系统中 指向 文件 的 最长绝对路径 的长度 。 如果系统中没有文件，返回 0。
388
*/
// "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
// \n \t 是一个字符

class Solution {
public:
    int lengthLongestPath(string input) {
		stack<string> sk;
		vector<int> vec;
    }
};
/* 
给你一个由若干单词组成的句子 sentence ，单词间由空格分隔。每个单词仅由大写和小写英文字母组成。

请你将句子转换为 “山羊拉丁文（Goat Latin）”（一种类似于 猪拉丁文 - Pig Latin 的虚构语言）。山羊拉丁文的规则如下：

    如果单词以元音开头（'a', 'e', 'i', 'o', 'u'），在单词后添加"ma"。
        例如，单词 "apple" 变为 "applema" 。
    如果单词以辅音字母开头（即，非元音字母），移除第一个字符并将它放到末尾，之后再添加"ma"。
        例如，单词 "goat" 变为 "oatgma" 。
    根据单词在句子中的索引，在单词最后添加与索引相同数量的字母'a'，索引从 1 开始。
        例如，在第一个单词后添加 "a" ，在第二个单词后添加 "aa" ，以此类推。

返回将 sentence 转换为山羊拉丁文后的句子。
824 
*/
class Solution {
public:
    string toGoatLatin(string sentence) {
		set<char> st={'a','A','e','E','i','I','o','O','u','U'};
		int n=sentence.size(),i=0;
		int index=1;
		string res="";
		while(i<n){
			int k=sentence.find(' ',i+1);
            string temp=sentence.substr(i,k-i);
			if(!st.count(temp[0])){
				string s=temp.substr(1);
                temp=s+temp[0];
			}
			temp+="ma";
			for(int j=0;j<index;j++){
				temp+='a';
			}
            index++;
            res+=temp+' ';
            if(k==-1){
                break;
            }
			i=k+1;
		}
        res.pop_back();
		return res;
    }
};
/* 
给定一个长度为 n 的整数数组 nums 。

假设 arrk 是数组 nums 顺时针旋转 k 个位置后的数组，我们定义 nums 的 旋转函数  F 为：

    F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]

返回 F(0), F(1), ..., F(n-1)中的最大值 。

生成的测试用例让答案符合 32 位 整数。
396
 */
class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
		int sum=accumulate(nums.begin(),nums.end(),0);
		int n=nums.size();
		int res=0;
		for(int i=0;i<n;i++){
			res+=i*nums[i];
		}
		int k=res;
		for(int i=n-1;i>0;i--){
			k-=(n-1)*nums[i];
			k+=sum-nums[i];
			res=max(res,k);
		}
		return res;
    }
};
/* 
给定一个可能含有重复元素的整数数组，要求随机输出给定的数字的索引。 您可以假设给定的数字一定存在于数组中。

注意：
数组大小可能非常大。 使用太多额外空间的解决方案将不会通过测试。
398
*/
//方法一：map
class Solution {
public:
    Solution(vector<int>& nums) {
		for(int index=0;auto i:nums){
			ump[i].emplace_back(index++);
		}
    }
    
    int pick(int target) {
		vector<int> temp;
		temp=ump[target];
		return temp[rand()%temp.size()];
    }
private:
	unordered_map<int,vector<int>> ump;
};
//方法二：蓄水池抽样
class Solution {
public:
    Solution(vector<int>& nums) {
		this->nums=nums;
    }
    
    int pick(int target) {
		int cnt=0,res=-1;
		for(int i=0;i<nums.size();i++){
			if(target==nums[i]){
				if(rand()%++cnt==0){
					res=i;
				}
			}
		}
		return res;
    }
private:
	vector<int> nums;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */
/* 
给你一个 n * n 矩阵 grid ，矩阵由若干 0 和 1 组成。请你用四叉树表示该矩阵 grid 。

你需要返回能表示矩阵的 四叉树 的根结点。

注意，当 isLeaf 为 False 时，你可以把 True 或者 False 赋值给节点，两种值都会被判题机制 接受 。

四叉树数据结构中，每个内部节点只有四个子节点。此外，每个节点都有两个属性：

    val：储存叶子结点所代表的区域的值。1 对应 True，0 对应 False；
    isLeaf: 当这个节点是一个叶子结点时为 True，如果它有 4 个子节点则为 False 。

class Node {
    public boolean val;
    public boolean isLeaf;
    public Node topLeft;
    public Node topRight;
    public Node bottomLeft;
    public Node bottomRight;
}

我们可以按以下步骤为二维区域构建四叉树：

    如果当前网格的值相同（即，全为 0 或者全为 1），将 isLeaf 设为 True ，将 val 设为网格相应的值，并将四个子节点都设为 Null 然后停止。
    如果当前网格的值不同，将 isLeaf 设为 False， 将 val 设为任意值，然后如下图所示，将当前网格划分为四个子网格。
    使用适当的子网格递归每个子节点。
427
*/
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
class Solution {
public:
    Node* construct(vector<vector<int>>& grid) {
        
    }
};
/* 
给你一个整数数组 nums 和一个整数 k ，请你返回子数组内所有元素的乘积严格小于 k 的连续子数组的数目。 
713
 */
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
		int left=0,right=0,sum=1,res=0;
		while(right<nums.size()){
			sum*=nums[right];
			while(sum>=k&&left<right){
				sum/=nums[left++];
			}
			res+=sum>=k?0:right-left+1;
			right++;
		}
		return res;
    }
};
/* 
基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一。

假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。

    例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化。

另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。

给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1 。

注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中。
433
 */
class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
		char c[4]={'A','C','G','T'};
		set<string> dir(bank.begin(),bank.end()),visit;
		queue<string> mq;
		int res=0;
		mq.emplace(start);
		visit.emplace(start);
		while(!mq.empty()){
			int len=mq.size();
			for(int i=0;i<len;i++){
				string str=mq.front();
				mq.pop();
				if(str==end){
					return res;
				}
				for(auto ch:c){
					for(int j=0;j<str.size();j++){
						string temp=str;
						temp[j]=ch;
						if(!dir.count(temp)||visit.count(temp)){
							continue;
						}
						mq.emplace(temp);
						visit.emplace(temp);
					}
				}
			}
			res++;
		}
		return -1;
    }
};
/* 
序列化是将数据结构或对象转换为一系列位的过程，以便它可以存储在文件或内存缓冲区中，或通过网络连接链路传输，以便稍后在同一个或另一个计算机环境中重建。

设计一个算法来序列化和反序列化 二叉搜索树 。 对序列化/反序列化算法的工作方式没有限制。 您只需确保二叉搜索树可以序列化为字符串，并且可以将该字符串反序列化为最初的二叉搜索树。

编码的字符串应尽可能紧凑。
449
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
	string res;
	void preorder(TreeNode* root){
		if(!root){
			return;
		}
		res+=to_string(root->val)+',';
		preorder(root->left);
		preorder(root->right);
	}
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        preorder(root);
		return res;
    }
	void splite(string str,vector<int>& ans){
		int i=0;
		while(i<str.size()){
			int k=str.find(',',i);
			ans.emplace_back(stoi(str.substr(i,k-i)));
			i=k+1;
		}
	}
	TreeNode* buildtree(vector<int>& data,int L,int R){
		if(L<0||L>=data.size()||L>R){
			return nullptr;
		}
		TreeNode* root=new TreeNode(data[L]);
		int l=-1,r=-1;
		for(int i=L;i<=R;i++){
			if(data[i]<data[L]&&l==-1){
				l=i;
			}
			if(data[i]>data[L]&&r==-1){
				r=i;
			}
		}
		root->left=buildtree(data,l,r-1<0?R:r-1);
		root->right=buildtree(data,r,R);
		return root;
	}
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<int> ans;
		splite(data,ans);
		return buildtree(ans,0,ans.size()-1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec* ser = new Codec();
// Codec* deser = new Codec();
// string tree = ser->serialize(root);
// TreeNode* ans = deser->deserialize(tree);
// return ans;
/* 
给你由 n 个小写字母字符串组成的数组 strs，其中每个字符串长度相等。

这些字符串可以每个一行，排成一个网格。例如，strs = ["abc", "bce", "cae"] 可以排列为：
944
 */
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
		int res=0;
		for(int j=0;j<strs[0].size();j++){
			bool flag=true;
			for(int i=1;i<strs.size();i++){
				if(strs[i][j]<strs[i-1][j]){
					flag=false;
					break;
				}
			}
			if(!flag){
				res++;
			}
		}
		return res;
    }
};
/* 
字符串有三种编辑操作:插入一个字符、删除一个字符或者替换一个字符。 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
面试题 01.05. 一次编辑
 */
class Solution {
public:
    bool oneEditAway(string first, string second) {
        int m=first.size(),n=second.size();
		if(abs(m-n)>1){
			return false;
		}
		if(m==n){
			int k=0;
			for(int i=0;i<m;i++){
				if(first[i]!=second[i]){
					k++;
					if(k>1){
						return false;
					}
				}
			}
		}else{
			string s1=m>n?first:second;
			string s2=m>n?second:first;
			int k=0;
			for(int i=0;i<s2.size();i++){
				if(s1[i+k]!=s2[i]){
                    i--;
					k++;
					if(k>1){
						return false;
					}
				}
			}
		}
		return true;
    }
};
/* 
给你一个区间数组 intervals ，其中 intervals[i] = [starti, endi] ，且每个 starti 都 不同 。

区间 i 的 右侧区间 可以记作区间 j ，并满足 startj >= endi ，且 startj 最小化 。

返回一个由每个区间 i 的 右侧区间 在 intervals 中对应下标组成的数组。如果某个区间 i 不存在对应的 右侧区间 ，则下标 i 处的值设为 -1 。
 */
class Solution {
public:
    vector<int> findRightInterval(vector<vector<int>>& intervals) {
		
    }
};
/* 
现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。

给定一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序 。

请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，返回 "" 。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。

字符串 s 字典顺序小于 字符串 t 有两种情况：

    在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t 。
    如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。

剑指114
 */
/* 
输入：words = ["wrt","wrf","er","ett","rftt"]
输出："wertf"
 */
class Solution {
public:
    string alienOrder(vector<string>& words) {
		int n=words.size();
		map<char,set<char>> next;
		vector<int> vin(26,0);
		set<char> st(words.back().begin(),words.back().end());
		for(int i=0;i<n-1;i++){
			st.insert(words[i].begin(),words[i].end());
			int j=0;
			while(j<min(words[i].size(),words[i+1].size())){
				if(words[i][j]!=words[i+1][j]){
                    if(!next[words[i][j]].count(words[i+1][j])){
                        next[words[i][j]].emplace(words[i+1][j]);
					    vin[words[i+1][j]-'a']++;   
                    }
                    break;
				}
                j++;
			}
            if(words[i].size()>words[i+1].size()&&j==words[i+1].size()){
                return "";
            }
		}
		queue<char> mq;
		for(int i=0;i<26;i++){
			if(st.count(i+'a')&&vin[i]==0){
				mq.emplace(i+'a');
			}
		}
		string res="";
		while(!mq.empty()){
			char c=mq.front();
            mq.pop();
			res+=c;
			for(auto ch:next[c]){
				if(--vin[ch-'a']==0){
					mq.emplace(ch);
				}
			}
		}
		return res.size()==st.size()?res:"";
    }
};
/* 
给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。

一般来说，删除节点可分为两个步骤：

    首先找到需要删除的节点；
    如果找到了，删除它。
450
 */
/* 
给你一个大小为 m x n 的矩阵 mat ，请以对角线遍历的顺序，用一个数组返回这个矩阵中的所有元素。
498
 */
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
		vector<int> res;
		int m=mat.size(),n=mat[0].size();
		for(int i=0;i<m+n-1;i++){
			if(i%2==0){
				int x=i>=m?m-1:i;
				int y=i>=m?i-m:0;
				for(;x>=0&&y<n;x--,y++){
					res.emplace_back(mat[x,y]);
				}
			}else{
				int x=i>=n?i-n:0;
				int y=i>=n?n-1:i;
				for(;x<m&&y>=0;x++,y--){
					res.emplace_back(mat[x,y]);
				}
			}
		}
		return res;
    }
};
/* 
不使用任何库函数，设计一个 跳表 。

跳表 是在 O(log(n)) 时间内完成增加、删除、搜索操作的数据结构。跳表相比于树堆与红黑树，其功能与性能相当，并且跳表的代码长度相较下更短，其设计思想与链表相似。

例如，一个跳表包含 [30, 40, 50, 60, 70, 90] ，然后增加 80、45 到跳表中，以下图的方式操作：
1206
 */
constexpr int MAX_LEVEL = 32;
constexpr double P_FACTOR = 0.25;

struct SkiplistNode {
    int val;
    vector<SkiplistNode *> forward;
    SkiplistNode(int _val, int _maxLevel = MAX_LEVEL) : val(_val), forward(_maxLevel, nullptr) {
        
    }
};

class Skiplist {
private:
    SkiplistNode * head;
    int level;
    mt19937 gen{random_device{}()};
    uniform_real_distribution<double> dis;

public:
    Skiplist(): head(new SkiplistNode(-1)), level(0), dis(0, 1) {

    }

    bool search(int target) {
        SkiplistNode *curr = this->head;
        for (int i = level - 1; i >= 0; i--) {
            /* 找到第 i 层小于且最接近 target 的元素*/
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        curr = curr->forward[0];
        /* 检测当前元素的值是否等于 target */
        if (curr && curr->val == target) {
            return true;
        } 
        return false;
    }

    void add(int num) {
        vector<SkiplistNode *> update(MAX_LEVEL, head);
        SkiplistNode *curr = this->head;
        for (int i = level - 1; i >= 0; i--) {
            /* 找到第 i 层小于且最接近 num 的元素*/
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        int lv = randomLevel();
        level = max(level, lv);
        SkiplistNode *newNode = new SkiplistNode(num, lv);
        for (int i = 0; i < lv; i++) {
            /* 对第 i 层的状态进行更新，将当前元素的 forward 指向新的节点 */
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool erase(int num) {
        vector<SkiplistNode *> update(MAX_LEVEL, nullptr);
        SkiplistNode *curr = this->head;
        for (int i = level - 1; i >= 0; i--) {
            /* 找到第 i 层小于且最接近 num 的元素*/
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        curr = curr->forward[0];
        /* 如果值不存在则返回 false */
        if (!curr || curr->val != num) {
            return false;
        }
        for (int i = 0; i < level; i++) {
            if (update[i]->forward[i] != curr) {
                break;
            }
            /* 对第 i 层的状态进行更新，将 forward 指向被删除节点的下一跳 */
            update[i]->forward[i] = curr->forward[i];
        }
        delete curr;
        /* 更新当前的 level */
        while (level > 1 && head->forward[level - 1] == nullptr) {
            level--;
        }
        return true;
    }

    int randomLevel() {
        int lv = 1;
        /* 随机生成 lv */
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }
};

class Node{
public:
	Node(int val):val(val){
		memset(next,0,sizeof(next));
	}
	Node* next[32];
	int val;
};
class Skiplist {
public:
    Skiplist() {

    }
    
    bool search(int target) {

    }
    
    void add(int num) {

    }
    
    bool erase(int num) {

    }
private:
	
};
/* 
给定一个表示分数加减运算的字符串 expression ，你需要返回一个字符串形式的计算结果。 

这个结果应该是不可约分的分数，即最简分数。 如果最终结果是一个整数，例如 2，你需要将它转换成分数形式，其分母为 1。所以在上述例子中, 2 应该被转换为 2/1。
592
 */
class Solution {
public:
    string fractionAddition(string expression) {
		vector<pair<string,string>> vps;
		pair<string,string> ps;
		if(expression[0]!='-'){
			expression="+"+expression;
		}
		string str;
		int k=1;
		for(auto c:expression){
			if(c=='/'){
				ps.first=str;
				str="";
			}else if(c=='+'||c=='-'){
				ps.second=str;
				k*=stoi(str);
				vps.emplace_back(ps);
				if(c=='-'){
					str="-";
				}else{
					str="";
				}
			}else{
				str+=c;
			}
		}
		int t=0;
		for(auto [x,y]:vps){
			t+=stoi(x)*(k/stoi(y));
		}
		if(t==0){
			return "0/1";
		}
		bool flag=false;
		if(t<0){
			t=-t;
			flag=true;
		}
		if(t>k&&t%k==0){
			
		}
    }
};
/* 
给你一个整数数组 arr ，请你将数组中的每个元素替换为它们排序后的序号。

序号代表了一个元素有多大。序号编号的规则如下：

    序号从 1 开始编号。
    一个元素越大，那么序号越大。如果两个元素相等，那么它们的序号相同。
    每个数字的序号都应该尽可能地小。
1331
 */
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
		int j=0,n=arr.size();
		vector<pair<int,int>> vec; 
		for(int i:arr){
			vec.emplace_back(i,j++);
		}
		sort(vec.begin(),vec.end());
		vector<int> res;
		int index=1;
		for(int i=0;i<n;i++){
			if(i==0||i>0&&vec[i].first==vec[i-1].first){
				res[vec[i].second]=index;
			}else{
				res[vec[i].second]=++index;
			}
		}
		return res;
    }
};
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> index(arr);
		iota(index.begin(),index.end(),0);
		sort(index.begin(),index.end(),[&](int a,int b){return arr[a]<arr[b];});
		int pre=INT_MAX,k=0;
		for(auto i:index){
			if(pre!=arr[i]) k++;
			arr[i]=k;
			pre=arr[i];
		}
		return arr;
    }
};
/* 
给定2D空间中四个点的坐标 p1, p2, p3 和 p4，如果这四个点构成一个正方形，则返回 true 。

点的坐标 pi 表示为 [xi, yi] 。输入 不是 按任何顺序给出的。

一个 有效的正方形 有四条等边和四个等角(90度角)。
593
 */
using ll=long long;
class Solution {
public:
	vector<ll> arr;
	void getLen(int x1,int y1,int x2,int y2){
		arr.emplace_back(ll(x1-x2)*(x1-x2)+ll(y1-y2)*(y1-y2));
	}
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
		getLen(p1[0],p1[1],p2[0],p2[1]);
		getLen(p1[0],p1[1],p3[0],p3[1]);
		getLen(p1[0],p1[1],p4[0],p4[1]);
		getLen(p2[0],p2[1],p3[0],p3[1]);
		getLen(p2[0],p2[1],p4[0],p4[1]);
		getLen(p3[0],p3[1],p4[0],p4[1]);
		sort(arr.begin(),arr.end());
		return arr[0]==arr[3]&&arr[4]==arr[5]&&arr[3]!=arr[4];
    }
};
/* 
设计你的循环队列实现。 循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。

循环队列的一个好处是我们可以利用这个队列之前用过的空间。
在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。但是使用循环队列，我们能使用这些空间去存储新的值。

你的实现应该支持如下操作：

    MyCircularQueue(k): 构造器，设置队列长度为 k 。
    Front: 从队首获取元素。如果队列为空，返回 -1 。
    Rear: 获取队尾元素。如果队列为空，返回 -1 。
    enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
    deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
    isEmpty(): 检查循环队列是否为空。
    isFull(): 检查循环队列是否已满。
622
 */
class MyCircularQueue {
public:
    MyCircularQueue(int k) {
		arr=vector<int>(k);
		head=0;
		tail=-1;
		len=0;
    }
    
    bool enQueue(int value) {
		if(isFull()){
			return false;
		}
		tail=(tail+1)%arr.size();
		arr[tail]=value;
		return true;
    }	
    
    bool deQueue() {
		if(isEmpty()){
			return false;
		}
		len--;
		head=(head+1)%arr.size();
		return true;
    }
    
    int Front() {
		if(isEmpty()){
			return -1;
		}
		return arr[head];
    }
    
    int Rear() {
		if(isEmpty()){
			return -1;
		}
		return arr[tail];
    }
    
    bool isEmpty() {
		return len==0;
    }
    
    bool isFull() {
		return len==arr.size();
    }
private:
	vector<int> arr;
	int head,tail,len;
};
/* 
给你一个数组 nums，请你从中抽取一个子序列，满足该子序列的元素之和 严格 大于未包含在该子序列中的各元素之和。

如果存在多个解决方案，只需返回 长度最小 的子序列。如果仍然有多个解决方案，则返回 元素之和最大 的子序列。

与子数组不同的地方在于，「数组的子序列」不强调元素在原数组中的连续性，也就是说，它可以通过从数组中分离一些（也可能不分离）元素得到。

注意，题目数据保证满足所有约束条件的解决方案是 唯一 的。同时，返回的答案应当按 非递增顺序 排列。

1403
 */
class Solution {
public:
    vector<int> minSubsequence(vector<int>& nums) {
		auto temp=nums;
		sort(temp.begin(),temp.end());
		int sum=accumulate(temp.begin(),temp.end(),0);
		map<int,int> mp;
		int k=0;
		for(int i=temp.size()-1;i>=0;i--){
			k+=temp[i];
			mp[temp[i]]++;
			if(k>sum-k){
				break;
			}
		}
		vector<int> res;
		for(auto i:nums){
			if(mp[i]>0){
				mp[i]--;
				res.emplace_back(i);
			}
		}
		return res;
    }
};