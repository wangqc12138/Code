#include <bits/stdc++.h>
using namespace std;
long long process(long long a[],long long L,long long R){
    long long mid=(R-L)/2+L;
    long long help[R-L+1];
    long long i=L,j=mid+1,index=0;
    long long res=0;
    while(i<=mid&&j<=R){
        if(a[i]>=a[j]){
            help[index++]=a[j++];
            res+=mid-i+1;
        }else{
            help[index++]=a[i++];
        }
    }
    while(i<=mid){
        help[index++]=a[i++];
    }
    while(j<=R){
        help[index++]=a[j++];
    }
    //cout<<L<<"->"<<R<<endl;
    for(long long i=L;i<=R;i++){
        a[i]=help[i-L];
        //cout<<a[i]<<" ";
    }
    //cout<<endl<<res<<endl;
    return res;
}
long long mergesort(long long a[],long long L,long long R){
    if(L>=R){
        return 0;
    }
    long long mid=(R-L)/2+L;
    return (long long)mergesort(a,L,mid)+mergesort(a,mid+1,R)+process(a,L,R);
}
long long main(){
    freopen("./test.txt","r",stdin);
    long long T;
    cin>>T;
    while(T--){
        long long N;
        cin>>N;
        long long a[N];
        for(long long i=0;i<N;i++){
            cin>>a[i];
        }
        long long ans=mergesort(a,0,N-1);
        cout<<ans<<endl;
    }
    return 0;
}
