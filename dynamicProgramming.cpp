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

/* PATTERN: Partition DP (Subset Sum)

Idea:
- Compute total sum of array
- Try to find a subset whose sum is as close as possible
  to totalSum / 2
- Answer = min |totalSum - 2 * subsetSum|

DP Definition:
dp[i][j] = true if we can form sum j using first i elements */
int subSet_min_diff(vector<int> &nums) {
    int totalSum = 0;
    int n = nums.size();

    // Step 1: Calculate total sum
    for (int x : nums) {
        totalSum += x;
    }

    // We only need to check till half of total sum
    int target = (totalSum + 1) / 2;

    // Step 2: DP table
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

    // Step 3: Base Case
    // Sum = 0 is always possible (empty subset)
    for (int i = 0; i <= n; i++) {
        dp[i][0] = true;
    }

    // Step 4: Fill DP table (0/1 Knapsack style)
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {

            // Option 1: Do not pick current element
            bool not_pick = dp[i - 1][j];

            // Option 2: Pick current element (if possible)
            bool pick = false;
            if (nums[i - 1] <= j) {
                pick = dp[i - 1][j - nums[i - 1]];
            }

            dp[i][j] = pick || not_pick;
        }
    }

    // Step 5: Find minimum difference
    int ans = INT_MAX;

    // Only need last row since it contains all valid subset sums
    for (int s1 = 0; s1 <= target; s1++) {
        if (dp[n][s1]) {
            int diff = abs(totalSum - 2 * s1);
            ans = min(ans, diff);
        }
    }

    return ans;
}

// s1 - s2 = diff
// total is the sum of all nums elements
// s1 - total + s1 = diff
// 2*s1 - total = diff
// 2*s1 = total + diff
// s1 = (total + diff)/2
int subSet_diff_count(vector<int> &nums, int diff){
    int n = nums.size();
    int total = 0;
    for(auto it: nums){
        total += it;
    }
    // Invalid cases
    if (diff > total || (diff + total) % 2 != 0)
        return 0;
    
    int s = (diff + total) / 2;

    vector<vector<int>> dp(n + 1, vector<int>(s + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= s; j++) {
            dp[i][j] = dp[i - 1][j];
            if (nums[i - 1] <= j) {
                dp[i][j] += dp[i - 1][j - nums[i - 1]];
            }
        }
    }

    return dp[n][s];
}

void CountPosNegTargetSum_hlpr(int indx, vector<int> &nums, int trg,
    unordered_map<vector<int>, int> &memo){

}

// ================== UNBOUNDED KNAPSACK PATTERN ==================
// Problem Type:
// - Coin Change (Minimum number of coins)
// - Each coin can be used unlimited times
// - Goal: Minimize count to reach exact sum

// DP Meaning:
// dp[i][j] = Minimum number of coins needed to make sum = j
//            using first i coins

// Choice Diagram (for coin i):
// 1) Exclude coin i     → dp[i-1][j]
// 2) Include coin i    → 1 + dp[i][j - coin[i-1]]
//    (stay at same i because coins are unlimited)

// Final Answer:
// dp[n][sum]

int min_coin_change(vector<int> &coins, int sum) {
    int n = coins.size();

    // dp table: (n+1) x (sum+1)
    vector<vector<int>> dp(n+1, vector<int>(sum+1));

    // ---------------- BASE CASES ----------------

    // Case 1: Sum = 0
    // Minimum coins needed to make sum 0 is always 0
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }

    // Case 2: No coins available (i = 0)
    // Impossible to make any positive sum
    for (int j = 1; j <= sum; j++) {
        dp[0][j] = INT_MAX;
    }

    // ---------------- DP TRANSITION ----------------
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {

            // Option 1: Exclude current coin
            dp[i][j] = dp[i-1][j];

            // Option 2: Include current coin (unbounded)
            if (coins[i-1] <= j) {

                // Guard against INT_MAX overflow
                int include = (dp[i][j - coins[i-1]] == INT_MAX)
                                ? INT_MAX
                                : 1 + dp[i][j - coins[i-1]];

                dp[i][j] = min(dp[i][j], include);
            }
        }
    }

    // If dp[n][sum] == INT_MAX → not possible
    return dp[n][sum];
}


int main(){
    
    vector<int> nums = {1, 2, 3};
    cout<<"ANS: "<<min_coin_change(nums, 5);

    return 0;
}