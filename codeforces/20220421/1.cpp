/*
For Division 1: 1900≤rating
For Division 2: 1600≤rating≤1899
For Division 3: 1400≤rating≤1599
For Division 4: rating≤1399 
 */
#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int m;
        cin>>m;
        if(m>=1900){
            cout<<"Division 4"<<endl;
        }else if(m>=1600){
            cout<<"Division 3"<<endl;
        }else if(m>=1400){
            cout<<"Division 2"<<endl;
        }else{
            cout<<"Division 1"<<endl;
        }
    }
    return 0;
}