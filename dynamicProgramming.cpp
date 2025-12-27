#include <bits/stdc++.h>
using namespace std;

void Display(vector<vector<int>> &vec){
    for(int i=0;i<vec.size();i++){
        for(int j=0;j<vec[0].size();j++){
            cout<<vec[i][j]<<" ";
        }
        cout<<"\n";
    }
}

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


// *******LONGEST COMMON SUBSEQUENCE*******
// Recusrsive version
int LCS_recursive(string &a, string &b, int i, int j, vector<vector<int>>& dp){
    if(i==0 || j==0)
        return 0;
    if(dp[i][j] != -1)
        return dp[i][j];
    if(a[i-1] == b[j-1]){
        return dp[i][j] = 1 + LCS_recursive(a, b, i-1, j-1, dp);
    }
    return dp[i][j] = max(LCS_recursive(a, b, i-1, j, dp), LCS_recursive(a, b, i, j-1, dp));
}

// Iterative version
int LCS_iterative(string x, string y){
    int m=x.length(), n=y.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(x[i-1] == y[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    int i=m, j=n;
    string ans = "";
    while(i>0 && j>0){
        if(x[i-1] == y[j-1]){
            ans.push_back(x[i-1]);
            i--;
            j--;
        }
        else if(dp[i][j-1] >= dp[i-1][j]){
            j--;
        }
        else{
            i--;
        }
    }
    reverse(ans.begin(), ans.end());
    cout<<ans<<"\n";
    return dp[m][n];
}


// *******LONGEST COMMON SUBSTRING*******
int LongestCommonSubstring(string x, string y){
    int m=x.length(), n=y.length();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(x[i-1] == y[j-1]){
                dp[i][j] = 1 + dp[i-1][j-1];
            }
            else{
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    string ans = "";
    string finalAns = "";
    int maxLen = 0;
    int i=m, j=n;
    while(i>0 && j>0){
        if(x[i-1] == y[j-1]){
            ans.push_back(x[i-1]);
            i--;
            j--;
        }
        else{
            if(dp[i-1][j] >= dp[i][j-1]){
                i--;
            }
            else{
                j--;
            }
            if(ans.size() > maxLen){
                maxLen = ans.size();
                finalAns = ans;
                ans = "";
            }
        }
    }

    cout<<finalAns<<"\n";

    return finalAns.size();
}

string LongestRepeatingSubsequence(string s) {
    int n = s.length();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == s[j - 1] && i != j) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    cout << "Length: " << dp[n][n] << "\n";

    // Correct backtracking
    int i = n, j = n;
    string ans = "";

    while (i > 0 && j > 0) {
        if (s[i - 1] == s[j - 1] && i != j &&
            dp[i][j] == 1 + dp[i - 1][j - 1]) {

            ans.push_back(s[i - 1]);
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

int LexicographicallyGreaterCount_hlpr(int i, int j, int grtr,
    string s, string t, unordered_map<string, int> &dp){
    int MOD = 1e9+7;
    if(i == s.size()){
        return (grtr == 1) ? 1 : 0;
    }
    string key = to_string(i) + " " + to_string(j) + " " + to_string(grtr);
    if(dp.find(key) != dp.end()){
        return dp[key];
    }

    long long res = 0;
    // skip s[i]
    res = LexicographicallyGreaterCount_hlpr(i+1, j, grtr, s, t, dp) % MOD;

    // take s[i]
    if(grtr){
        // Already lex greater
        res = (res + LexicographicallyGreaterCount_hlpr(i+1, j, 1, s, t, dp)) % MOD;
    }
    else{
        // Still matching
        if(j < t.size()){
            if(s[i] > t[j]){
                res = (res + LexicographicallyGreaterCount_hlpr(i+1, j+1, 1, s, t, dp))%MOD;
            }
            else if(s[i]==s[j]){
                res = (res + LexicographicallyGreaterCount_hlpr(i+1, j+1, 0, s, t, dp))%MOD;
            }
        }
        else{
            // t exhausted
            res = (res + LexicographicallyGreaterCount_hlpr(i+1, j, 1, s, t, dp))%MOD;
        }
    }
    return dp[key] = res;
}

int LexicographicallyGreaterCount(string s, string t){
    return 0;
}


// ***** Matrix Chain Multiplication *****
// Pattern: Partition DP (Matrix Chain Multiplication)
//
// Problem type:
// - Given a range [i..j]
// - Try all possible partitions k in [i..j-1]
// - Combine left and right subproblems
// - Take MIN / MAX based on problem requirement
//

// 2 For Loop strategies that can be used for MCM pattern
// for(k=i;k<j;k++) Partition1: i to k, Partition2: k+1 to j-1
// for(k=i+1;k<=j;k++) Partition1: i to k-1, Partition2: k+1 to j

// Recurrence:
// dp[i][j] = min over k=i..j-1 of
//            (dp[i][k] + dp[k+1][j] + cost of combining)
//
// Base Case:
// i >= j  → single matrix or no matrix → cost = 0

int Solve(int i, int j, vector<int> &nums,
          vector<vector<int>> &dp) {
    // 40, 20, 30, 10, 30
    // Base case: no multiplication needed
    if (i >= j)
        return 0;

    // Memoization check
    if (dp[i][j] != -1)
        return dp[i][j];

    int ans = INT_MAX;

    // Try all possible partition points
    for (int k = i; k < j; k++) {

        // Solve left and right partitions
        int left  = Solve(i, k, nums, dp);
        int right = Solve(k+1, j, nums, dp);

        // Cost of multiplying two resulting matrices
        int cost = nums[i - 1] * nums[k] * nums[j]
                   + left + right;

        // Take minimum among all partitions
        ans = min(ans, cost);
    }

    // Store and return result
    return dp[i][j] = ans;
}

int MCM(vector<int> &nums) {
    int n = nums.size();

    // dp[i][j] → minimum cost to multiply matrices i..j
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

    return Solve(1, n - 1, nums, dp);
}

bool isPalindrome(string s, int i, int j){
    while(i<=j){
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}
int MinPalindromePartition_solve(int i, int j, string s,
    vector<vector<int>> &dp){
    if(i >= j)
        return 0;
    if(dp[i][j] != -1)
        return dp[i][j];
    if(isPalindrome(s, i, j)){
        return dp[i][j] = 0;
    }
    int minCost = INT_MAX;
    for(int k=i;k<j;k++){
        int count = 1 + MinPalindromePartition_solve(i, k, s, dp) +
                    MinPalindromePartition_solve(k+1, j, s, dp);
        if(count < minCost){
            minCost = count;
        }
    }
    return dp[i][j] = minCost;
}
int MinPalindromePartition(string s){
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return MinPalindromePartition_solve(0, n-1, s, dp);
}

int EvalExprToTrue_hlpr(string s, int i, int j, bool isTrue,
                       map<tuple<int,int,bool>, int> &memo) {

    // Base case: invalid range
    if (i > j)
        return 0;

    // Base case: single operand
    if (i == j) {
        if (isTrue)
            return s[i] == 'T';
        else
            return s[i] == 'F';
    }

    // Memoization key
    // string key = to_string(i) + " " + to_string(j) + " " + to_string(isTrue);
    if (memo.count({i, j, isTrue}))
        return memo[{i, j, isTrue}];

    int ans = 0;

    // Partition expression at every operator
    for (int k = i + 1; k < j; k += 2) {

        // Recursively compute all possibilities
        int LT = EvalExprToTrue_hlpr(s, i, k - 1, true, memo);
        int LF = EvalExprToTrue_hlpr(s, i, k - 1, false, memo);
        int RT = EvalExprToTrue_hlpr(s, k + 1, j, true, memo);
        int RF = EvalExprToTrue_hlpr(s, k + 1, j, false, memo);

        // Evaluate based on operator at position k
        if (s[k] == '|') {
            if (isTrue)
                ans += LT * RT + LT * RF + LF * RT;
            else
                ans += LF * RF;
        }
        else if (s[k] == '&') {
            if (isTrue)
                ans += LT * RT;
            else
                ans += LF * RF + LT * RF + LF * RT;
        }
        else if (s[k] == '^') {
            if (isTrue)
                ans += LT * RF + LF * RT;
            else
                ans += LT * RT + LF * RF;
        }
    }

    // Store result before returning
    memo[{i, j, isTrue}] = ans;
    return ans;
}

int EvalExprToTrue(string s) {
    map<tuple<int,int,bool>, int> memo;
    return EvalExprToTrue_hlpr(s, 0, s.length() - 1, true, memo);
}

int EggDroppingProblem_hlpr(int e, int s, int t, map<tuple<int, int, int>, int> &dp){
    if(e==0){
        return 0;
    }
    if(s>t){
        return 0;
    }
    if(e==1){
        return t-s+1;
    }
    if(t == s){
        return 1;
    }
    if(dp.count({e, s, t})){
        return dp[{e, s, t}];
    }
    int ans = INT_MAX;
    for(int k=s;k<=t;k++){
        int brk = 1 + EggDroppingProblem_hlpr(e-1, s, k-1, dp);
        int notbrk = 1 + EggDroppingProblem_hlpr(e, k+1, t, dp);
        ans = min(ans, brk + notbrk);
    }
    return dp[{e, s, t}] = ans;
}

int EggDroppingProblem(int e, int f){
    map<tuple<int, int, int>, int> dp;
    return EggDroppingProblem_hlpr(e, 1, f, dp);
}



int main(){
    
    // vector<int> nums = {1, 2, 3};
    // cout<<"ANS: "<<min_coin_change(nums, 5);

    // string a = "abcdgh";
    // string b = "abedgh";
    // string c = "agtxbcbxhia";
    // string d = c;
    // reverse(d.begin(), d.end());
    // vector<vector<int>> dp(a.length()+1, vector<int>(b.length()+1, -1));
    // cout<<LCS_recursive(a, b, a.length(), b.length(), dp)<<"\n";
    // cout<<LCS_iterative(c, d);
    // string e = "AAEBCBDDXVXABDX";
    
    // vector<int> nums = {40, 20, 30, 10, 30};
    // cout<<MCM(nums);

    // string s = "T|F&T^F";
    // cout<<EvalExprToTrue(s);

    cout<<EggDroppingProblem(3, 5);

    return 0;
}