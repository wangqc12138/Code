#include "iostream"
/* 
Sexy primes are pairs of primes of the form (p, p+6), so-named since “sex” is the Latin word for “six”. 
(Quoted from http://mathworld.wolfram.com/SexyPrimes.html)

Now given an integer, you are supposed to tell if it is a sexy prime.

Input Specification:
Each input file contains one test case. Each case gives a positive integer N (≤108 ).

Output Specification:
For each case, print in a line Yes if N is a sexy prime, then print in the next line the other sexy prime paired with N 
(if the answer is not unique, output the smaller number). 
Or if N is not a sexy prime, print No instead, then print in the next line the smallest sexy prime which is larger than N.

Sample Input 1:
47
Sample Output 1:
Yes
41

Sample Input 2:
21
Sample Output 2:
No
23 */
//素数打表
#ifdef one
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <set>
using namespace std;
set<int> primenums;
int fuc(int n);
int getPrimeNums(int n);
int main(){
	int n;
	cin>>n;
	getPrimeNums(108);
	int ret=fuc(n);
	if(ret>0){
		cout<<"Yes"<<endl;
		cout<<ret<<endl;
	}
	if(ret<0){
		cout<<"No"<<endl;
		cout<<-ret<<endl;
	}
	return 0;
}
int fuc(int n){
	if(primenums.count(n)){
		if(primenums.count(n-6)){
			return n-6;
		}
		if(primenums.count(n+6)){
			return n+6;
		}
	}
	for(auto i:primenums){
		if(i>n){
			if(primenums.count(i+6)){
				return -i;
			}
		}
	}
	return 0;
}
//打表
int getPrimeNums(int n){
	vector<int> isPrime(n+1,1);
	for(int i=2;i<=n;i++){
		if(isPrime[i]==0){
			continue;
		}
		primenums.emplace(i);
		for(int j=i*i;j<=n;j+=i){
			isPrime[j]=0;
		}
	}
	return 0;
}
#endif
/* 
Zhejiang University is about to celebrate her 122th anniversary in 2019. To prepare for the celebration, the alumni association （校友会） has gathered the ID’s of all her alumni. Now your job is to write a program to count the number of alumni among all the people who come to the celebration.

Input Specification:
Each input file contains one test case. For each case, the first part is about the information of all the alumni. Given in the first line is a positive integer N (≤105 ). Then N lines follow, each contains an ID number of an alumnus. An ID number is a string of 18 digits or the letter X. It is guaranteed that all the ID’s are distinct.

The next part gives the information of all the people who come to the celebration. Again given in the first line is a positive integer M (≤105 ). Then M lines follow, each contains an ID number of a guest. It is guaranteed that all the ID’s are distinct.

Output Specification:
First print in a line the number of alumni among all the people who come to the celebration. Then in the second line, print the ID of the oldest alumnus – notice that the 7th - 14th digits of the ID gives one’s birth date. If no alumnus comes, output the ID of the oldest guest instead. It is guaranteed that such an alumnus or guest is unique.

Sample Input:
5
372928196906118710
610481197806202213
440684198612150417
13072819571002001X
150702193604190912
6
530125197901260019
150702193604190912
220221196701020034
610481197806202213
440684198612150417
370205198709275042
Sample Output:
3
150702193604190912
 */
#ifdef two
#include<iostream>
#include<map>
#include<set>
using namespace std;
int main(){
	int n;
	set<string> stu;
	map<int,string> mmp1,mmp2;
	cin>>n;
	string temp;
	for(int i=0;i<n;i++){
		cin>>temp;
		stu.emplace(temp);
		int ttemp=stoi(temp.substr(6,8));
		mmp1.emplace(ttemp,temp);
	}
	cin>>n;
	int res=0;
	for(int i=0;i<n;i++){
		cin>>temp;
		if(stu.count(temp)){
			res++;
		}
		int ttemp=stoi(temp.substr(6,8));
		mmp2.emplace(ttemp,temp);
	}
	if(res!=0){
		cout<<res<<endl<<mmp1.begin()->second<<endl;
	}else{
		cout<<res<<endl<<mmp2.begin()->second<<endl;
	}
	return 0;
}
#endif
/* 
Telefraud（电信诈骗） remains a common and persistent problem in our society. In some cases, unsuspecting victims lose their entire life savings. To stop this crime, you are supposed to write a program to detect those suspects from a huge amount of phone call records.

A person must be detected as a suspect if he/she makes more than K short phone calls to different people everyday, but no more than 20% of these people would call back. And more, if two suspects are calling each other, we say they might belong to the same gang. A makes a short phone call to B means that the total duration of the calls from A to B is no more than 5 minutes.

Input Specification:
Each input file contains one test case. For each case, the first line gives 3 positive integers K (≤500, the threshold（阈值） of the amount of short phone calls), N (≤103 , the number of different phone numbers), and M (≤105 , the number of phone call records). Then M lines of one day’s records are given, each in the format:

caller receiver duration

where caller and receiver are numbered from 1 to N, and duration is no more than 1440 minutes in a day.

Output Specification:
Print in each line all the detected suspects in a gang, in ascending order of their numbers. The gangs are printed in ascending order of their first members. The numbers in a line must be separated by exactly 1 space, and there must be no extra space at the beginning or the end of the line.

If no one is detected, output None instead.
Sample Input 1:
5 15 31
1 4 2
1 5 2
1 5 4
1 7 5
1 8 3
1 9 1
1 6 5
1 15 2
1 15 5
3 2 2
3 5 15
3 13 1
3 12 1
3 14 1
3 10 2
3 11 5
5 2 1
5 3 10
5 1 1
5 7 2
5 6 1
5 13 4
5 15 1
11 10 5
12 14 1
6 1 1
6 9 2
6 10 5
6 11 2
6 12 1
6 13 1
Sample Output 1:
3 5
6
Note: In sample 1, although 1 had 9 records, but there were 7 distinct receivers, among which 5 and 15 both had conversations lasted more than 5 minutes in total. Hence 1 had made 5 short phone calls and didn’t exceed the threshold 5, and therefore is not a suspect.

Sample Input 2:
5 7 8
1 2 1
1 3 1
1 4 1
1 5 1
1 6 1
1 7 1
2 1 1
3 1 1
Sample Output 2:
None
 */
#ifdef three
#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int M,N,K;
	int from,to,m;
	cin>>M>>N>>K;
	vector<vector<int>> vec1(N+1,vector<int>(N+1,-1));
	vector<int> vec2(N+1,0);
	vector<int> vec3;
	set<int> ms;
	for(int i=0;i<K;i++){
		cin>>from>>to>>m;
		if(m<=5&&vec1[from][to]==-1){
			vec2[from]++;
		}
		vec1[from][to]=m;
	}
	for(int i=1;i<=N;i++){
		if(vec2[i]>=M){
			int temp=0;
			for(int j=1;j<=N;j++){
				if(vec1[j][i]!=-1&&vec1[i][j]!=-1&&vec1[i][j]<=5){
					temp++;
				}
			}
			if(temp<vec2[i]*0.2){
				vec3.emplace_back(i);
			}
		}
	}
	if(vec3.empty()){
		cout<<"None";
	}
	sort(vec3.begin(),vec3.end());
	for(int i=0;i<vec3.size();i++){
		int m=vec3[i];
		if(ms.count(m)){
			continue;
		}
		if(i!=0){
			cout<<endl;
		}
		cout<<m;
		ms.emplace(m);
		for(int j=i;j<vec3.size();j++){
			int n=vec3[j];
			if(vec1[m][n]!=-1){
				ms.emplace(n);
				cout<<" "<<n;
			}
		}
	}
	return 0;
}
#endif