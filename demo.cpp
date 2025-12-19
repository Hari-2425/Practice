#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

vector<int> cyclicalTraversal(vector<vector<int>> v, int &top, int &bottom, int &left, int &right){
    
    vector<int> res;
    //left to right
    for(int i=left;i<=right;i++){
        res.push_back(v[top][i]);
    }
    top++;
    //top to bottom
    for(int i=top;i<=bottom;i++){
        res.push_back(v[i][right]);
    }
    right--;
    //right to left
    if(top<=bottom){
        for(int i=right;i>=left;i--){
            res.push_back(v[bottom][i]);
        }
        bottom--;
    }
    //bottom to top
    if(left<=right){
        for(int i=bottom;i>=top;i--){
            res.push_back(v[i][left]);
        }
        left++;
    }
    return res;
}

bool isPrime(int n){
    if(n <= 1) return false;
    if(n<=3) return true;
    if(n%2==0 || n%3==0) return false;
    for(int i=5;i*i<=n;i+=6){
        if(n%i==0 || n%(i+2)==0){
            return false;
        }
    }
    return true;
}

bool isComposite(int num) {
    if (num <= 1) return false; 
    if (num == 2 || num == 3) return false; 
    if (num % 2 == 0 || num % 3 == 0) return true; 
    for (int i = 5; i * i <= num; i += 6) { 
        if (num % i == 0 || num % (i + 2) == 0) return true; 
    } 
    return false;
}

bool isValidPermutation(const std::vector<int>& perm) { 
    for (size_t i = 0; i < perm.size() - 1; ++i) { 
        if (!isComposite(perm[i] + perm[i + 1])) { 
            return false; 
        } 
    } 
    return true; 
}

bool generateValidPermutation(std::vector<int>& perm, int l, int r, std::vector<int>& result) { 
    if (l == r) { 
        if (isValidPermutation(perm)) { 
            result = perm; return true; 
        } 
    } 
    else { 
        for (int i = l; i <= r; ++i) { 
            std::swap(perm[l], perm[i]); 
            if (l == 0 || isComposite(perm[l-1] + perm[l])) { 
                if (generateValidPermutation(perm, l + 1, r, result)) { 
                    return true; 
                } 
            } 
        std::swap(perm[l], perm[i]); // backtrack 
        } 
    } 
    return false; 
}

int median(vector<int> ar){
    sort(ar.begin(), ar.end());
    return ar[ar.size()/2];
}

int GCD(int a, int b){
    if(b==0)
        return a;
    return GCD(b, a%b);
}

int maxSubarraySum(vector<int> nums, int k){

    // 1. cover edge/base cases 
    // 2. inside the loop
    //      a. curr variable ki value ko update kro
    //      b. check the condition of your window size and update ans, start and curr variables
    // 3. return your ans
    if (nums.empty() || k <= 0 || k > nums.size()) {
        return 0;
    }

    int maxSum = -1e9; // Initialize maxSum to a very small number
    int currentSum = 0;
    int windowStart = 0;

    for (int windowEnd = 0; windowEnd < nums.size(); ++windowEnd) {
        currentSum += nums[windowEnd]; // Add the next element to the window

        // Slide the window once it reaches size k
        if (windowEnd >= k - 1) {
            maxSum = std::max(maxSum, currentSum); // Update maxSum
            currentSum -= nums[windowStart]; // Subtract the element going out of the window
            windowStart++; // Slide the window forward
        }
    }

    return maxSum;
}

string minWindow(string s, string t){
    if(t.size() == 0){
        return "";
    }
    unordered_map<char, int> mps, mpt;
    for(auto i: t){
        mpt[i]++;
    }
    int start_index = -1;
    int left=0, right=0, minLen=1e9, formed=0;

    for(;right<s.length();++right){
        char currChar = s[right];
        mps[currChar]++;
        if(mpt.count(currChar) && mpt[currChar]==mps[currChar]){
            formed++;
        }
        while (left<=right && formed==mpt.size())
        {
            currChar = s[left];
            if(right-left+1 < minLen){
                minLen = right-left+1;
                start_index = left;
            }

            mps[currChar]--;
            if(mpt.count(currChar) && mps[currChar]<mpt[currChar]){
                formed--;
            }

            left++;
        }
        
    }
    if(start_index == -1){
        return "";
    }
    return s.substr(start_index, minLen);
}

struct node
{
    int x, y;
    node(int x, int y){
        this->x = x;
        this->y = y;
    }
};

int BFS(vector<vector<int>>& grid, vector<vector<bool>> &vis, int k){
    queue<node> nodeQ;
    nodeQ.push(node(0, 0));

    int ans = 0;
    
    while (!nodeQ.empty())
    {
        node curr = nodeQ.front();
        vis[curr.x][curr.y] = 1;
        ans++;
        nodeQ.pop();
        // Left
        if(grid[curr.x][curr.y] < k && curr.x-1>=0 && !vis[curr.x-1][curr.y]){
            nodeQ.push(node(curr.x-1, curr.y));
        }

        // Up
        if(grid[curr.x][curr.y] < k && curr.y-1>=0 && !vis[curr.x][curr.y-1]){
            nodeQ.push(node(curr.x, curr.y-1));
        }

        // Right
        if(grid[curr.x][curr.y] < k && curr.x+1<grid.size() && !vis[curr.x+1][curr.y]){
            nodeQ.push(node(curr.x+1, curr.y));
        }

        // Down
        if(grid[curr.x][curr.y] < k && curr.y+1<grid[0].size() && !vis[curr.x][curr.y+1]){
            nodeQ.push(node(curr.x, curr.y+1));
        }

    }
    return ans;
}

vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
    int m=grid.size(), n=grid[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, 0));
    vector<int> res;
    for(auto it: queries){
        int ans = BFS(grid, vis, it);
        cout<<ans<<endl;
        res.push_back(ans);
        vis.clear();
    }
    return res;
}

double median_func(vector<int> arr){
    int n = arr.size();
    std::sort(arr.begin(), arr.end());
    double result;
    if (n % 2 == 1) {
        result = static_cast<double>(arr[n / 2]); // For odd size, the middle element
    } else {
        result = (static_cast<double>(arr[n / 2 - 1]) + static_cast<double>(arr[n / 2])) / 2.0; // Average of the two middle elements
    }
    return result;
}

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    if(nums.size()==0 || k==0){
        return {};
    }
    int left=0, right=0;
    vector<double> res;

    for(;right+k<nums.size();++right){
        auto startIt = nums.begin() + right;
        auto endIt = nums.begin() + right + k;
        vector<int> tmp;
        tmp.assign(startIt, endIt);
        double med = median_func(tmp);
        res.push_back(med);
    }
    return res;
}

void solve(ifstream &cin){
    
    int n, m;
    cin>>n>>m;
    char u='U', d='D', l='L', r='R', uk='?';
    vector<string> ar(n);
    for(int i=0;i<n;i++){
        cin>>ar[i];
    }
    vector<vector<int>> unKnowns;
    vector<vector<int>> exits;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(ar[i][j]==uk){
                unKnowns.push_back({i, j});
            }
        }
    }

    for(int i=0;i<m;i++){
        if(ar[0][i]==u){
            exits.push_back({0, i});
        }
    }

    for(int i=1;i<n;i++){
        if(ar[i][m-1]==r){
            exits.push_back({i, m-1});
        }
    }

    for(int i=m-2;i>=0;i--){
        if(ar[n-1][i]==d){
            exits.push_back({n-1, i});
        }
    }

    for(int i=n-2;i>0;i--){
        if(ar[i][0]==l){
            exits.push_back({i, 0});
        }
    }

}

long long minOperationsToMakeMedianK(vector<int>& nums, int k) {
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int med = nums[n/2];
    long long ans=0;
    if(med < k){
        for(int i=n/2;i<n && nums[i]<k;++i){
            ans += (k-nums[i]);
        }
    }
    else if(med > k){
        for(int i=n/2;i>=0 && nums[i]>k;--i){
            ans += (nums[i]-k);
        }
    }
    return ans;
}


vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;
    vector<vector<string>> res;
    for(int i=0;i<strs.size();i++){
        vector<int> arr(26, 0);
        string curr = strs[i];
        sort(curr.begin(), curr.end());
        mp[curr].push_back(strs[i]);
    }
    for(auto it: mp){
        res.push_back(it.second);
    }
    return res;
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans;
    unordered_map<int, int> count;
    for(int i=0;i<n;i++){
        count[i]++;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
    for(auto it: count){
        pq.push({-1*it.second, it.first});
    }
    while(k){
        pair<int, int> tp = pq.top();
        ans.push_back(tp.second);
        pq.pop();
    }
    return ans;
}

int longestConsecutive(vector<int>& nums) {
    if(nums.size()==0) return 0;
    unordered_set<int> us;
    for(int i=0;i<nums.size();i++){
        us.insert(nums[i]);
    }
    int ans = INT_MIN;
    for(auto it: us){
        int x = it;
        
        if(us.find(x-1)==us.end()){
            int cnt = 0;
            while (us.find(x+1)!=us.end())
            {
                cnt++;
                x++;
            }
            ans = max(ans, cnt);
        }
        
    }
    return ans;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    if(n < 3){
        return {};
    }
    // unordered_map<int, int> count;
    // for(auto it: nums){
    //     count[it]++;
    // }
    unordered_set<int> count;
    vector<vector<int>> ans;
    set<vector<int>> hs;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            vector<int> tmp;
            // count[nums[i]]--;
            // count[nums[j]]--;
            int el = 0 - (nums[i]+nums[j]);
            if(count.find(el) != count.end()){
                tmp = {nums[i], nums[j], el};
                sort(tmp.begin(), tmp.end());
                hs.insert(tmp);
            }
            count.insert(nums[j]);
            // count[nums[i]]++;
            // count[nums[j]]++;
        }
    }
    for(auto it: hs){
        ans.push_back(it);
    }
    return ans;
}

int maxArea(vector<int>& heights) {
    int n=heights.size();
    int l=0, r=n-1, ans=0;
    int lMax=heights[0], rMax=heights[n-1];
    while(l<=r){
        if(heights[l] <= heights[r]){
            if(heights[l] < lMax){
                ans += lMax-heights[l];
            }
            else{
                lMax = heights[l];
            }
            l++;
        }
        else{
            if(heights[r] < rMax){
                ans += rMax-heights[r];
            }
            else{
                rMax = heights[r];
            }
            r--;
        }
    }
    return ans;
}

int maxProfit(vector<int>& prices) {
    int minP = INT_MAX;
    int ans = 0;
    for(int i=0;i<prices.size();i++){
        minP = min(minP, prices[i]);
        ans = max(ans, prices[i]-minP);
    }
    return ans;
}

int lengthOfLongestSubstring(string s) {
    int n = s.size();
    int left=0, right=0, ans=INT_MIN;
    unordered_set<char> count;
    while(right < n){
        char ch = s[right];
        
        if(count.find(ch) != count.end()){
            ans = max(ans, (right-left));
            while (count.find(ch) != count.end())
            {
                count.erase(s[left]);
                left++;
            }
        }
        count.insert(ch);
        right++;
    }
    return ans;
}

int longestValidSubstring(vector<string> forbidden, string words){
    if(words.length() == 0) return 0;
    unordered_map<string, int> bag;
    for(auto s: forbidden){
        bag[s] = 1;
    }
    int n = words.length();
    int l = n-1, r = n-1, maxLen = INT_MIN;

    while(l > -1){
        for(int i=l;i<=std::min(r, l+9);i++){
            string tmp = words.substr(l, i-l+1);
            if(bag.find(tmp)!=bag.end() || bag[tmp]!=1){
                r = i-1;
                break;
            }
        }
        maxLen = std::max(maxLen, r-l+1);
        l--;
    }
    return maxLen;
}

    void hlpr(vector<int>& nums, vector<bool> &used, vector<int> &curr, vector<vector<int>> &store){
        if(curr.size() == nums.size()){
            store.push_back(curr);
            return;
        }
        for(int i=0;i<nums.size();i++){
            if(!used[i]){
                curr.push_back(nums[i]);
                used[i] = true;
                hlpr(nums, used, curr, store);
                used[i] = false;
                curr.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> curr;
        vector<bool> used(nums.size(), false);
        vector<vector<int>> res;
        hlpr(nums, used, curr, res);
        return res;
    }
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    void hlpr(vector<int> &arr, TreeNode* root){
        if(root == nullptr){
            return;
        }
        hlpr(arr, root->left);
        arr.push_back(root->val);
        hlpr(arr, root->right);
    }

    

    char nextGreatestLetter(vector<char>& letters, char target) {
        int low=0, high=letters.size()-1, mid=low+(high-low)/2;
        while(low<=high){
            mid=low+(high-low)/2;
            if(letters[mid]>target){
                if(mid==0 || mid-1==0){
                    return letters[0];
                }
                else if(letters[mid-1]<=target){
                    return letters[mid];
                }
            }
            else{
                if(letters[mid]<target){
                    low = mid+1;
                }
                else if(letters[mid]>target){
                    high = mid-1;
                }
            }
        }
        return letters[0];
    }

    TreeNode* increasingBST(TreeNode* root) {
        vector<int> arr;
        hlpr(arr, root);
        if(arr.size()>0){
            TreeNode* ans = new TreeNode(arr[0]);
            TreeNode* curr = ans;
            for(int i=1;i<arr.size();i++){
                curr->right = new TreeNode(arr[i]);
                curr = curr->right;
            }
            return ans;
        }
        return nullptr;
    }

    vector<int> findRightInterval(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<pair<int, int>> starts(n);
        for (int i = 0; i < n; ++i) starts[i] = {intervals[i][0], i};
        sort(starts.begin(), starts.end());
        vector<int> res(n, -1);
        for (int i = 0; i < n; ++i) {
            int target = intervals[i][1];
            int low = 0, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (starts[mid].first >= target) high = mid - 1;
                else low = mid + 1;
            }
            if (low < n) res[i] = starts[low].second;
        }
        return res;
    }

class SnapshotArray {
public:
    vector<int> arr;
    map<int, vector<int>> mp;
    int cntr;
    SnapshotArray(int length) {
        cntr = -1;
        arr = vector<int>(length, 0);
    }
    
    void set(int index, int val) {
        arr[index] = val;
    }
    
    int snap() {
        cntr++;
        mp[cntr] = arr;
        return cntr;
    }
    
    int get(int index, int snap_id) {
        return mp[snap_id][index];
    }
};

int FirstOccur(vector<int> arr, int target){
    int low=0, high=arr.size()-1, ans=-1;
    while (low <= high)
    {
        /* code */
        int mid = low + (high-low)/2;
        if(arr[mid]>=target){
            high = mid-1;
            if(arr[mid]==target){
                ans = mid;
            }
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}

int LastOccur(vector<int> arr, int target){
    int low=0, high=arr.size()-1, ans=-1;
    while (low <= high)
    {
        /* code */
        int mid = low + (high-low)/2;
        if(arr[mid]<=target){
            low = mid+1;
            if(arr[mid]==target){
                ans = mid;
            }
        }
        else{
            high = mid-1;
        }
    }
    return ans;
}

int BinarySearchinRotatedArray(vector<int> arr, int target){
    int n=arr.size();
    int low=0, high=n-1;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(arr[mid]==target){
            return mid;
        }

        if(arr[low]==arr[mid] && arr[mid]==arr[high]){
            low++;
            high--;
            continue;
        }
        
        if(arr[mid]>=arr[low]){
            if(arr[mid]>target && target>=arr[low]){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        else{
            if(target<=arr[high] && arr[mid]<target){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
    return -1;
}

int FindMinRotatedArray(vector<int> arr){
    int n = arr.size();
    int low = 0, high = n - 1;

    while (low < high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] < arr[high]) {
            // Minimum is in left half (including mid)
            high = mid;
        } else if (arr[mid] > arr[high]) {
            // Minimum is in right half (excluding mid)
            low = mid + 1;
        } else {
            // Cannot determine, reduce search space
            high--;
        }
    }

    return arr[low];  // or return low if index is required
}

int FindMaxRotatedArray(vector<int> arr){
    int n = arr.size();
    int low=0, high=n-1;
    while (low<high)
    {
        int mid = low + (high-low)/2;
        if(arr[mid]>arr[low]){ // max is present in right half(including mid)
            low = mid;
        }
        else if(arr[mid]<arr[low]){// max is present in left half(excluding mid)
            high = mid-1;
        }
        else{
            high--;
            low++;
        }
    }
    return high;
}

int numOfRotations(vector<int> arr){
    int n = arr.size();
    return FindMinRotatedArray(arr);
}

// all elements are present 2 times except 1 which is single
// Return single element
// time complexity - O(logn)
int BinarySearchSingleVal(vector<int> arr){
    int n = arr.size();
    if(n == 1) return arr[0];
    int low=1, high=n-2;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(arr[mid]!=arr[mid-1] && arr[mid]!=arr[mid+1]){
            return arr[mid];
        }
        if(mid%2==1 && arr[mid-1]==arr[mid] ||
            mid%2==0 && arr[mid]==arr[mid+1])
            low = mid+1; // eliminate left half
        else
            high = mid-1; // eliminate right half
    }
    return -1;
}

// Find Peak element in mountain array
int FindPeak(vector<int> arr){
    int n = arr.size();
    if(n==1) return arr[0];
    if(arr[0]>arr[1]) return arr[0];
    if(arr[n-1]>arr[n-2]) return arr[n-1];
    int low=1, high=n-2;
    while(low<=high){
        int mid = low + (high-low)/2;
        if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1])
            return arr[mid];
        else if(arr[mid]<=arr[mid+1]){
            low = mid+1; // eliminate left half
        }
        else{
            high = mid-1; // eliminate right half
        }
    }
    return -1;
}

long ReqTime(vector<int> &arr, int t){
    long ans = 0;
    for(int i=0;i<arr.size();i++){
        // ans += ((arr[i] + t - 1) / t);
        if(arr[i]%t != 0){
            ans += arr[i]/t + 1;
        }
        else{
            ans += arr[i]/t;
        }
    }
    return ans;
}

int KokoBananaProb(vector<int> arr, int h){
    int n = arr.size(), ans=-1;
    int low=1, high=INT_MIN;
    for(int i=0;i<n;i++){
        high = max(arr[i], high);
    }
    while(low<=high){
        int mid = low + (high-low)/2;
        int time = ReqTime(arr, mid);
        if(time <= h){
            ans = time;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}

bool IsEnough(vector<int>& bloomDay, int d, int k, int m){
    int cnt = 0, adj = 0;
    for(int i = 0; i < bloomDay.size(); i++){
        if(bloomDay[i] <= d){
            adj++;
            if(adj == k){
                cnt++;
                adj = 0; // reset for the next bouquet
            }
        } else {
            adj = 0; // reset because flowers must be adjacent
        }
    }
    return cnt >= m;
}

int minDays(vector<int>& bloomDay, int m, int k) {
    int n = bloomDay.size(), ans=-1;
    long l = m*k;
    if(l > n) return -1;
    int low=1, high=INT_MIN;
    for(int i=0;i<n;i++){
        high = max(high, bloomDay[i]);
    }
    while(low<=high){
        int mid = low + (high-low)/2;
        if(IsEnough(bloomDay, mid, k, m)){
            high = mid-1;
            ans = mid;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}


int KthMissingNum(vector<int> arr, int k){
    int low=0, high=arr.size()-1;
    
    while(low<=high){
        int mid = low + (high-low)/2;
        int cnt = arr[mid]-(mid+1);
        if(cnt<k){
            low = mid+1; //Eliminate left half
        }
        else{
            high = mid-1; //Eliminate right half
        }
    }
    return high+1+k;
}

bool IsPossible(vector<int> arr, int dist, int k){
    int n=arr.size(), prev = arr[0];
    k--;
    for(int i=1;i<n;i++){
        
        if(arr[i]-prev >= dist){
            k--;
            prev = arr[i];
        }

        if(k == 0){
            return true;
        }
    }
    return false;
}

int AggressiveCows(vector<int> arr, int k){
    int n = arr.size(), ans=-1;
    sort(arr.begin(), arr.end());
    int low = 0, high = arr[n-1]-arr[0];
    while(low<=high){
        int mid = low + (high-low)/2;
        if(IsPossible(arr, mid, k)){
            ans = mid;
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return ans;
}

bool Check(vector<int> arr, int sum, int k){
    int n = arr.size();
    int curr = 0, ans = 1;
    for(int i=0;i<n;i++){
        if(arr[i] > sum) return false;
        if(curr+arr[i] > sum){
            ans++;
            curr = arr[i];
        }
        else{
            curr += arr[i];
        }
    }
    return (ans<=k);
}

int splitArray(vector<int>& nums, int k) {
    int n = nums.size(), low=0, high=0, ans=-1;
    for(int i=0;i<n;i++){
        high += nums[i];
    }
    while(low<=high){
        int mid = low + (high-low)/2;
        if(Check(nums, mid, k)){
            ans = mid;
            high = mid-1;
        }
        else{
            low = mid+1;
        }
    }
    return ans;
}

vector<int> decimalRepresentation(int n) {
    int fact = 1;
    vector<int> ans;
    while(n > 0){
        int dig = n%10;
        ans.push_back(dig*fact);
        fact *= 10;
        n = n/10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

long long splitArray(vector<int>& nums) {
    int n = nums.size();
    if(n==2) return abs(nums[0]-nums[n-1]);
    int l = -1, r = n;
    int left = INT_MIN, right = INT_MIN;
    long long left_sum=0, right_sum=0;
    while(l < r){
        if(left >= nums[l+1] || right >= nums[r-1]){
            break;
        }
        left = nums[l+1];
        right = nums[r-1];
        left_sum += nums[l+1];
        right_sum += nums[r-1];
        l++;
        r--;
    }
    while(l<r && left<nums[l+1]){
        left_sum += nums[l+1];
        left = nums[l+1];
        l++;
    }
    while(l<r && right<nums[r-1]){
        right_sum += nums[r-1];
        right = nums[r-1];
        r--;
    }
    if(abs(l-r)>1) return -1;
    if(l == r)
        return min(abs(left_sum-right_sum+nums[l]), abs(right_sum-left_sum+nums[l]));
    return abs(left_sum-right_sum);
}

int main(){
    
   vector<int> stalls = {1, 2, 8, 4, 9};
    int cows = 3;
    cout << AggressiveCows(stalls, cows);
}