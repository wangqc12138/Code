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
    vector<treenode *> child;
};
//递归
ll dfs_lsit(treenode *root, string dir);
void printTree(treenode *root, int len = 1);
//递归排序
void sortusemerge(vector<psll> &nums);
void mergesort(vector<psll> &nums, int left, int right);
void merge(vector<psll> &nums, int left, int right);
//哈希
unordered_map<string, fileinfo *> mpFile;
unordered_map<string, dirinfo *> mpDir;
string time2str(time_t time)
{
    char res[1024];
    struct tm *p;
    p = localtime(&time);
    sprintf(res, "%04d-%02d-%02d %02d:%02d:%02d\n", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    return res;
}
string better(int size)
{
    vector<string> vec = {"B", "b", "kb", "mb", "gb", "tb"};
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
            root->child.emplace_back(chnode);
            mpFile[temp] = new fileinfo(dp->d_name, dir, time, size);
            sumSize += size;
        }
        if (dp->d_type == 4)
        {
            treenode *chnode = new treenode(temp);
            root->child.emplace_back(chnode);
            size = dfs_lsit(chnode, temp);
            mpDir[temp] = new dirinfo(dp->d_name, dir, time, size);
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
        cout << "--";
    }
    if (mpFile.count(root->name))
    {
        auto ff = mpFile[root->name];
        cout << ff->name << " " << better(ff->size) << " " << time2str(ff->time) << endl;
        return;
    }
    auto df = mpDir[root->name];
    cout << df->name << " " << better(df->size) << " " << time2str(df->time) << endl;
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
void printDir(treenode *root, int type = 0)
{
    vector<psll> temp;
    for (auto [x, y] : mpDir)
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
//打印文件，可以按照文件时间大小排序
void printFile(treenode *root, int type = 0)
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

int main()
{
    string Dname = "/home/wangqc/CppPracticeCode/test";
    string dir, file;
    getDirandFile(Dname, dir, file);
    treenode *root = new treenode(Dname);
    ll size;
    time_t time = 0;
    getFileSizeAndTime(Dname, size, time);
    size = dfs_lsit(root, Dname);
    mpDir[Dname] = new dirinfo(file, dir, time, size);
    printTree(root);
    printFile(root, 1);
    return 0;
}
