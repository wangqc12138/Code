#include <bits/stdc++.h>
using namespace std;
const int MAX = 200007;
const int MOD = 1000000007;
void solve(){
    string str;
    cin>>str;
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
    if(a+c!=b&&b+c!=a){
        cout<<"no\n";
        return;
    }
    stack<char> sk;
    for(auto ch:str){
        if(ch=='?'){
            ch=a>b?')':'(';
        }
        if(ch=='('){
            sk.emplace(ch);
        }else if(ch==')'){
            if(sk.empty()){
                cout<<"no\n";
                return;
            }else{
                sk.pop();
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    freopen("./test.txt","r",stdin);
    int tt;cin>>tt;for(int i=0;i<tt;i++){solve();}
    return 0;
}
