#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    string str;
    cin>>str;
    int n=str.size();
    int a=0,b=0,c=0;
    for(auto ch:str){
        if(ch=='('){
            a++;
        }else if(ch==')'){
            b++;
        }else{
            c++;
        }
    }
    int k=abs(a-b);
    if(k>c||str.size()%2){
        cout<<"no\n";
        return;
    }
    if(str[0]=='?'){
        str[0]='(';
        c--;
        a++;
    }
    if(str[n-1]=='?'){
        str[n-1]=')';
        c--;
        b++;
    }
    stack<char> sk;
    for(int i=0;i<n;i++){
        if(str[i]=='('){
            sk.emplace(str[i]);
        }else if(str[i]==')'){
            if(sk.empty()){
                cout<<"no\n";
                return;
            }else{
                sk.pop();
            }
        }else{
            if(sk.empty()||b-a==c){
                sk.emplace(str[i]);
            }else if(sk.top()=='?'){
                sk.pop();
            }else{
                cout<<"no\n";
                return;
            }
        }
    }
    if(sk.empty()){
        cout<<"yes\n";
    }else{
        cout<<"no\n";
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
