#include "head.h"
/* 
 */
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
#define INF 1000000
int main(){
    int n;
    cin>>n;
    string str;
    cin>>str;
    int ends[n+1];
    ends[1]=str[0];
    int length=1;
    for(int i=1;i<str.length();i++){
        int low=1;
        int high=length;
        while(low<high){
            int mid=(low+high)/2;
            if(ends[mid]<=str[i])
                low=mid+1;
            else
                high=mid;
        }
        if(ends[low]>str[i])
            ends[low]=str[i];
        else{
            length++;
            ends[length]=str[i];
        }
    }
    cout<<n-length;
    return 0;
}
