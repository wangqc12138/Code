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