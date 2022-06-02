#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
using namespace std;
using ll = long long;
using psll = pair<string, ll>;
class fileinfo
{
public:
    fileinfo(string name, string dir, time_t time, ll size = 0) : name(name), dir(dir), time(time), size(size){};
    string name; //文件名
    string dir;  //文件所属目录
    ll size;     //文件大小
    time_t time; //文件最后修改时间
};
class dirinfo
{
public:
    dirinfo(string name, string dir, time_t time, ll size = 0) : name(name), dir(dir), time(time), size(size){};
    string name; //目录名
    string dir;  //目录所属目录
    ll size;     //目录下总大小
    time_t time; //目录最后修改时间
};
//树
class treenode
{
public:
    treenode(string name)
    {
        this->name = name;
        this->child.clear();
    }
    string name;
    deque<treenode *> child;
};
//递归
ll dfs_lsit(treenode *root, string dir);
void printTree(treenode *root, int len = 0);
//递归排序
void sortusemerge(vector<psll> &nums);
void mergesort(vector<psll> &nums, int left, int right);
void merge(vector<psll> &nums, int left, int right);
//哈希
unordered_map<string, fileinfo *> mpFile;
unordered_map<string, dirinfo *> mpDir;
unordered_map<string, treenode *> mpTreenode;
string time2str(time_t time)
{
    char res[1024];
    struct tm *p;
    p = localtime(&time);
    sprintf(res, "%04d-%02d-%02d %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    return res;
}
string better(int size)
{
    vector<string> vec = {"B", "K", "M", "G", "T"};
    int index = 0;
    int t = size;
    while (t > 1024)
    {
        index++;
        t = t / 1024.00;
    }
    return to_string(t) + vec[index];
}
int getFileSizeAndTime(string file, ll &size, time_t &time)
{
    struct stat64 s;
    if (-1 == stat64(file.c_str(), &s))
    {
        return -1;
    }
    size = s.st_size;
    time = s.st_mtim.tv_sec;
    return 0;
}
//获取文件及目录，存放到树形结构中
ll dfs_lsit(treenode *root, string dir)
{
    DIR *dDir;
    struct dirent *dp;
    if ((dDir = opendir(dir.c_str())) == NULL)
    {
        return -1;
    }
    ll sumSize = 0;
    while ((dp = readdir(dDir)))
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
        {
            continue;
        }
        string temp = dir + "/" + dp->d_name;
        ll size = 0;
        time_t time = 0;
        if (-1 == getFileSizeAndTime(temp, size, time))
        {
            continue;
        }
        if (dp->d_type == 8)
        {
            treenode *chnode = new treenode(temp);
            root->child.emplace_front(chnode);
            mpFile[temp] = new fileinfo(dp->d_name, dir, time, size);
            mpTreenode[temp] = chnode;
            sumSize += size;
        }
        if (dp->d_type == 4)
        {
            treenode *chnode = new treenode(temp);
            root->child.emplace_back(chnode);
            size = dfs_lsit(chnode, temp);
            mpDir[temp] = new dirinfo(dp->d_name, dir, time, size);
            mpTreenode[temp] = chnode;
            sumSize += size;
        }
    }
    return sumSize;
}
//打印出树形结构
void printTree(treenode *root, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (i == len - 1)
        {
            cout << "└──";
        }
        else
        {
            cout << "   ";
        }
    }
    if (mpFile.count(root->name))
    {
        auto ff = mpFile[root->name];
        printf("f %s %5s %s\n", time2str(ff->time).c_str(), better(ff->size).c_str(), ff->name.c_str());
        return;
    }
    auto df = mpDir[root->name];
    printf("d %s %5s %s\n", time2str(df->time).c_str(), better(df->size).c_str(), df->name.c_str());
    for (auto treenode : root->child)
    {
        printTree(treenode, len + 1);
    }
}
//排序,按照second元素排序从小到大
void sortusemerge(vector<psll> &nums)
{
    int n = nums.size();
    mergesort(nums, 0, n - 1);
}
void mergesort(vector<psll> &nums, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = left + (right - left) / 2;
    mergesort(nums, left, mid);
    mergesort(nums, mid + 1, right);
    merge(nums, left, right);
}
void merge(vector<psll> &nums, int left, int right)
{
    vector<pair<string, int>> help(right - left + 1);
    int mid = left + (right - left) / 2;
    int p1 = left, p2 = mid + 1, index = 0;
    while (p1 <= mid && p2 <= right)
    {
        if (nums[p1].second <= nums[p2].second)
        {
            help[index++] = nums[p1++];
        }
        else
        {
            help[index++] = nums[p2++];
        }
    }
    while (p1 <= mid)
    {
        help[index++] = nums[p1++];
    }
    while (p2 <= right)
    {
        help[index++] = nums[p2++];
    }
    for (int i = 0; i <= right - left; i++)
    {
        nums[left + i] = help[i];
    }
}
//打印目录，可以按照目录时间，大小排序
void printDir(treenode *root, int type = 0, string dir = "")
{
    vector<psll> temp;
    cout<<"2"<<endl;
    cout<<dir<<endl;
    cout<<dir==""<<endl;
    if(dir != ""){
        cout<<"3";
        for (auto [x, y] : mpDir)
        {
            cout<<"4";
            cout<<x<<y<<endl;
            temp.emplace_back(y->name, type == 0 ? y->size : y->time);
        }
    }
    
    sortusemerge(temp);
    for (auto [x, y] : temp)
    {
        if (type == 1)
        {
            cout << x << " " << time2str(y) << endl;
        }
        else
        {
            cout << x << " " << better(y) << endl;
        }
    }
}
//打印文件，可以按照文件时间大小排序
void printFile(treenode *root, int type = 0, string dir = "")
{
    vector<psll> temp;
    for (auto [x, y] : mpFile)
    {
        temp.emplace_back(y->name, type == 0 ? y->size : y->time);
    }
    sortusemerge(temp);
    for (auto [x, y] : temp)
    {
        if (type == 1)
        {
            cout << x << " " << time2str(y) << endl;
        }
        else
        {
            cout << x << " " << better(y) << endl;
        }
    }
}
void getDirandFile(string dname, string &dir, string &file)
{
    if (dname.back() == '/')
    {
        dname.pop_back();
    }
    file = dname.substr(dname.rfind('/') + 1);
    dir = dname.substr(0, dname.rfind('/') + 1);
}
int findstr(string haystack, string needle)
{
    int m = needle.size(), n = haystack.size(), j = 0, i = 1;
    vector<int> next(m, 0);
    //填入next数组
    for (; i < m; i++)
    {
        while (needle[i] != needle[j])
        {
            if (j == 0)
            {
                next[i] = 0;
                break;
            }
            else
            {
                j = next[j - 1];
            }
        }
        if (needle[i] == needle[j])
        {
            next[i] = ++j;
        }
    }
    //利用next数组比较
    i = 0, j = 0;
    while (i < n && j < m)
    {
        if (needle[j] == haystack[i])
        {
            i++;
            j++;
        }
        else if (j == 0)
        {
            i++;
        }
        else
        {
            j = next[j - 1];
        }
    }
    return j != m ? -1 : i - m;
}
int help(string dest, string filename)
{
    std::ifstream fp(filename.c_str());
    char buf[1024];
    int line = 1;
    while (fp.getline(buf, 1024, '\n'))
    {
        string src = buf;
        // if (src.find(dest) != string::npos)
        if (findstr(src, dest) != -1)
        {
            cout << filename << "(" << line << "):" << src << endl;
        }
        line++;
    }
    fp.close();
    return 0;
}
int grep(string dest, string filename,int type = 0)
{
    queue<treenode *> mq;
    if (!mpTreenode.count(filename))
    {
        return -1;
    }
    mq.emplace(mpTreenode[filename]);
    while (!mq.empty())
    {
        int len = mq.size();
        for(int i=0;i<len;i++){
            auto tn = mq.front();
            mq.pop();
            string fname = tn->name;
            if (mpFile.count(fname))
            {
                help(dest, fname);
            }
            for (auto chn : tn->child)
            {
                mq.emplace(chn);
            }
        }
        if(type==0){
            break;
        }
    }
    return 0;
}

int main()
{
    while (1)
    {
        char buf[1024];
        printf("input dir:\n");
        cin >> buf;
        if (!strncmp(buf, "quit", strlen(buf)))
        {
            break;
        }
        string Dname = buf;
        string dir, file;
        getDirandFile(Dname, dir, file);
        treenode *root = new treenode(Dname);
        ll size;
        time_t time = 0;
        getFileSizeAndTime(Dname, size, time);
        if ((size = dfs_lsit(root, Dname)) == -1){
            cout<<"open dir fail:"<<Dname<<endl;
            continue;
        }
        mpDir[Dname] = new dirinfo(file, dir, time, size);
        while (1)
        {
            printf("input command:\n");
            cin.getline(buf,1024,'\n');
            if (0 == strncmp(buf, "clear", 5))
            {
                delete root;
                break;
            }
            else if (0==strncmp(buf, "tree", 4))
            {
                printTree(root);
            }
            else if (0==strncmp(buf, "file", 4))
            {
                char command[1024],type[1024],dir[1024];
                sscanf(buf,"%s %s %s",command,type,dir);
                printFile(root, type[1]=='t'||type[1]=='T',dir);
            }
            else if (0 == strncmp(buf, "dir", 3))
            {
                cout<<"1"<<endl;
                char command[1024],type[1024],dir[1024];
                sscanf(buf,"%s %s %s",command,type,dir);
                printDir(root, type[1]=='t'||type[1]=='T',dir);
            }
            else if (0 == strncmp(buf, "grep", 4))
            {
                char command[1024],type[1024],dest[1024],fname[1024];
                sscanf(buf,"%s %s %s %s",command,type,dest,fname);
                if(fname == ""){
                    grep(dest,Dname,type[1]=='r'||type[1]=='R');
                }else{
                    grep(dest,fname,type[1]=='r'||type[1]=='R');
                }
            }
        }
    }
    return 0;
}
