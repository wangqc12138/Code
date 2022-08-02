#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
#define bit(x,i)(((x)>>(i))&1)
using ll=long long;
using pii=pair<int,int>;
void solve(){
    int n,index=0;
    cin>>n;
    vector<int> vec(n);
    for(int i=0;i<n;i++){
        int x,k;
        cin>>x;
        k=x%10;
        if(k==0||k==5){
            if(k==5)x+=5;
            vec[i]=x;
            index=1;
            continue;
        }
        while(k!=2){
            x+=k;
            k=x%10;
        }
        vec[i]=x;
    }
    if(index==1){
        for(int i=1;i<n;i++){
            if(vec[i]!=vec[i-1]){cout<<"no\n";return;}
        }
    }else{
        for(int i=1;i<n;i++){
            if(abs(vec[i]-vec[i-1])%20!=0){cout<<"no\n";return;}
        }
    }
    cout<<"yes\n";
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
/* 
0->0
1->2->4->8->6->2
2->4->8->6->2
3->6->2->4->8->6
4->8->6->2->4
5->0->0
6->2->4->8->6
7->4->8->6->2->4
8->6->2->4->8
9->8->6->2->4->8
 */