#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n;
        cin>>n;
        vector<map<string,int>> vs(26);
        vector<int> vec(26,0);
        for(int j=0;j<n;j++){
            string str;
            cin>>str;
            vs[str[0]-'a'][str]++;
            vec[str[0]-'a']++;
            if(str[0]-'a'!=str[1]-'a'){
                vs[str[1]-'a'][str]++;
                vec[str[1]-'a']++;
            }
        }
        int ans=0;
        for(int k='a';k<='k';k++){
            int temp=0;
            for(auto [x,y]:vs[k-'a']){
                string s=x;
                s[0]=x[1];
                s[1]=x[0];
                cout<<s<<"->"<<vs[k-'a'][s]<<" ";
                if()
                temp+=y*(vec[k-'a']-y-vs[k-'a'][s]);
            }
            cout<<"-"<<temp<<endl;
            ans+=temp/2;
        }
        cout<<ans<<endl;

    }
    return 0;
}
