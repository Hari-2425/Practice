#include <bits/stdc++.h>
using namespace std;

/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution {
    public:

    Solution(){}

    void Display(ListNode* head){
        ListNode* curr = head;
        while(curr!=nullptr){
            cout<<curr->val<<" ";
            curr = curr->next;
        }
        cout<<"\n";
    }

    vector<int> longestPalindrome_hlpr(int l, int r, string &s){
        while(l>=0 && r<s.length() && s[r]==s[l]){
            l--;
            r++;
        }
        return {l+1, r-1};
    }

    string longestPalindrome(string s) {
        vector<int> ls = {0, 0};
        for(int i=1;i<s.length();i++){
            if(s[i]==s[i-1]){
                vector<int> tmp = longestPalindrome_hlpr(i, i-1, s);
                if(tmp[1]-tmp[0]+1 > ls[1]-ls[0]+1){
                    ls = tmp;
                }
            }
            vector<int> tmp = longestPalindrome_hlpr(i, i, s);
            if(tmp[1]-tmp[0]+1 > ls[1]-ls[0]+1){
                ls = tmp;
            }
        }
        return s.substr(ls[0], ls[1]-ls[0]+1);
    }

    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        unordered_map<char, int> idx;
        int l=0, r=0, ans=0;
        while(r<n){

            if(idx.count(s[r])){
                l = max(l, idx[s[r]]+1);
            }
            idx[s[r]] = r;
            ans = max(ans, r-l+1);
            r++;
        }

        return ans;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *curr1, *curr2, *_Dummy;
        curr1 = l1;
        curr2 = l2;
        ListNode* dummy = new ListNode(-1);
        _Dummy = dummy;
        int carry = 0;

        //3->2->1->null => 123

        while(curr1!=nullptr && curr2!=nullptr){
            int num = curr1->val + curr2->val + carry;
            carry = num/10;
            _Dummy->next = new ListNode(num%10);
            _Dummy = _Dummy->next;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }

        while(curr1 != nullptr){
            int num = curr1->val + carry;
            carry = num/10;
            _Dummy->next = new ListNode(num%10);
            _Dummy = _Dummy->next;
            curr1 = curr1->next;
        }

        while(curr2 != nullptr){
            int num = curr2->val + carry;
            carry = num/10;
            _Dummy->next = new ListNode(num%10);
            _Dummy = _Dummy->next;
            curr2 = curr2->next;
        }

        if(carry > 0){
            _Dummy->next = new ListNode(carry);
        }

        return dummy->next;
    }

    int trap(vector<int>& height) {
        int n = height.size();
        // vector<int> l_max(n), r_max(n);
        // l_max[0] = height[0];
        // r_max[n-1] = height[n-1];
        // for(int i=1;i<n;i++){
        //     l_max[i] = max(l_max[i-1], height[i]);
        // }
        // for(int i=n-2;i>=0;i--){
        //     r_max[i] = max(r_max[i+1], height[i]);
        // }

        // 7 2 1 4 3
        // ANS = 5

        
        int ans = 0;
        int l_max=height[0], r_max=height[n-1];
        int l=0, r=n-1;

        while(l<=r){
            if(height[l] <= height[r]){
                if(height[l] < l_max){ 
                    ans += (l_max - height[l]);
                }
                else{
                    l_max = height[l];
                }
            }
            else{
                if(height[r] < r_max){ 
                    ans += (r_max - height[r]);
                }
                else{
                    r_max = height[r];
                }
            }
        }

        return ans;
    }

    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> s_map; // to store the pref sums occured.
        int n = nums.size();
        // // 1 3 6 6, k=6
        // s_map[1] = 1; // 1-6 = -5 -> No
        // s_map[4] = 1; // 4-6 = -2 -> No, ans=0
        // s_map[10] = 1; // 10-6 = 4 -> Yes, ans=1
        // s_map[16] = 1; // 16-6 = 10 -> Yes, ans=2

        int preSum = 0;
        int ans = 0;
        s_map[0] = 1;
        for(int i=0;i<n;i++){
            preSum += nums[i];
            if(s_map.count(preSum-k)){
                ans += s_map[preSum-k];
            }
            s_map[preSum]++;
        }
        return ans;
    }

    int niceSubarrays(vector<int> &nums, int k){
        int ans=0, n=nums.size();

        unordered_map<int, int> freq;
        freq[0] = 1;
        int odd=0;
        for(int i=0;i<n;i++){
            if(nums[i]%2 == 1){
                odd++;
            }
            if(freq.count(odd-k)){
                ans += freq[odd-k];
            }
            freq[odd]++;
        }
        return ans;
    }

    int lengthOfMaxSubbArraySum(vector<int> &nums, int k){
        int n=nums.size();
        unordered_map<int, int> idx_map;
        //{s: idx} oldest index

        // 1,-1,5,-2,3

        idx_map[0] = -1;
        int preSum = 0, ans = 0;
        for(int i=0;i<n;i++){
            preSum += nums[i];

            if(idx_map.count(preSum-k)){
                if(idx_map[preSum-k] == -1){
                    ans = max(ans, i+1);
                }
                else{
                    ans = max(ans, i-idx_map[preSum-k]);
                }
            }
            if(!idx_map.count(preSum)){
                idx_map[preSum] = i;
            }
        }
        return ans;
    }

    int maxLengthSubarray(vector<int> &nums){
        int n = nums.size();
        unordered_map<int, int> firstIndex;
        firstIndex[0] = -1;
        int ans = 0;
        int preSum = 0;
        for(int i=0;i<n;i++){
            if(nums[i]==0){
                preSum--;
            }
            else{
                preSum++;
            }
            if(firstIndex.count(preSum)){
                ans = max(ans, i-firstIndex[preSum]);
            }
            if(!firstIndex.count(preSum)){
                firstIndex[preSum] = i;
            }
        }
        return ans;
    }

    void generateParenthesis_hlpr(int open, int close, 
        string &par, int n, vector<string> &ans){
        
        if(close > open){
            return;
        }

        if(open>n || close>n){
            return;
        }

        if(open==n && close==n){
            ans.push_back(par);
            cout<<par<<"\n";
            return;
        }

        if(open > close){
            par += ')';
            close++;
            generateParenthesis_hlpr(open, close, par, n, ans);
            close--;
            par.pop_back();
        }
        if(open < n){
            par += '(';
            open++;
            generateParenthesis_hlpr(open, close, par, n, ans);
            open--;
            par.pop_back();
        }
    }

    vector<string> generateParenthesis(int n) {
        string par = "";
        vector<string> ans;
        int open=0, close=0;
        generateParenthesis_hlpr(open, close, par, n, ans);
        cout<<ans.size()<<"\n";
        return ans;
    }

    bool areEqual(unordered_map<char, int> &fs, unordered_map<char, int> &ft){
        for(auto t: ft){
            if(fs[t.first] < t.second){
                return 0;
            }
        }
        return 1;
    }

    string minWindow(string s, string t) {
        int m=s.length(), n=t.length();
        unordered_map<char, int> freqt, freqs;

        for(char t_char: t){
            freqt[t_char]++;
        }
        int required = freqt.size();
        int matched = 0;

        int l=0, ans=INT_MAX, idx=-1;
        for(int r=0;r<m;r++){
            freqs[s[r]]++;
            if(freqt.count(s[r]) && freqs[s[r]]>=freqt[s[r]]){
                matched++;
            }
            while(matched == required){
                if(r-l+1 < ans){
                    ans = r-l+1;
                    idx = l;
                }
                freqs[s[l]]--;
                if(freqt.count(s[l]) && freqs[s[l]]<freqt[s[l]]){
                    matched--;
                }
                l++;
            }
        }

        if(idx==-1) return "";
        return s.substr(idx, ans);
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for(int x: nums){
            freq[x]++;
        }
        vector<vector<int>> count_array(nums.size()+1, vector<int>());
        for(auto f: freq){
            count_array[f.second].push_back(f.first);
        }
        vector<int> ans;
        for(int i=count_array.size()-1;i>=0 && k>0;i--){
            for(int j=0;j<count_array[i].size() && k>0;j++){
                ans.push_back(count_array[i][j]);
                k--;
            }
        }
        return ans;
    }

    int lcs_hlpr(int i, int j, string &t1, string &t2,
        unordered_map<string, int> &dp){
        
        // base conditions
        if(i>=t1.size() || j>=t2.size()){
            return 0;
        }
        string key = to_string(i) + "_" + to_string(j);
        if(dp.count(key)){
            return dp[key];
        }
        
        int ans = 0;
        //Choices
        //1. if t1[i]==t2[j]
        if(t1[i] == t2[j]){
            ans = 1 + lcs_hlpr(i+1, j+1, t1, t2, dp);
        }
        //2. t1[i]!=t2[j]
        else{
            //a
            ans = lcs_hlpr(i+1, j, t1, t2, dp);
            //b
            ans = max(ans, lcs_hlpr(i, j+1, t1, t2, dp));
        }
        return dp[key] = ans;
    }

    int lcs(string &t1, string &t2){
        // unordered_map<string, int> dp;
        // return lcs_hlpr(0, 0, t1, t2, dp);
        int m=t1.size(), n=t2.size();
        // vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        vector<int> prev(n+1, 0), curr(n+1, 0);
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(t1[i-1] == t2[j-1]){
                    curr[j] = 1 + prev[j-1];
                }
                else{
                    curr[j] = max(curr[j-1], prev[j]);
                }
            }
            prev = curr;
        }
        return curr[n];
    }

    //t1, t2, i, j
    // if t1[i]==t2[j] -> hlpr(i+1, j+1)
    // else -> min(hlpr(i, j+1,), hlpr(i+1, j))

    int editDistance_hlpr(int i, int j, string &w1, string &w2, 
        vector<vector<int>> &dp){
        if(i >= w1.size()){
            return w2.size()-j;
        }
        if(j >= w2.size()){
            return w1.size()-i;
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        if(w1[i] == w2[j]){
            return dp[i][j] =  editDistance_hlpr(i+1, j+1, w1, w2, dp);
        }
        else{
            int del = editDistance_hlpr(i+1, j, w1, w2, dp);
            int rep = editDistance_hlpr(i+1, j+1, w1, w2, dp);
            int add = editDistance_hlpr(i, j+1, w1, w2, dp);
            return dp[i][j] = 1 + min(del, min(rep, add));
        }
    }

    int editDistance(string &w1, string &w2){
        int m=w1.size(), n=w2.size();
        // vector<vector<int>> dp(m+1, vector<int>(n+1, -1));

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=1;i<=n;i++){
            dp[0][i] = i; // delete
        }

        for(int i=1;i<=m;i++){
            dp[i][0] = i; // insert
        }

        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(w1[i-1] == w2[j-1]){
                    dp[i][j] = dp[i-1][j-1];
                }
                else{
                    dp[i][j] = 1 + min(dp[i-1][j-1], 
                        min(dp[i-1][j], dp[i][j-1]));
                }
            }
        }

        return dp[m][n];

    }

    int distinctSubsequences_hlpr(int i, int j, string &w1, string& w2,
        vector<vector<int>> &dp){

        //base cases
        if(j>=w2.size()){
            return 1;
        }

        if(i >= w1.size()){
            return 0;
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        if(w1[i]==w2[j]){
            return dp[i][j] = distinctSubsequences_hlpr(i+1, j+1, w1, w2, dp) +
            distinctSubsequences_hlpr(i+1, j, w1, w2, dp);
        }
        else{
            return dp[i][j] = distinctSubsequences_hlpr(i+1, j, w1, w2, dp);
        }
    }

    int distinctSubsequences(string &w1, string &w2){
        int m=w1.length(), n=w2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        // return distinctSubsequences_hlpr(0, 0, w1, w2, dp);

        for(int i=0;i<=m;i++){
            dp[i][0] = 1;
        }

        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(w1[i-1] == w2[j-1]){
                    dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[m][n];
    }

    int characterReplacement(string s, int k) {
        int n = s.length();
        int l=0, ans=0, maxF=0;
        vector<int> freq(26, 0);

        for(int r=0;r<n;r++){
            freq[s[r]-'A']++;
            if(freq[s[r]-'A'] > maxF){
                maxF = freq[s[r]-'A'];
            }
            while(r-l+1-maxF > k){
                // shrinking logic
                freq[s[l]-'A']--;
                l++;
            }
            ans = max(ans, r-l+1);
        }
        return ans;
    }

    //ABABC, k=2
    //l=0, r=0, maxF=1, freq-{{A:1}, {}}
    //l=0, r=1, maxF=1, freq-{{A:1}, {B:1}}, ans=2
    //l=0, r=2, maxF=2, freq-{{A:2}, {B:1}}, ans=3
    //l=0, r=3, maxF=2, freq-{{A:2}, {B:2}}, ans=4
    //l=1, r=4, maxF=2, freq-{{A:1}, {B:2}, {C:1}}, ans=4

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        int l=0, r=n-k;

        //[1 2 3 4 5 6 7]  k=4, x=4
        // l r

        while(l < r){
            int mid = l + (r-l)/2; // 
            int l_diff = x-arr[mid]; 
            int r_diff = arr[mid+k]-x; 
            if(l_diff > r_diff){
                // move right
                l = mid+1; 
            }
            else{
                r = mid;
            }
        }
        vector<int> ans;
        while(k--){
            ans.push_back(arr[l++]);
        }
        return ans;
    }

    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int low=0, mid=0, high=n-1;
        // [{0... low-1} {low... mid-1} {mid... high-1} {high... n-1}]

        while(mid < high){
            if(nums[mid]==0){
                swap(nums[low], nums[mid]);
                mid++;
                low++;
            }
            else if(nums[mid]==2){
                swap(nums[high], nums[mid]);
                high--;
            }
            else{
                mid++;
            }
        }
    }

    bool canFinish(int k, vector<int> &piles, int h){
        for(int i=0;h>0 && i<piles.size();i++){
            h -= (piles[i]+k-1)/k;
        }
        return h>=0;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int n = piles.size();

        // 3,6,7,11   h=8
        // for i=1... sum(piles) -> canFinish() -> true/false

        // binary search approach

        int l=1, r=1;
        for(int p: piles){
            r = max(p, r);
        }

        int ans = -1;
        while(l <= r){
            int mid = l + (r-l)/2;

            if(canFinish(mid, piles, h)){
                ans = mid;
                r = mid-1;
            }
            else{
                l = mid+1;
            }
        }
        return ans;
    }

    bool canSplit(vector<int> &nums, int kSum, int k){
        int sum=0;
        int i=0, count=0;
        while(i < nums.size()){
            if(sum + nums[i] > kSum){
                sum = 0;
                count++;
            }
            else{
                sum += nums[i];
                i++;
            }
            if(count > k){
                return false;
            }
        }
        return true;
    }

    int splitArray(vector<int>& nums, int k) {
        int l=INT_MAX, r=0, ans=-1;
        // search range: [min_val, arr_sum]
        for(int num: nums){
            r += num;
            l = min(l, num);
        }

        while(l <= r){
            int mid = l + (r-l)/2;
            if(canSplit(nums, mid, k)){
                ans = mid;
                r = mid-1;
            }
            else{
                l = mid+1;
            }
        }
        return ans;
    }
};

ListNode* createList(initializer_list<int> nums){
    ListNode *dummy = new ListNode(-1);
    ListNode *tail = dummy;

    for(int x : nums){
        tail->next = new ListNode(x);
        tail = tail->next;
    }

    return dummy->next;
}

vector<int> prodExceptSelf(vector<int> arr){
    // 3 5 1 7 0 9 8
    // 0 0 0 0 <num> 0 0

    // 1 2 3 -> prod = 6
    // pref = 1
    // 1 1 2 -> ans
    // suff = 1 ----- ans[i] = ans[i]*suff, suff = suff*arr[i+1]
    // 6 3 2

    // [0, 1) -> prod => prefProd && (1, n-1] -> prod => suffProd
    // for each i => ans = preProd * suffProd

    // 6 3 2

    int n = arr.size();
    // vector<int> preProd(n, 1), suffProd(n, 1);
    vector<int> ans(n, 1);
    // for(int i=1;i<n;i++){
    //     preProd[i] = arr[i-1]*preProd[i-1];
    // }
    // for(int i=n-2;i>=0;i--){
    //     suffProd[i] = arr[i+1]*suffProd[i+1];
    // }

    int pref=1, suff=1;
    for(int i=1;i<n;i++){
        pref = pref*arr[i-1];
        ans[i] = pref;
    }
    // print(ans);
    for(int i=n-2;i>=0;i--){
        suff = suff*arr[i+1];
        ans[i] = ans[i]*suff;

    }

   
    // for(int i=0;i<n;i++){
    //     ans.push_back(preProd[i]*suffProd[i]);
    // }
    return ans;
}

void print(vector<int> v, int t){
    cout<<"TestCase "<<t<<"\n";
    for(int x : v)
        cout << x << " ";
    cout << endl;
}

int main(){

    // Solution sol;
    // vector<int> h = {4,2,0,3,2,5};
    // cout<<"ANS: "<<sol.trap(h);

    Solution sol;

    vector<int> nums = {7,2,5,10,8};
    int k = 2;
    cout<<sol.splitArray(nums, k);


    return 0;
}