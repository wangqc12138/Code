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
