#include <iostream>
<<<<<<< HEAD
using namespace std;
int count = 1;  //全局变量，计数；
int count1 = 0; //判断奇数个字母出现的次数
int Judge(char str[]);
int Circle(char str[]);
int Circle(char str[])
{
    int i, j, k, m, t;
    char a[30];
    for (i = 0; str[i] != '\0'; i++)
    {
        continue;
    }
    k = i;
    for (j = 0; j < k; j++)
    {
        a[j] = str[--i];
    }
    a[j] = '\0';
    for (i = 0; i < k; i++)
    {
        if (str[i] == a[i])
            continue;
        else
        {
            m = i + 1;
            while (m != k - i && str[i] != a[m])
            {
                count++;
                m++;
            }
            if (m == k - 1 - i && count1 == 0)
            {
                count1++;
                t = a[m];
                for (int g = m - 1; g >= (k + 1) / 2; g--)
                {
                    a[g + 1] = a[g];
                }
                a[(k + 1) / 2] = t;
            }
            else if (count1 != 0)
            {
                cout << "不是回文数" << endl;
                count = 0;
                return 0;
            }
            else
            {
                t = a[m];
                for (int g = m - 1; g >= i; g--)
                {
                    a[g + 1] = a[g];
                }
                a[i] = t;
            }
            break;
        }
    }
    if (Judge(a) == 1)
    {
        cout << "是回文数" << endl;
        for (i = 0; a[i] != '\0'; i++)
            cout << a[i];
        cout << endl;
    }
    else
    {
        Circle(a);
    }
    return count;
}
int Judge(char str[])
{
    int i, j, k;
    char b[30];
    for (i = 0; str[i] != '\0'; i++)
    {
        continue;
    }
    k = i;
    for (j = 0; j <= k; j++)
    {
        b[j] = str[--i];
    }
    b[j] = '\0';
    for (j = 0; j < k; j++)
    {
        if (str[j] == b[j])
            continue;
        else
            return 0;
    }
    return 1;
}
int main()
{
    char str[30];
    int k;
    cout << "请输入字符串" << endl;
    cin >> str;
    k = Circle(str);
    if (k != 0)
    {
        cout << k << endl;
    }
    return 0;
=======
#include <string>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <sys/types.h>
#include <sys/stat.h> 
#include <unistd.h>
using namespace std;
vector<string> ans;
string temp;
//递归版本回溯
void dfs1(vector<string>& vstr,int index){
	if(index==vstr.size()){
		ans.emplace_back(temp);
		return;
	}
	for(int i=0;i<vstr[index].size();i++){
		temp+=vstr[index][i];
		dfs1(vstr,index+1);
		temp.pop_back();
	}
}
//非递归版本 BFS
void bfs(vector<string>& vstr){
	queue<string> mq;
	int index=0;
	//加入一个假定的头-空字符串
	mq.emplace("");
	while(index<vstr.size()){
		int len=mq.size();
		//将队列的字符串弹出加index层的元素
		for(int i=0;i<len;i++){
			auto f=mq.front();
			mq.pop();
			//再将拼装后的加入队列
			for(int j=0;j<vstr[index].size();j++){
				mq.emplace(f+vstr[index][j]);
			}
		}
		cout<<"第"<<index<<"层:"<<endl;
		queue<string> t=mq;
		int k=0;
		while(!t.empty()){
			cout<<t.front()<<" ";
			if(++k%10==0){
				cout<<endl;
			}
			t.pop();
		}
		cout<<endl;
		index++;
	}
	while(!mq.empty()){
		ans.emplace_back(mq.front());
		mq.pop();
	}
} 
//非递归-dfs
void dfs2(vector<string>& vstr){
	stack<pair<string,int>> msk;
	msk.emplace("",0);
	while(!msk.empty()){
		auto psi=msk.top();
		int len=psi.first.size();
		int index=psi.second;
		if(len==vstr.size()){
			ans.emplace_back(psi.first);
			msk.pop();
			continue;
		}
		if(index==vstr[len].size()){
			msk.pop();
			continue;
		}
		psi.first+=vstr[len][index];
		psi.second=0;
		msk.top().second++;
		msk.emplace(psi);
	}
}
int main(){
	char str[1024]={0};
	char temp[1024]={0};
	string s="12345|qwerqwer|ASDASD;";
	if(s.back()==';'){
		s.pop_back();
	}
	if(s.find(";") != string::npos){
		cout<<s.find(";")<<endl;
		//s = s.replace(s.find(";"),1,":");
	}
	cout<<s<<endl;
	//cout<<str<<endl;
	return 0;
>>>>>>> origin/main
}
