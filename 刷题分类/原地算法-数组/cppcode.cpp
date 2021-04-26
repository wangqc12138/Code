/*
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
27
*/
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
    	//双指针
    	int j=0;
    	for(int i=0;i<nums.size();i++){
    		if(nums[i]!=val){
    			nums[j++]=nums[i];
    		}
    	}
    	return j;

    }
};
/*
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 只出现一次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
26
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        //如果这个数和前一个数相同，则跳过
        int j=1;
        for(int i=1;i<nums.size();i++){
            if(nums[i]!=nums[j-1]){
                nums[j++]=nums[i];
            }
        }
        return j;
    }
};
/*
给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 最多出现两次 ，返回删除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
80
*/
//解此类题，视为双指针，快指针遍历数组，慢指针指向修改的数组。
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n=nums.size();
        if(n<=2){
            return n;
        }
        int j=2;
        for(int i=2;i<n;i++){
            if(nums[i]!=nums[j-2]){
                nums[j++]=nums[i];
            }
        }
        return j;

    }
};
/*
给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
在 S 上反复执行重复项删除操作，直到无法继续删除。
在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
1047
*/
/*
给定一组字符，使用原地算法将其压缩。

压缩后的长度必须始终小于或等于原数组长度。

数组的每个元素应该是长度为1 的字符（不是 int 整数类型）。

在完成原地修改输入数组后，返回数组的新长度。

 

进阶：
你能否仅使用O(1) 空间解决问题？
443
*/
class Solution {
public:
    int compress(vector<char>& chars) {
        int n=chars.size(),begin=0,w=0;
        for(int i=0;i<n;i++){
            if(i==n-1||chars[i]!=chars[i+1]){
                char b=chars[begin];
                if(i>begin){
                    int len=i-begin+1;
                    string lenstr=to_string(len);
                    for(auto c:lenstr){
                        chars[w++]=c;
                    }
                }
                chars[w++]=b;
                begin=i+1;
            }
        }
        chars.resize(w);
        return w;
    }
};