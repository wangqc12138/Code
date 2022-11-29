#include "head.h"
/*
剑指 Offer II 060. 出现频率最高的 k 个数字
给定一个整数数组 nums 和一个整数 k ，请返回其中出现频率前 k 高的元素。可以按 任意顺序 返回答案。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]

提示：

    1 <= nums.length <= 105
    k 的取值范围是 [1, 数组中不相同的元素的个数]
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
 */
// 此题还有快排的方法在快排分类中记录
using pii = pair<int, int>;
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        auto cmp = [](pii a, pii b)
        {
            return a.second > b.second;
        };
        priority_queue<pii, vector<pii>, decltype(cmp)> mpq(cmp);
        map<int, int> mp;
        for (int i : nums)
        {
            mp[i]++;
        }
        for (auto itr : mp)
        {
            mpq.emplace(itr);
            if (mpq.size() > k)
            {
                mpq.pop();
            }
        }
        vector<int> res;
        while (!mpq.empty())
        {
            res.emplace_back(mpq.top().first);
            mpq.pop();
        }
        return res;
    }
};
/*
剑指 Offer II 059. 数据流的第 K 大数值

设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。

请实现 KthLargest 类：

    KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
    int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。
 */
class KthLargest
{
public:
    KthLargest(int k, vector<int> &nums)
    {
        this->k = k;
        for (int i : nums)
        {
            mpq.emplace(i);
            if (mpq.size() > k)
            {
                mpq.pop();
            }
        }
    }

    int add(int val)
    {
        mpq.emplace(val);
        if (mpq.size() > k)
        {
            mpq.pop();
        }
        return mpq.top();
    }

private:
    priority_queue<int, vector<int>, greater<int>> mpq;
    int k;
};
/*
剑指 Offer 49. 丑数

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。
 */
class Solution
{
public:
    int nthUglyNumber(int n)
    {
        priority_queue<long long, vector<long long>, greater<long long>> mpq;
        int temp[3] = {2, 3, 5};
        set<long long> visit;
        mpq.emplace(1);
        visit.emplace(1);
        int index = 0;
        while (!mpq.empty())
        {
            if (++index == n)
            {
                return mpq.top();
            }
            int k = mpq.top();
            mpq.pop();
            for (auto i : temp)
            {
                long long L = (long long)i * k;
                if (!visit.count(L))
                {
                    mpq.emplace(L);
                    visit.emplace(L);
                }
            }
        }
        return -1;
    }
};
class Solution
{
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        int heapSize = nums.size();
        heapInsert(nums, heapSize);
        for (int i = 1; i < k; i++)
        {
            swap(nums, 0, --heapSize);
            heapify(nums, 0, heapSize);
        }
        return nums[0];
    }
    void heapInsert(vector<int> &nums, int heapSize)
    {
        for (int i = 0; i < heapSize; i++)
        {
            while (nums[i] > nums[(i - 1) / 2])
            {
                int index = i;
                while (nums[index] > nums[(index - 1) / 2])
                {
                    swap(nums, index, (index - 1) / 2);
                    index = (index - 1) / 2;
                }
            }
        }
    }
    void heapify(vector<int> &nums, int index, int heapSize)
    {
        int left = 2 * index + 1;
        while (left < heapSize)
        {
            int maxIndex = (left + 1 < heapSize) && nums[left + 1] > nums[left] ? left + 1 : left;
            if (nums[maxIndex] <= nums[index])
            {
                break;
            }
            swap(nums, maxIndex, index);
            index = maxIndex;
            left = 2 * index + 1;
        }
    }
    void swap(vector<int> &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
    /*    vector<int> v(2,-1);
        int L=0,R=nums.size()-1;
        int rn;
        while(k > (nums.size() - v[0])||k < (nums.size() - v[1])){
            rn=rand()%(R-L+1)+ L;
            swap(nums, rn, R);
            partition(nums, L, R, v);
            if(k > (nums.size() - v[0])){
                R=v[0]-1;
            }
            if(k < (nums.size() - v[1])){
                L=v[1]+1;
            }
        }
        return nums[v[1]];
    }
    void partition(vector<int> &nums, int L, int R, vector<int> &v){
        int less=L-1;
        int more=R+1;
        int index=L;
        int n = nums[R];
        while(index<more){
            if(nums[index]==n) {
                index++;
            }
            else if(nums[index]<n) {
                swap(nums, ++less, index++);
            }
            else if(nums[index]>n) {
                swap(nums, --more, index);
            }
        }
        v[0]=less+1;
        v[1]=more-1;
    */

    void swap(vector<int> &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
};
class MedianFinder
{
    vector<int> maxHeap;
    vector<int> minHeap;

public:
    /** initialize your data structure here. */
    void swap(vector<int> &nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void heapInsert(vector<int> &nums, int index)
    {
        while (nums[index] > nums[(index - 1) / 2])
        {
            swap(nums, index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void heapify(vector<int> &nums, int index, int heapSize)
    {
        int left = index * 2 + 1;
        while (left < heapSize)
        {
            int maxIndex = (left + 1 < heapSize) && (nums[left] < nums[left + 1]) ? left + 1 : left;
            if (nums[maxIndex] < nums[index])
                break;
            swap(nums, index, maxIndex);
            index = maxIndex;
            left = index * 2 + 1;
        }
    }

    void minheapInsert(vector<int> &nums, int index)
    {
        while (nums[index] < nums[(index - 1) / 2])
        {
            swap(nums, index, (index - 1) / 2);
            index = (index - 1) / 2;
        }
    }

    void minheapify(vector<int> &nums, int index, int heapSize)
    {
        int left = index * 2 + 1;
        while (left < heapSize)
        {
            int minIndex = (left + 1 < heapSize) && (nums[left] > nums[left + 1]) ? left + 1 : left;
            if (nums[minIndex] > nums[index])
                break;
            swap(nums, index, minIndex);
            index = minIndex;
            left = index * 2 + 1;
        }
    }
    void addNum(int num)
    {
        if (maxHeap.size() != 0)
        {
            if (num > maxHeap[0])
            {
                minHeap.push_back(num);
                minheapInsert(minHeap, minHeap.size() - 1);
            }
            else
            {
                maxHeap.push_back(num);
                heapInsert(maxHeap, maxHeap.size() - 1);
            }
            if (maxHeap.size() > minHeap.size() + 1)
            {
                minHeap.push_back(maxHeap[0]);
                swap(maxHeap, 0, maxHeap.size() - 1);
                maxHeap.pop_back();
                heapify(maxHeap, 0, maxHeap.size());
                minheapInsert(minHeap, minHeap.size() - 1);
            }
            if (minHeap.size() > maxHeap.size() + 1)
            {
                maxHeap.push_back(minHeap[0]);
                swap(minHeap, 0, minHeap.size() - 1);
                minHeap.pop_back();
                minheapify(minHeap, 0, minHeap.size());
                heapInsert(maxHeap, maxHeap.size() - 1);
            }
        }
        else
        {
            maxHeap.push_back(num);
        }
    }
    double findMedian()
    {
        if (maxHeap.size() == minHeap.size())
            return (maxHeap[0] + minHeap[0]) / 2.0;
        else
        {
            return maxHeap.size() > minHeap.size() ? maxHeap[0] : minHeap[0];
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */