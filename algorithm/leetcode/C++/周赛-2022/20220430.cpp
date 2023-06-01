#include "head.h"
class Solution {
public:
    int countPrefixes(vector<string>& words, string s) {
        int res=0;
        for(auto str:words){
            if(s.find(str)==0){
                res++;
            }
        }
        return res;
    }
};
class Solution {
public:
    int minimumAverageDifference(vector<int>& nums) {
        vector<int> sum=nums;
        int res=0,n=nums.size(),minn=INT_MAX;
        for(int i=1;i<n;i++){
            sum[i]=nums[i]+sum[i-1];
        }
        for(int i=0;i<n;i++){
            int k=abs(sum[i]/(i+1)-(sum[n-1]-sum[i])/(n-i-1));
            if(minn>k){
                minn=k;
                res=i;
            }
        }
        return res;
    }
};
class Solution {
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        set<pair<int,int>> g,w;
        vector<vector<int>> mar(m,vector<int>(n,0));
        for(auto vec:guards){
            g.emplace(vec[0],vec[1]);
            mar[vec[0]][vec[1]]=2;
        }
        for(auto vec:walls){
            w.emplace(vec[0],vec[1]);
            mar[vec[0]][vec[1]]=3;
        }
        int res=0;
        for(int i=0;i<m;i++){
            bool iswatch=false;
            for(int j=0;j<n;j++){
                if(mar[i][j]==2){
                    iswatch=true;
                }
                if(mar[i][j]==3){
                    iswatch=false;
                }
                if(mar[i][j]==0&&iswatch){
                    mar[i][j]=1;
                }
            }
            iswatch=false;
            for(int j=n-1;j>=0;j--){
                if(mar[i][j]==2){
                    iswatch=true;
                }
                if(mar[i][j]==3){
                    iswatch=false;
                }
                if(mar[i][j]==0&&iswatch){
                    mar[i][j]=1;
                }
            }
        }
        for(int j=0;j<n;j++){
            bool iswatch=false;
            for(int i=0;i<m;i++){
                if(mar[i][j]==2){
                    iswatch=true;
                }
                if(mar[i][j]==3){
                    iswatch=false;
                }
                if(mar[i][j]==0&&iswatch){
                    mar[i][j]=1;
                }
            }
            iswatch=false;
            for(int i=m-1;i>=0;i--){
                if(mar[i][j]==2){
                    iswatch=true;
                }
                if(mar[i][j]==3){
                    iswatch=false;
                }
                if(mar[i][j]==0&&iswatch){
                    mar[i][j]=1;
                }
                if(mar[i][j]==0){
                    res++;
                }
            }
        }
        return res;
    }
};
using pii=pair<int,int>;
class Solution {
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int index=0,k1=-1,k2=-1,k3=-1;
        queue<pii> mq;
        mq.emplace(m-1,n-1);
        vector<vector<int>> visit(m,vector<int>(n,0));
        visit[m-1][n-1]=1;
        vector<pii> dir={{0,1},{0,-1},{1,0},{-1,0}};
        set<pii> fire;
        while(!mq.empty()){
            int len=mq.size();
            for(int i=0;i<len;i++){
                int x=mq.front().first;
                int y=mq.front().second;
                mq.pop();
                //cout<<x<<" "<<y<<" "<<grid[x][y]<<endl;
                for(auto [a,b]:dir){
                    if(a+x<0||b+y<0||a+x>=m||b+y>=n||visit[a+x][b+y]==1||grid[a+x][b+y]==2){
                        continue;
                    }
                    if(a+x==0&&b+y==0){
                        k1=index+1;
                    }
                    if(grid[a+x][b+y]==1){
                        k2=index+1;
                        fire.emplace(a+x,b+y);
                    }
                    visit[a+x][b+y]=1;
                    mq.emplace(a+x,b+y);
                }
            }
            if(k2!=-1){
                if(k1==-1){
                    return -1;
                }
                break;
            }
            index++;
        }
        if(k1==-1){
            return -1;
        }
        if(k2==-1){
            return 1000000000;
        }
        queue<pii> mq1=queue<pii>();
        vector<vector<int>>visit1=vector<vector<int>>(m,vector<int>(n,0));
        queue<pii> mq2=queue<pii>();
        mq2.emplace(0,0);
        vector<vector<int>> visit2=vector<vector<int>>(m,vector<int>(n,0));
        visit2[0][0]=1;
        for(auto p:fire){
            mq1.emplace(p);
            visit1[p.first][p.second]=1;
        }
        index=0;
        while(index<=k2){
            int len =mq1.size();
            bool flag=false;
            for(int i=0;i<len;i++){
                int x=mq1.front().first;
                int y=mq1.front().second;
                mq1.pop();
                for(auto [a,b]:dir){
                    if(a+x<0||b+y<0||a+x>=m||b+y>=n||visit1[a+x][b+y]==1||grid[a+x][b+y]==2){
                        continue;
                    }
                    if(a+x==m-1&&b+y==n-1){
                        flag=true;
                    }
                    visit1[a+x][b+y]=1;
                    grid[a+x][b+y]=1;
                    mq1.emplace(a+x,b+y);
                }
            }
            if(index<k2-k1){
                if(grid[0][0]==1){
                    return k2-k1-1;
                }
                index++;
                continue;
            }
            len =mq2.size();
            for(int i=0;i<len;i++){
                int x=mq2.front().first;
                int y=mq2.front().second;
                mq2.pop();
                for(auto [a,b]:dir){
                    if(a+x<0||b+y<0||a+x>=m||b+y>=n||visit2[a+x][b+y]==1||grid[a+x][b+y]==2){
                        continue;
                    }
                    if(grid[a+x][b+y]==1){
                        if(a+x!=m-1||b+y!=n-1){
                            continue;
                        }
                        if(!flag){
                            continue;
                        }
                    }
                    if(x+a==m-1&&y+b==n-1){
                        return k2-k1;
                    }
                    visit2[a+x][b+y]=1;
                    mq2.emplace(a+x,b+y);
                }
            }
            index++;
        }
        cout<<k1<<" "<<k2<<endl;
        return k2-k1-1;
    }
};
