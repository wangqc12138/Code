/*
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
704
*/
/*
实现 int sqrt(int x) 函数。
计算并返回 x 的平方根，其中 x 是非负整数。
由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
69
*/
/*
猜数字游戏的规则如下：
    每轮游戏，我都会从 1 到 n 随机选择一个数字。 请你猜选出的是哪个数字。
    如果你猜错了，我会告诉你，你猜测的数字比我选出的数字是大了还是小了。
你可以通过调用一个预先定义好的接口 int guess(int num) 来获取猜测结果，返回值一共有 3 种可能的情况（-1，1 或 0）：
    -1：我选出的数字比你猜的数字小 pick < num
    1：我选出的数字比你猜的数字大 pick > num
    0：我选出的数字和你猜的数字一样。恭喜！你猜对了！pick == num
返回我选出的数字。
374
*/
/*
整数数组nums按升序排列，数组中的值互不相同。
在传递给函数之前，nums在预先未知的某个下标k（0<=k<nums.length）上进行了旋转，使数组变为[nums[k],nums[k+1],...,nums[n-1],nums[0],nums[1],...,nums[k-1]]（下标从0开始计数）。
例如，[0,1,2,4,5,6,7]在下标3处经旋转后可能变为[4,5,6,7,0,1,2]。
给你旋转后的数组nums和一个整数target，如果nums中存在这个目标值target，则返回它的索引，否则返回-1。
33
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1,mid;
        while(left<=right){
            mid=(right-left)/2+left;
            if(nums[mid]==target){
                return mid;
            }
            if(nums[mid]>=nums[left]){//左边有序
                if(nums[mid]>target&&nums[left]<=target){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }else{//右边有序
                if(nums[mid]<target&&nums[right]>=target){
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }
        }
        return -1;
    }
};
/*
已知存在一个按非降序排列的整数数组nums，数组中的值不必互不相同。
在传递给函数之前，nums在预先未知的某个下标k（0<=k<nums.length）上进行了旋转，使数组变为[nums[k],nums[k+1],...,nums[n-1],nums[0],nums[1],...,nums[k-1]]（下标从0开始计数）。
例如，[0,1,2,4,4,4,5,6,6,7]在下标5处经旋转后可能变为[4,5,6,6,7,0,1,2,4,4]。
给你旋转后的数组nums和一个整数target，请你编写一个函数来判断给定的目标值是否存在于数组中。如果nums中存在这个目标值target，则返回true，否则返回false。
81
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1,mid;
        while(left<=right){
            while(left<right&&nums[left]==nums[left+1]){
                left++;
            }
            while(left<right&&nums[right]==nums[right-1]){
                right--;
            }
            mid=(right-left)/2+left;
            if(nums[mid]==target){
                return true;
            }
            if(nums[mid]>=nums[left]){//左边有序
                if(nums[mid]>target&&nums[left]<=target){
                    right=mid-1;
                }else{
                    left=mid+1;
                }
            }else{//右边有序
                if(nums[mid]<target&&nums[right]>=target){
                    left=mid+1;
                }else{
                    right=mid-1;
                }
            }
        }
        return false;
    }
};
/*
你是产品经理，目前正在带领一个团队开发新的产品。不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。
假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
278
*/
/*
峰值元素是指其值大于左右相邻值的元素。
给你一个输入数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
你可以假设 nums[-1] = nums[n] = -∞ 。
162
*/
/*
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
    若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
    若旋转 4 次，则可以得到 [0,1,2,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
假设按照升序排序的数组在预先未知的某个点上进行了旋转。例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] 。
请找出其中最小的元素。
153
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size(),mid;
        while(left<right){
            mid=left+(right-left)/2;
            if(nums[mid]>nums[right]){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return nums[left];
    }
};
/*
给定一个排序好的数组 arr ，两个整数 k 和 x ，从数组中找到最靠近 x（两数之差最小）的 k 个数。返回的结果必须要是按升序排好的。
整数 a 比整数 b 更接近 x 需要满足：
    |a - x| < |b - x| 或者
    |a - x| == |b - x| 且 a < b
658
*/
//其他二分是查找一个数，这个可以看作查找一段数
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left=0,right=arr.size()-1-k,mid;
        while(left<=right){//找出左边界
            mid=left+(right-left)/2;
            if(x-arr[mid]>arr[mid+k]-x){//如果mid距离x比mid+k距离x更远，则左边界还在右侧
                left=mid+1;
            }else{
                right=mid-1;
            }
        }
        return vector<int>(arr.begin()+left,arr.begin()+left+k);
    }
};
/*
给定一个升序整数数组，写一个函数搜索 nums 中数字 target。如果 target 存在，返回它的下标，否则返回 -1。注意，这个数组的大小是未知的。
你只可以通过 ArrayReader 接口访问这个数组，ArrayReader.get(k) 返回数组中第 k 个元素（下标从 0 开始）。
你可以认为数组中所有的整数都小于 10000。如果你访问数组越界，ArrayReader.get 会返回 2147483647。
702
*/
/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

class Solution {
public:
    int search(const ArrayReader& reader, int target) {
        int left=0,right=MAX_INT,mid;
        while(left<=right){
            mid=left+(right-left)/2;
            if(reader.get(mid)==target){
                return mid;
            }else if(reader.get(mid)>9999||reader.get(mid)>target){
                right=mid-1;
            }else{
                left=mid+1;
            }
        }
        return -1;
    }
};
/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。
34
*/
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left=0,right=nums.size()-1,mid;
        vector<int> res;
        //找第一次出现的位置
        while(left<right){
            mid=left+(right-left)/2;
            if(nums[mid]<target){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        res.push_back(left);
        left=0;right=nums.size()-1;
        //找最后一次出现的位置
        while(left<right){
            mid=left+(right-left+1)/2;//注意向上取整
            if(nums[mid]>target){
                right=mid-1;
            }else{
                left=mid;
            }
        }
        res.push_back(left);
        return res;
    }
};
/*
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。
*/
class Solution {
public:
    double myPow(double x, int n) {
        
    }
};
/*
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,4,4,5,6,7] 在变化后可能得到：
    若旋转 4 次，则可以得到 [4,5,6,7,0,1,4]
    若旋转 7 次，则可以得到 [0,1,4,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
给你一个可能存在 重复 元素值的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。
154
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left=0,right=nums.size()-1,mid;
        while(left<right){
            while(left<right&&nums[left]==nums[left+1]){
                left++;
            }
            while(left<right&&nums[right]==nums[right-1]){
                right--;
            }
            mid=left+(right-left)/2;
            
            if(nums[mid]>nums[right]){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return nums[left];
    }
};

/*
给定一个 正整数 num ，编写一个函数，如果 num 是一个完全平方数，则返回 true ，否则返回 false 。
进阶：不要 使用任何内置的库函数，如  sqrt 。
367
*/
class Solution {
public:
    bool isPerfectSquare(int num) {
        long left=0,right=num,mid,t;
        while(left<right){
            mid=left+(right-left)/2;
            t=mid*mid;
            if(t==num){
                return true;
            }
            if(t<num){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left*left==num;
    }
};
/*
给你一个排序后的字符列表 letters ，列表中只包含小写英文字母。另给出一个目标字母 target，请你寻找在这一有序列表里比目标字母大的最小字母。
在比较时，字母是依序循环出现的。举个例子：
    如果目标字母 target = 'z' 并且字符列表为 letters = ['a', 'b']，则答案返回 'a'
744
*/
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left=0,right=letters.size()-1,mid;
        target=target>=letters[right]?'a':target+1;
        while(left<right){
            mid=left+(right-left)/2;
            if(letters[mid]<target){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return letters[left];
    }
};
/*
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。
287
*/
//此方法可以用快慢指针的方法
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        /*int slow=0,quick=0,n=nums.size();
        do{
            slow=nums[slow];
            quick=nums[nums[quick]];
        }while(slow!=quick);
        slow=0;
        while(slow!=quick){
            slow=nums[slow];
            quick=nums[quick];
        }
        return slow;*/
        int left=1,right=nums.size()-1,mid,cnt;
        while(left<mid){
            mid=left+(right-mid)/2;
            cnt=0;
            for(int i:nums){
                if(i<=mid){//计算小于mid的数
                    cnt++;
                }
            }
            if(mid<cnt){
                right=mid
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};
/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
4
*/
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len=nums1.size()+nums2.size();
        int index1=0,index2=0;
        while(len){
            len/=2;

        }
    }
    int process(vector<int>& nums1, vector<int>& nums2, int index) {
        int i1=0;i2=0;
        while(index){
            i1=min(index/2,nums1.size()-1);
            i2=min(index/2,nums2.size()-1);
            if(nums1[i1]>=nums2[i2]){

            }
        }
    }
};