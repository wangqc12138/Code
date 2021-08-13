#include "head.h"
/*
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
704
*/
//当判断条件为left<right时，如果需要查找是否有此值，则还需判断left的值！
//当判断条件为left<=right，已经判断过了，直接返回-1即可！
//私以为需要找到是否有目标值则用<=比较好，而找出范围什么的就用<比较好，另外right的初值也可以用size来设置
//当要排除右半部分时---righ=mid-1，left=mid；mid最好向上取整，才不会死循环
class Solution {
public:
    int search(vector<int>& nums, int target) {
		int left=0,right=nums.size();
		while(left<right){
			int mid=left+(right-left)/2;
			if(nums[mid]==target){
				return mid;
			}else if(nums[mid]<target){
				left=mid+1;
			}else{
				right=mid-1;
			}
		}
		return nums[left]==target?left:-1;
    }
};
class Solution {
public:
    int search(vector<int>& nums, int target) {
		int left=0,right=nums.size()-1;
		while(left<=right){
			int mid=left+(right-left)/2;
			if(nums[mid]==target){
				return mid;
			}else if(nums[mid]<target){
				left=mid+1;
			}else{
				right=mid-1;
			}
		}
		return -1;
    }
};
/*
实现 int sqrt(int x) 函数。
计算并返回 x 的平方根，其中 x 是非负整数。
由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。
69
*/
class Solution {
public:
    int mySqrt(int x) {
		long left=0,right=x;
		while(left<right){
			long mid=left+(right-left+1)/2;//向上取整
			if(mid>x/mid){
				right=mid-1;
			}else{
				left=mid;
			}
		}
		return left;
    }
};
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
不重复！
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
    int search(/* const  */ArrayReader& reader, int target) {
        int left=0,right=INT_MAX,mid;
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
                right=mid;
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
        int i1=0,i2=0;
        while(index){
            // i1=min(index/2,nums1.size()-1);
            // i2=min(index/2,nums2.size()-1);
            if(nums1[i1]>=nums2[i2]){

            }
        }
    }
};
/*
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。
传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。
1011
*/
//二分
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n=weights.size();
        int left=*max_element(weights.begin(),weights.end());
        int right=accumulate(weights.begin(),weights.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int temp=0,day=1;
            for(int w:weights){
                temp+=w;
                if(temp>mid){
                    day++;
                    temp=w;
                }
            }
            if(day>D){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/*
珂珂喜欢吃香蕉。这里有 N 堆香蕉，第 i 堆中有 piles[i] 根香蕉。警卫已经离开了，将在 H 小时后回来。
珂珂可以决定她吃香蕉的速度 K （单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 K 根。如果这堆香蕉少于 K 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。  
珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在 H 小时内吃掉所有香蕉的最小速度 K（K 为整数）。
875
*/
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
        int left=1,right=*max_element(piles.begin(),piles.end());
        while(left<right){
            int mid=left+(right-left)/2;
            int h=0;
            for(int p:piles){
                h+=(p-1)/mid+1;
            }
            if(h>H){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/*
你有一大块巧克力，它由一些甜度不完全相同的小块组成。我们用数组 sweetness 来表示每一小块的甜度。
你打算和 K 名朋友一起分享这块巧克力，所以你需要将切割 K 次才能得到 K+1 块，每一块都由一些 连续 的小块组成。
为了表现出你的慷慨，你将会吃掉 总甜度最小 的一块，并将其余几块分给你的朋友们。
请找出一个最佳的切割策略，使得你所分得的巧克力 总甜度最大，并返回这个 最大总甜度。
1231
*/
class Solution {
public:
    int maximizeSweetness(vector<int>& sweetness, int K) {
        int left=*min_element(sweetness.begin(),sweetness.end());
        int right=accumulate(sweetness.begin(),sweetness.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int k=0,temp=0;
            for(auto c:sweetness){
                temp+=c;
                if(temp>mid){
                    //我是最小值，其他可以允许比我大
                    k++;
                    //当分配的大于mid时，这个一小块也分给前个人，而不是可以切割
                    temp=0;
                }
            }
            if(k>K){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
/*
给定一个非负整数数组 nums 和一个整数 m ，你需要将这个数组分成 m 个非空的连续子数组。
设计一个算法使得这 m 个子数组各自和的最大值最小。
410
*/
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int left=*max_element(nums.begin(),nums.end());//注意取值
        int right=accumulate(nums.begin(),nums.end(),0);
        while(left<right){
            int mid=left+(right-left)/2;
            int temp=0,k=1;
            for(auto num:nums){
                temp+=num;
                if(temp>mid){
                    //mid时最大值，其他不允许比mid大，所以num得算到下一个人身上
                    k++;
                    temp=num;
                }
            }
            if(k>m){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};

/* 
给你一个整数数组 bloomDay，以及两个整数 m 和 k 。

现需要制作 m 束花。制作花束时，需要使用花园中 相邻的 k 朵花 。

花园中有 n 朵花，第 i 朵花会在 bloomDay[i] 时盛开，恰好 可以用于 一束 花中。

请你返回从花园中摘 m 束花需要等待的最少的天数。如果不能摘到 m 束花则返回 -1 。
1482
bloomDay.length == n
1 <= n <= 10^5
1 <= bloomDay[i] <= 10^9
1 <= m <= 10^6
1 <= k <= n
 */
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if(m*k>bloomDay.size()){
            return -1;
        }
        int left=1,right=*max_element(bloomDay.begin(),bloomDay.end());
        auto check=[&](int n){
            vector<int> now(bloomDay.size());
            for(int i=0;i<bloomDay.size();++i){
                now[i]=bloomDay[i]<=n?1:0;
            }
            int l=0,ans=0;
            for(int i:now){
                if(i==1){
                    l++;
                }else{
                    l=0;
                }
                if(l==k){
                    ans++;
                    l=0;
                }
            }
            //当可以拿到的花大于m也行
            return ans>=m;
        };
        while(left<right){
            int mid=left+(right-left)/2;
            if(check(mid)){
                right=mid;
            }else{
                left=mid+1;
            }
        }
        return left;
    }
};