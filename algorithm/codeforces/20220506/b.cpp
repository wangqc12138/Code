#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int M;
    cin>>M;
    while(M--){
        int len;
        cin>>len;
        string str;
        cin>>str;
        int N;
        cin>>N;
        vector<int> index(26,0);
        for(int i=0;i<N;i++){
            char c;
            cin>>c;
            index[c-'a']=1;
        }
        int ans=0;
        for(int i=0;i<len;i++){
            string temp;
            for(int j=0;j<str.size();i++){
                if(index[str[j]-'a']==1&&!temp.empty()){
                    temp.pop_back();
                }
                temp.push_back(str[j]);
            }
            if(str==temp){
                cout<<i<<endl;
                break;
            }
            str=temp;
        }
    }
    return 0;
}