/* #include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
int main(){
    //freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n,k;
        cin>>n>>k;
        int p[n];
        for(int j=0;j<n;j++){
            cin>>p[j];
        }
        sort(p,p+n);
        int sum=0;
        int pre=0;
        for(int t=0;t<n;t++){
            pre+=p[t];
            if(pre>k){
                break;
            }
            sum+=(k-pre)/(t+1)+1;
            //cout<<sum<<" ";
        }
        cout<<sum<<endl;
    }
    return 0;
} */
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
int main(){
    //freopen("./test.txt","r",stdin);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        int n,k;
        cin>>n>>k;
        int p[n];
        for(int j=0;j<n;j++){
            cin>>p[j];
        }
        sort(p,p+n);
        long long sum=0,pre=0;
        for(int t=0;t<n;t++){
            if(p[t]+pre>k){
                break;
            }
            if(t==0){
                sum+=k-p[0]+1;
            }else{
                sum+=(k-pre-p[t])/(t+1)+1;
            }
            pre+=p[t];
            //cout<<sum<<" ";
        }
        cout<<sum<<endl;
    }
    return 0;
}