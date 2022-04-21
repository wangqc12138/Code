#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
int main(){
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
            vs[str[1]-'a'][str]++;
            vec[str[1]-'a']++;
        }
        int ans=0;
        for(int k='a';k<='k';k++){
            for(auto [x,y]:vs[k-'a']){
                ans+=y*(vec[k-'a']-y);
            }
        }
        cout<<ans<<endl;

    }
    return 0;
}
