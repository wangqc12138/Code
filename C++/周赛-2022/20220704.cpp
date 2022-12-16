#include "head.h"
/* 

 */
class Solution {
public:
    string decodeMessage(string key, string message) {
        unordered_map<char,char> ump;
        ump.clear();
        char v='a';
        for(auto c:key){
            if(ump.size()==26){
                break;
            }
            if(c!=' '&&!ump.count(c)){
                ump[c]=v++;
            }
        }
        for(auto &c:message){
            if(c!=' '){
                c=ump[c];
            }
        }
        return message;
    }
};
class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> res(m,vector<int>(n,-1));
        int a=0,b=0,c=m-1,d=n-1;
        while(head){
            for(int i=b;i<=d&&head;i++){res[a][i]=head->val;head=head->next;}
            a++;
            for(int i=a;i<=c&&head;i++){res[i][d]=head->val;head=head->next;}
            d--;
            for(int i=d;i>=b&&head;i--){res[c][i]=head->val;head=head->next;}
            c--;
            for(int i=c;i>=a&&head;i--){res[i][b]=head->val;head=head->next;}
            b++;
        }
        return res;
    }
};
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        int arr[n],sum[n];
        sum[0]=1;
        arr[0]=0;
        for(int i=1;i<n;i++){
            arr[i]=arr[i-1];
            if(i-delay>=0){
                arr[i]+=sum[i-delay];
            }
            if(i-forget>=0){
                arr[i]-=sum[i-forget];
            }
            sum[i]+=arr[i-1];
            sum[i]%=1000000007;
            arr[i]%=1000000007;
        }
        return sum[n-1];
    }
};