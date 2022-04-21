#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;
bool splite(string& data){
	int i=0;
    set<char> st;
	while(i<data.size()){
		int n=data.find('W',i);
        if(n-i<2){
            return false;
        }
        st.clear();
        for(int j=i;j<n;j++){
            st.emplace(data[j]);
        }
        if(st.size()==1){
            return false;
        }
		i=n+1;
	}
    return true;
}
int main(){
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n;
        string str;
        cin>>n;
        cin>>str;
        if(splite(str)==false){
            cout<<"No"<<endl;
        }else{
            cout<<"Yes"<<endl;
        }
    }
    return 0;
}
