//动态规划单串-带维度问题
/*
我们将给定的数组 A 分成 K 个相邻的非空子数组 ，我们的分数由每个子数组内的平均值的总和构成。计算我们所能得到的最大分数是多少。
注意我们必须使用 A 数组中的每一个数进行分组，并且分数不一定需要是整数。
813
*/
class Solution {
public:
    double largestSumOfAverages(vector<int>& A, int K) {
        int n=A.size(),t=0;
        vector<double> sum;
        vector<vector<double>> dp(n,vector<double>(K,0));
        for(auto i:A){
            sum.push_back(t+=i);
        }
        auto averge=[&](int i,int j){
            return i==0?sum[j]/(j+1):(sum[j]-sum[i-1])/(j-i+1);
        };
        for(int i=0;i<n;i++){
            dp[i][0]=averge(0,i);
        }
        for(int k=1;k<K;k++){
            for(int i=0;i<n;i++){
                for(int j=i-1;j>=0;j--){
                    dp[i][k]=max(dp[j][k-1]+averge(j+1,i),dp[i][k]);
                }
            }
        }
            
        return dp[n-1][K-1];       
    }
};
/*
给你 k 枚相同的鸡蛋，并可以使用一栋从第 1 层到第 n 层共有 n 层楼的建筑。
已知存在楼层 f ，满足 0 <= f <= n ，任何从 高于 f 的楼层落下的鸡蛋都会碎，从 f 楼层或比它低的楼层落下的鸡蛋都不会破。
每次操作，你可以取一枚没有碎的鸡蛋并把它从任一楼层 x 扔下（满足 1 <= x <= n）。如果鸡蛋碎了，你就不能再次使用它。如果某枚鸡蛋扔下后没有摔碎，则可以在之后的操作中 重复使用 这枚鸡蛋。
请你计算并返回要确定 f 确切的值 的 最小操作次数 是多少？
887
*/
class Solution {
public:
    int superEggDrop(int k, int n) {
        
    }
};