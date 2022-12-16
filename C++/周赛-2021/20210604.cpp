#include <iostream>
using namespace std;
bool process(int x[4],int y[4]){
    int kx[6],ky[6];
    for(int j=3;j>0;j++){
        for(int i=0;i<j;i++){
            kx[i]=x[3-j]-x[i];
            ky[i]=y[3-j]-y[i];
        }
    }
    int res=0;
    for(int i=0;i<5;i++){
        for(int j=i+1;j<6;j++){
            if(kx[i]*ky[j]==ky[i]*kx[j]){
                res++;
            }
        }
    }
    return res==1;
}
int main(){
    int n;
    int x[4],y[4];
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            cin>>x[j]>>y[j];
        }
        if(process(x,y)){
            cout<<"TRUE"<<endl;
        }else{
            cout<<"FALSE"<<endl;
        }
    }
    return 0;
}
//C
#include <iostream>
#include <algorithm>
#include <numeric>
#include <queue>
#include <iomanip>
using namespace std;
double process(priority_queue<double> &x,double k,double sum){
    int top=x.top();
    x.pop();
    sum-=top;
    top=(top+k)/2.00;
    x.emplace(top);
    sum+=top;
    return sum;
}
int main(){
    int m,n;
    priority_queue<double> x;
    cin>>m>>n;
    double k;
    double sum=0;
    for(int i=0;i<m;i++){
        cin>>k;
        sum+=k;
        x.emplace(k);
    }
    for(int i=0;i<n;i++){
        cin>>k;
        double res=process(x,k,sum);
        printf("%.2f\n", res);
    }
    return 0;
}
//B
#include<iostream>
using namespace std;
int process(string str){
    int an=0;
    int sum=0;
    for(char c:str){
        if(c=='b'){
            sum+=(an+an-1)/2;
        }else{
            an++;
        }
    }
    return sum;
}
int main(){
    string str;
    cin>>str;
    string s1="a"+str;
    string s2=str+"b";
    cout<<max(process(s1),process(s2));
    return 0;
}
//D
#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
using ULL= unsigned long long;
class node{
public:
    node(int f,int t,ULL):from(f),to(t),weight(t){};
    bool operator < (const node &n) const{
        return weight<n.weight;
    }
private:
    int from;
    int to;
    ULL weight;
};
int main(){
    ULL n,k;
    vector<ULL> vec;
    vector<vector<ULL>> edge;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>k;
        vec.emplace_back(k);
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(vec[i]&vec[j]!=0){
                edge.emplace_back(vec[i],vec[j],vec[i]+vec[j]);
            }
        }
    }
    return 0;
}