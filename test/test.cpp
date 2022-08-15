#include <bits/stdc++.h>
using namespace std;

pthread_t thread;
class node{
public:
    int k;
};
map<string,node*> mp;
void *fn(void * arg)
{
    node *n= (node*) arg;
    cout<<n->k<<endl;
    n->k=3;
    return nullptr;
}

int test(char* msg,vector<string>& fileRecord)
{
	char szTmp[256] = {0};
	int  iCount = 0;	
	fileRecord.clear();	
	char szMsg[1024] = {0};
	//最后还有个\n 字符 所以减2
	if(msg[0] != '{' || msg[strlen(msg) - 2] != '}') //不是一条完整的stat语句
		return -1;	
	
	char* p = strstr(msg, "warn_msg");
	if(p == NULL)
		return -2;
	else
		strcpy(szMsg,p+10); //10是warnMsg":"的长度
	//把最后的"}\n 去掉
	szMsg[strlen(szMsg) - 3] = '\0';
	
	p --;
	*p = '\0';
	p --;
	*p = '}';
	
  	p = strchr(msg, ':');
  	if(p == NULL)
  		return -3;//格式不对
  	else
  		p++;
  	
  	if(*p == '"')
  		p++;
  	
	char* q = strchr(p, ',');
	if(q == NULL)
		return -4;
	
	iCount = q - p ;	
	strncpy(szTmp,p,iCount);
	szTmp[iCount] = '\0';
	if(szTmp[iCount -1] == '"')
		szTmp[iCount -1] = '\0';
	fileRecord.push_back(szTmp);
	
	while(1)
	{
		p = strchr(q, ':');
		if(p == NULL)
			break;
		else
		{
			p++;
			if(*p == '"') p++;
		}
		q = strchr(p, ',');
		if(q == NULL)
		{
			strcpy(szTmp,p);
			if(szTmp[strlen(szTmp) - 1] == '}')
				szTmp[strlen(szTmp) - 1] = '\0';
			
			if(szTmp[strlen(szTmp) - 1] == '"')
				szTmp[strlen(szTmp) - 1] = '\0';
			
			fileRecord.push_back(szTmp);
			break;
		}
		else
		{
			iCount = q - p ;	
			strncpy(szTmp,p,iCount);
			szTmp[iCount] = '\0';
			if(szTmp[iCount -1] == '"')
				szTmp[iCount -1] = '\0';
			fileRecord.push_back(szTmp);
		}
	}  
	fileRecord.push_back(szMsg);
	for(int i=0;i<fileRecord.size();i++)
    {
		printf("wqc fileRecord[%d]: %s\n",i,fileRecord[i].c_str());
	}
	return 0;
}
int main()
{
    map<int,int> mp;
	mp[1]=1;
	mp.insert(map<int,int>::value_type(1,2));
	cout<<mp[1]<<endl;
}