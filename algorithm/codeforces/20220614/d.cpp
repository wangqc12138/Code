#include <bits/stdc++.h>
using namespace std;
int main(){
    freopen("./test.txt","r",stdin);
    int T;
    cin>>T;
    set<int> all={70,140,210,280,350,601,671,741,811,881,951,1202,1272,1342,1412};
    while(T--){
        string str;
        int t;
        cin>>str>>t;
        int h,m;
        sscanf(str.c_str(),"%d:%d",&h,&m);
        set<int> visit;
        int time=h*60+m,ans=0;
        while(visit.count(time)){
            if(all.count(time)){
                ans++;
            }
            time+=t;
            time%=1440;
        }
        cout<<ans<<endl;
    }
    return 0;
}