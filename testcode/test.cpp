#include "../include/head.h"
using namespace std;
int main(){
	map<int,int> mp;
	mp[0]=1;
	mp[1]=1;
	cout<<mp.size();
	mp.erase(1);
	cout<<mp.size();
	return 0;
}