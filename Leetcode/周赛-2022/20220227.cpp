#include "head.h"
class Solution {
public:
    long long minimumTime(vector<int>& time, int totalTrips) {
        int minn=*min_element(time.begin(),time.end());
        long long left=1;
        long long right=totalTrips*minn;
        while(left<right){
            long long mid=left+(right-left)/2;
            int k=0;
            for(int i:time){
                k+=mid/i;
                if(k>totalTrips){
                    break;
                }
            }
            if(k>totalTrips){
                left=mid+1;
            }else{
                right=mid;
            }
        }
        return left;
    }
};
class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        for(auto t: tires){
            int temp=0;
            while()
        }       
    }
};