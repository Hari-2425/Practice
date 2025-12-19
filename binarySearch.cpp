#include <bits/stdc++.h>
using namespace std;

// You are given an integer array piles where piles[i] is the number of bananas in the ith pile. You are also given an integer h, which represents the number of hours you have to eat all the bananas.

// You may decide your bananas-per-hour eating rate of k. Each hour, you may choose a pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, you may finish eating the pile but you can not eat from another pile in the same hour.

// Return the minimum integer k such that you can eat all the bananas within h hours.

// Example 1:

// Input: piles = [1,4,3,2], h = 9

// Output: 2
// Explanation: With an eating rate of 2, you can eat the bananas in 6 hours. With an eating rate of 1, you would need 10 hours to eat all the bananas (which exceeds h=9), thus the minimum eating rate is 2.

// Example 2:

// Input: piles = [25,10,23,4], h = 4

// Output: 25
// Constraints:

// 1 <= piles.length <= 1,000
// piles.length <= h <= 1,000,000
// 1 <= piles[i] <= 1,000,000,000
bool IsValid(vector<int>& piles, int k, int h){
    int calc_h = 0;
    for(int i=0;i<piles.size();i++){
        int ceil_value = (piles[i]%k != 0) ? 1+(piles[i]/k) : (piles[i]/k);
        calc_h += ceil_value;
    }
    return calc_h <= h;
}

int minEatingSpeed(vector<int>& piles, int h) {
    int n = piles.size();
    int low=1, high=1e9, ans = INT_MAX;
    while(low<=high){
        int k = low + (high-low)/2;
        if(IsValid(piles, k, h)){
            high = k-1;
            ans = min(ans, k);
        }
        else{
            low = k + 1;
        }
    }
    return ans;
}

// You are given an array of length n which was originally sorted in ascending order. It has now been rotated between 1 and n times. For example, the array nums = [1,2,3,4,5,6] might become:
// [3,4,5,6,1,2] if it was rotated 4 times.
// [1,2,3,4,5,6] if it was rotated 6 times.
// Notice that rotating the array 4 times moves the last four elements of the array to the beginning. Rotating the array 6 times produces the original array.
// Assuming all elements in the rotated sorted array nums are unique, return the minimum element of this array.
// A solution that runs in O(n) time is trivial, can you write an algorithm that runs in O(log n) time?

int findMin(vector<int> &nums) {
    int n = nums.size();
    if(n == 1){
        return nums[0];
    }
    int low=0, high=n-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(nums[low] < nums[high]){
            return nums[low];
        }
        else{
            if(nums[mid] < nums[mid-1]){
                return nums[mid];
            }
            if(nums[mid] >= nums[low]){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
    }
    return nums[low];
}

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int low=0, high=m-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(target > matrix[mid][n-1]){
            low = mid+1;
        }
        else if(target < matrix[mid][0]){
            high = mid-1;
        }
        else{
            int indx = lower_bound(matrix[mid].begin(), matrix[mid].end(), target) - matrix[mid].begin();
            return matrix[mid][indx] == target;
        }
    }
    return false;
}

int main(){

    return 0;
}