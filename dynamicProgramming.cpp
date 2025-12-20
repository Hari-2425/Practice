#include <bits/stdc++.h>
using namespace std;

// ===== 0/1 KNAPSACK PATTERN =====
// State: (idx, W) represents max value using items from index idx onwards with capacity W
// Choice: for each item, decide to include it or exclude it
// Constraint: each item can be used at most once; total weight cannot exceed W
// Transition: max(exclude_item, include_item)
// Base case: no items left (idx >= n) or no capacity left (W <= 0) returns 0

int recursive_func(int idx, vector<int> &weights, vector<int> &val, int W, unordered_map<string, int> &store){
    // BASE CASE: knapsack pattern base condition
    if(idx>=weights.size() || W<=0)
        return 0;
    
    // MEMOIZATION KEY: encodes state (idx, W)
    // idx = current item index, W = remaining capacity
    string key = to_string(idx) + ", " + to_string(W);
    if(store.count(key)){
        return store[key];
    }
    
    // KNAPSACK CHOICE & TRANSITION:
    if(weights[idx] <= W){
        // Choice 1: exclude current item, move to next
        int ans1 = recursive_func(idx+1, weights, val, W, store); //not selected
        // Choice 2: include current item, reduce capacity, add its value
        int ans2 = recursive_func(idx+1, weights, val, W-weights[idx], store) + val[idx]; //Selected
         
        return store[key] = max(ans1, ans2);
    }
    
    // Current item too heavy: must exclude it
    return store[key] = recursive_func(idx+1, weights, val, W, store);
}

int knapSack(vector<int> weights, vector<int> val, int W){
    int n = weights.size();
    
    unordered_map<string, int> store;
    return recursive_func(0, weights, val, W, store);
}

int knapSack_iterative(vector<int> &weights, vector<int> &val, int W){
    int n = weights.size();
    // DP TABLE DEFINITION:
    // dp[i][j] = max value achievable using first i items with capacity j
    // i ranges [0..n] (number of items considered)
    // j ranges [0..W] (current capacity)
    vector<vector<int>> dp(n+1, vector<int>(W+1));

    // BASE CASE: 0 items or 0 capacity = 0 value
    for(int i=0;i<=n;i++){
        dp[i][0] = 0;
    }
    for(int i=1;i<=W;i++){
        dp[0][i] = 0;
    }

    // KNAPSACK TRANSITION: fill DP table
    // For each item i and capacity j, compute the maximum value
    for(int i=1;i<=n;i++){
        for(int j=1;j<=W;j++){
            int wt = weights[i-1];
            int value = val[i-1];
            // Choice 1: exclude item i-1
            int notPick = dp[i-1][j];
            // Choice 2: include item i-1 (if weight permits)
            int pick = 0;
            if(wt <= j){
                pick = value + dp[i-1][j-wt];
            }
            dp[i][j] = max(pick, notPick);
        }
    }
    return dp[n][W];
}

// ===== SUBSET SUM PATTERN (Knapsack Variant) =====
// State: (i, j) = can we achieve target sum j using first i elements?
// Choice: include element i-1 or exclude it
// Constraint: each element used at most once
// Transition: dp[i][j] = dp[i-1][j] OR dp[i-1][j-nums[i-1]]
// Base case: sum=0 is always achievable (empty subset), sum>0 with 0 items is impossible
bool subset_sum(vector<int> &nums, int trg){
    int n = nums.size();
    vector<vector<bool>> dp(n+1, vector<bool>(trg+1));

    // BASE CASE: target sum 0 is always achievable
    for(int i=0;i<=n;i++){
        dp[i][0] = 1;
    }
    // All other base cases default to false (already initialized)

    // SUBSET SUM TRANSITION: fill DP table
    for(int i=1;i<=n;i++){
        for(int j=1;j<=trg;j++){
            // Choice 1: exclude nums[i-1]
            bool notPick = dp[i-1][j];
            // Choice 2: include nums[i-1] (if it doesn't exceed target)
            bool pick = 0;
            if(nums[i-1] <= j){
                pick = dp[i-1][j-nums[i-1]];
            }
            dp[i][j] = pick || notPick;
        }
    }
    return dp[n][trg];
}

// ===== SUBSET SUM COUNT PATTERN (Knapsack Variant) =====
// State: (i, j) = count of subsets using first i elements that sum to j
// Choice: include element i-1 or exclude it
// Constraint: each element used at most once
// Transition: dp[i][j] = (subsets excluding i-1) + (subsets including i-1)
// Base case: sum=0 has exactly 1 way (empty subset)
int subsetSum_count(vector<int> &nums, int target){
    int n = nums.size();
    vector<vector<int>> dp(n+1, vector<int>(target+1, 0));

    // BASE CASE: target sum 0 is achievable in exactly 1 way (empty subset)
    for(int i=0;i<=n;i++){
        dp[i][0] = 1;
    }

    // SUBSET SUM COUNT TRANSITION: fill DP table
    for(int i=1;i<=n;i++){
        for(int j=1;j<=target;j++){
            // Count subsets excluding nums[i-1]
            int notPick = dp[i-1][j];
            // Count subsets including nums[i-1]
            int pick = 0;
            if(nums[i-1]<=j){
                pick = dp[i-1][j-nums[i-1]];
            }
            dp[i][j] = pick + notPick;
        }
    }
    return dp[n][target];
}

int subSet_min_diff(vector<int> &nums){
    int totalSum = 0;
    int n = nums.size();

    for(auto it: nums){
        totalSum += it;
    }
    int s = (totalSum+1)/2;
    vector<vector<bool>> dp(n+1, vector<bool>(s+1, 0));

    for(int i=0;i<=n;i++){
        dp[i][0] = 1;
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=s;j++){
            bool not_pick = dp[i-1][j];
            bool pick = 0;
            if(nums[i-1]<=j){
                pick = dp[i-1][j-nums[i-1]];
            }
            dp[i][j] = pick || not_pick;
        }
    }
    
    //Will traverse the last row of dp becoz it contains all
    // the valid subset sum to the half of total sum.
    int ans = INT_MAX;
    for(int i=0;i<=s;i++){
        if(dp[n][i] == 1){
            ans = min(ans,abs( totalSum - 2*i));
        }
    }
    return ans;
}

int main(){
    
    vector<int> nums = {1, 2, 7};
    cout<<"ANS: "<<subSet_min_diff(nums);

    return 0;
}