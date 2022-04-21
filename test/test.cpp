#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
bool splite(string& data){
	int i=0;
    set<char> st;
	for(int i=0;i<data.size();i++){
        if(data[i]=='W'){
            if(st.size()==1){
                return false;
            }
            st.clear();
        }else{
            st.emplace(data[i]);
        }
    }
    if(st.size()==1){
        return false;
    }
    return true;
}
int main(){
    freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n;
        string str;
        cin>>n;
        cin>>str;
        //cout<<str<<endl;
        if(splite(str)==false){
            cout<<"NO"<<endl;
        }else{
            cout<<"YES"<<endl;
        }
    }
    return 0;
}
