#include<bits/stdc++.h>
using namespace std;
#define bit(x,i)(((x)>>(i))&1)

int main(){
    freopen("./test.txt","r",stdin);
	int n,c;
	cin >> n >> c;
	vector<pair<int,int>>op(n);
	for(int i=0;i<n;i++)cin >> op[i].first >> op[i].second;

	vector<int>ans(n);
	for(int k=0;k<30;k++){
		array<int,2>func={0,1};
		int crr=bit(c,k);
		for(int i=0;i<n;i++){
			array<int,2>f;
			int x=bit(op[i].second,k);
			if(op[i].first==1)f={0&x,1&x};
			if(op[i].first==2)f={0|x,1|x};
			if(op[i].first==3)f={0^x,1^x};
			func={f[func[0]],f[func[1]]};
			crr=func[crr];
            cout<<crr<<" ";
			ans[i]|=crr<<k;
		}
        cout<<endl;
	}

	for(int i=0;i<n;i++)cout << ans[i] << endl;
}
