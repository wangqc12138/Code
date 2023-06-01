#include "head.h"
/* 
给你一个整数数组 nums 和一个整数 k 。你可以将 nums 划分成一个或多个 子序列 ，使 nums 中的每个元素都 恰好 出现在一个子序列中。

在满足每个子序列中最大值和最小值之间的差值最多为 k 的前提下，返回需要划分的 最少 子序列数目。

子序列 本质是一个序列，可以通过删除另一个序列中的某些元素（或者不删除）但不改变剩下元素的顺序得到。
 */
class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        int b=nums[0],res=1;
        for(int i=0;i<nums.size();i++){
            if(nums[i]-b>k){
                b=nums[i];
                res++;
            }
        }
        return res;
    }
};
/* 
给你一个下标从 0 开始的数组 nums ，它包含 n 个 互不相同 的正整数。请你对这个数组执行 m 个操作，在第 i 个操作中，你需要将数字 operations[i][0] 替换成 operations[i][1] 。

题目保证在第 i 个操作中：

    operations[i][0] 在 nums 中存在。
    operations[i][1] 在 nums 中不存在。

请你返回执行完所有操作后的数组。
 */
class Solution {
public:
    vector<int> arrayChange(vector<int>& nums, vector<vector<int>>& operations) {
        int m=operations.size(),n=nums.size();
        unordered_map<int,int> mp;
        for(int i=0;i<n;i++){
            mp[nums[i]]=i;
        }
        for(int i=0;i<m;i++){
            int k=mp[operations[i][0]];
            nums[k]=operations[i][1];
            mp[operations[i][1]]=k;
        }
        return nums;
    }
};
/* 
请你设计一个带光标的文本编辑器，它可以实现以下功能：

    添加：在光标所在处添加文本。
    删除：在光标所在处删除文本（模拟键盘的删除键）。
    移动：将光标往左或者往右移动。

当删除文本时，只有光标左边的字符会被删除。光标会留在文本内，也就是说任意时候 0 <= cursor.position <= currentText.length 都成立。

请你实现 TextEditor 类：

    TextEditor() 用空文本初始化对象。
    void addText(string text) 将 text 添加到光标所在位置。添加完后光标在 text 的右边。
    int deleteText(int k) 删除光标左边 k 个字符。返回实际删除的字符数目。
    string cursorLeft(int k) 将光标向左移动 k 次。返回移动后光标左边 min(10, len) 个字符，其中 len 是光标左边的字符数目。
    string cursorRight(int k) 将光标向右移动 k 次。返回移动后光标左边 min(10, len) 个字符，其中 len 是光标左边的字符数目。
 */
class TextEditor {
public:
    TextEditor() {
        lc.clear();
        lc.emplace_back('|');
        index=lc.begin();
    }
    
    void addText(string text) {
        lc.insert(index,text.begin(),text.end());
    }
    
    int deleteText(int k) {
        int t=k;
        while(t){
            if(index==lc.begin()){
                break;
            }
            t--;
            index--;
            index=lc.erase(index);
        }
        return k-t;
    }
    
    string cursorLeft(int k) {
        string res="";
        auto itr=index;
        for(int i=0;i<k;i++,itr--){
            if(itr==lc.begin()){
                break;
            }
        }
        if(itr!=index){
            index = lc.erase(index);
            itr = lc.insert(itr,'|');
            index=itr;
            itr--;
        }
        if(index==lc.begin()){
            return "";
        }
        for(int i=0;i<10;i++,itr--){
            res+=*itr;
            if(itr==lc.begin()){
                break;
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
    
    string cursorRight(int k) {
        string res="";
        auto itr=index;
        for(int i=0;i<=k;i++,itr++){
            if(itr==lc.end()){
                break;
            }
        }
        if(itr!=index){
            itr = lc.insert(itr,'|');
            index = lc.erase(index);
            index=itr;
            itr--;
        }
        if(index==lc.begin()){
            return "";
        }
        for(int i=0;i<10;i++,itr--){
            res+=*itr;
            if(itr==lc.begin()){
                break;
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
private:
    list<char> lc;
    list<char>::iterator index;
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */