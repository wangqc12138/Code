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
        return res
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