#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void display(vector<int> &v){
    for(auto it: v){
        cout<<it<<" ";
    }
    cout<<"\n";
}

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

// string minWindow(string s, string t){
//     if(t.size() == 0){
//         return "";
//     }
//     unordered_map<char, int> mps, mpt;
//     for(auto i: t){
//         mpt[i]++;
//     }
//     int start_index = -1;
//     int left=0, right=0, minLen=1e9, formed=0;

//     for(;right<s.length();++right){
//         char currChar = s[right];
//         mps[currChar]++;
//         if(mpt.count(currChar) && mpt[currChar]==mps[currChar]){
//             formed++;
//         }
//         while (left<=right && formed==mpt.size())
//         {
//             currChar = s[left];
//             if(right-left+1 < minLen){
//                 minLen = right-left+1;
//                 start_index = left;
//             }

//             mps[currChar]--;
//             if(mpt.count(currChar) && mps[currChar]<mpt[currChar]){
//                 formed--;
//             }

//             left++;
//         }
        
//     }
//     if(start_index == -1){
//         return "";
//     }
//     return s.substr(start_index, minLen);
// }

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


int no_of_pairs(vector<int> &nums){
    int n = nums.size();
    unordered_map<int, int> freq;
    for(int i=0;i<n;i++){
        freq[nums[i]-i]++;
    }
    int ans = 0;
    for(auto it: freq){
        if(it.second >=2){
            int val = it.second;
            ans += (val*(val-1))/2;
        }
    }
    return ans;
}

int reverse_n(int n){
    int ans = 0;
    while(n > 0){
        ans = ans*10 + (n%10);
        n /= 10;
    }
    return ans;
}

int mirrorDistance(int n) {
    if(n/10 == 0){
        return 0;
    }
    int rn = reverse_n(n);
    return abs(n - rn);  
}

long long minCost(string s, vector<int>& cost) {

    long long ans = 0;
    int n = s.length();
    long long total = 0;
    unordered_map<char, int> freq;
    for(int i=0;i<n;i++){
        total += cost[i];
        if(!freq.count(s[i])){
            freq[s[i]] = cost[i];
        }
        else{
            freq[s[i]] += cost[i];
        }
    }
    long long mn = INT_FAST64_MAX;
    for(auto it: freq){
        mn = min(mn, total-it.second);
    }
    return mn;
}

long long interactionCosts(int n, vector<vector<int>>& edges, 
    vector<int>& group) {
    vector<vector<int>> adj(n, vector<int>());
    for(auto it: edges){
        int u = it[0];
        int v = it[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<string> number(n);
    queue<int> qu;
    qu.push(0);
    number[0] = "0";
    while(!qu.empty()){
        int node = qu.front();
        qu.pop();
        for(auto nbr: adj[node]){
            number[nbr] = number[node] + "_" + to_string(nbr);
            qu.push(nbr);
        }
    }
    unordered_map<int, vector<int>> grps;
    for(int i=0;i<group.size();i++){
        grps[group[i]].push_back(i);
    }
    int cost = 0;
    for(auto vec: grps){
        int l = vec.second.size();
        
        for(int i=0;i<l;i++){
            for(int j=i+1;j<l;j++){
                string s1 = number[i];
                string s2 = number[j];
                int p=0, q=0;
                while(p<s1.size() && q<s2.size()){
                    if(s1[p] != s2[q])
                        break;
                }
                cost += (s1.size() + s2.size() - 2*(p-1));
            }
        }
    }
    return cost;
}

string largestEven(string s) {
    while(s.size()>0 && s.back()=='1'){
        s.pop_back();
    }
    return s;
}

//[  t       l     r      b
//["able","area","echo","also"],
//["area","able","also","echo"]
//]
vector<vector<string>> wordSquares(vector<string>& words) {
    vector<vector<string>> ans;
    int n = words.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            for(int k=0;k<n;k++){
                if(k==i || k==j) continue;
                for(int l=0;l<n;l++){
                    if(l==k || l==j || l==i) continue;

                    string top = words[i];
                    string left = words[j];
                    string right = words[k];
                    string bottom = words[l];

                    if(top[0]==left[0] && top[3]==right[0] &&
                        left[3]==bottom[0] && bottom[3]==right[3]){
                            ans.push_back({top, left, right, bottom});
                        }

                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

long long minimumCost(string s, string t, int flipCost, int swapCost, int crossCost) {
    int n = s.size();
    long long A = 0, B = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] != t[i]) {
            if (s[i] == '0') A++;
            else B++;
        }
    }

    long long singleCost = min(flipCost, crossCost);
    long long cost = 0;

    if (swapCost < 2 * singleCost) {
        long long pairs = min(A, B);
        cost += pairs * swapCost;
        A -= pairs;
        B -= pairs;
    }

    cost += (A + B) * singleCost;
    return cost;
}

int absDifference(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int i=0, j=nums.size()-1, sum1=0, sum2=0;
    while(k>0){
        sum1 += nums[i];
        sum2 += nums[j];
        i++;
        j--;
        k--;
    }
    return abs(sum1-sum2);
}

bool isVowel(char ch){
    if(ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u'){
        return true;
    }
    return false;
}

string reverseWords(string s) {
    int n = s.length(), vowCount=0;
    int i=0;
    while(s[i]!=' '){
        if(isVowel(s[i])){
            vowCount++;
        }
        i++;
    }
    while(i < n){
        i++;
        int start = i;
        int count=0;
        while(s[i]!=' ' && i<n){
            if(isVowel(s[i])){
                count++;
            }
            i++;
        }
        if(count == vowCount){
            reverse(s.begin()+start, s.begin()+i);
        }
    }
    return s;
}

long long minMoves(vector<int>& balance) {
    int n = balance.size(), negIdx=-1;
    long long totSum = 0, ans = 0;
    priority_queue<int> pq;
    for(int i=0;i<n;i++){
        totSum += balance[i];
        if(balance[i]<0){
            negIdx = i;
        }
        else{
            pq.push(balance[i]);
        }
    }
    if(totSum < 0){
        return -1;
    }

    while (!pq.empty() && balance[negIdx]<0){
        if(abs(balance[negIdx] >= pq.top())){
            ans += pq.top();
            balance[negIdx] += pq.top();
        }
        else{
            ans += abs(balance[negIdx]);
            balance[negIdx] = 0;
        }
        pq.pop();
    }
    
    if(balance[negIdx] < 0) return -1;
    return ans;
}

bool hasMatch(string s, string p) {
    // if * is at 0
    if(p[0]=='*'){
        int i=0;

        while(s[i]!=p[1]){
            i++;
        }
        int j=1;
        while(i<s.length() && j<p.length() && s[i]==p[j]){
            i++;
            j++;
        }
        return j==p.length();
    }

    // if * is in mid somewhere
    else if(p[p.length()-1]=='*'){
        int i=0, j=0;
        while(i<s.length() && j<p.length() && s[i]!=p[j]){
            i++;
        }
        while(i<s.length() && j<p.length() && s[i]==p[j]){
            i++;
            j++;
        }
        return p[j]=='*';
    }

    
    // if * is at end
}

vector<int> twoSum(vector<int>& numbers, int target) {
    int n = numbers.size();
    int i=0, j=n-1;
    while (i < j){
        int sum = numbers[i] + numbers[j];
        if(sum == target){
            return {i+1, j+1};
        }
        else if(sum < target){
            i++;
        }
        else{
            j--;
        }
    }
    return {};
}

string minWindow(string s, string t) {
    vector<int> freq(128, 0);
    for(char c : t) freq[c]++;

    int required = t.size();
    int l = 0, minLen = INT_MAX, start = 0;

    for(int r = 0; r < s.size(); r++){
        if(freq[s[r]] > 0) required--;
        freq[s[r]]--;

        while(required == 0){
            if(r - l + 1 < minLen){
                minLen = r - l + 1;
                start = l;
            }
            freq[s[l]]++;
            if(freq[s[l]] > 0) required++;
            l++;
        }
    }
    return minLen == INT_MAX ? "" : s.substr(start, minLen);
}

vector<int> ansFunc(vector<int> state, vector<string> &ops){
    int n = state.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i=0;i<n;i++){
        if(state[i]==0){
            pq.push(i);
        }
    }
    for(auto op: ops){
        if(op == "L"){
            if(!pq.empty()){
                int idx = pq.top();
                pq.pop();
                state[idx] = 1;
            }
        }
        else{
            int idx = stoi(op.substr(1));
            state[idx] = 0;
            pq.push(idx);
        }
    }
    return state;
}

vector<int> rightSideView(TreeNode* root) {
    if(!root){
        return {};
    }
    queue<TreeNode*> qu;
    qu.push(root);
    vector<int> res;
    while(!qu.empty()){
        int qu_size = qu.size();
        while(qu_size>0){
            TreeNode* qfv = qu.front();
            qu.pop();
            if(qu_size == 1){
                res.push_back(qfv->val);
            }

            if(qfv->left){
                qu.push(qfv->left);
            }
            if(qfv->right){
                qu.push(qfv->right);
            }

            qu_size--;
        }
    }
    return res;
}

int minTime_hlpr(int node, vector<vector<int>> &adj, 
    vector<bool> &hasApple, vector<bool> &vis){
    vis[node] = 1;
    int time = 0;
    for(auto nbr: adj[node]){
        if(!vis[nbr]){
            time += minTime_hlpr(nbr, adj, hasApple, vis);
        }
    }
    if(time>0 || hasApple[node]){
        return time+2;
    }
    return time;
}

int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
    vector<vector<int>> adj(n);
    for(auto e: edges){
        int u = e[0];
        int v = e[1];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> vis(n, 0);
    int time = minTime_hlpr(0, adj, hasApple, vis)-2;
    return (time<0)?0:time;
}

int countHighestScoreNodes_dfs(int node, vector<vector<int>> &adj, vector<int> &weight){
    int sz = 1;
    for(auto nbr: adj[node]){
        sz += countHighestScoreNodes_dfs(nbr, adj, weight);
    }
    weight[node] = sz;
    return sz;
}

int countHighestScoreNodes(vector<int>& parents) {
    int n = parents.size();
    vector<vector<int>> adj(n);
    vector<int> weight(n);

    for(int i=1;i<n;i++){
        adj[parents[i]].push_back(i);
    }

    countHighestScoreNodes_dfs(0, adj, weight);
    long long maxScore = 0;
    int count = 0;

    for(int i=0;i<n;i++){
        int score = 1;
        int rest = n-weight[i];
        if(rest > 0){
            score *= rest;
        }
        for(int child: adj[i]){
            score *= weight[child];
        }
        if(score > maxScore){
            maxScore = score;
            count = 1;
        }
        else if(score == maxScore){
            count++;
        }
    }
    return maxScore;
}

int maxProduct_hlpr(int n, set<int> &tmpSet){
    int numBits = (int)log2(n) + 1; // number of bits in n

    for (int i = numBits-1; i >= 0; i--) {
        if (n & (1 << i)) { // if bit i is set
            int flipped = n ^ (1 << i); // flip this bit
            if(tmpSet.find(flipped) != tmpSet.end()){
                return flipped;
            }
        }
    }
    return 0;
}

long long maxProduct(vector<int>& nums) {
    set<int> tmpSet;
    for(int it: nums){
        tmpSet.insert(it);
    }

    long long maxP = INT_MIN;
    sort(nums.begin(), nums.end());
    reverse(nums.begin(), nums.end());
    for(int i=0;i<nums.size();i++){
        int xor_num = maxProduct_hlpr(nums[i], tmpSet);
        if(xor_num*nums[i] > maxP){
            maxP = xor_num*nums[i];
        }
    }
    return (maxP == INT_MIN) ? 0 : maxP;
}

void solve(){
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 4;
    int n = 5;
    int low=0, high=n-1;
    while(low <= high){
        int mid = low + (high-low)/2;
        if(nums[mid] == target){
            cout<<mid<<"\n";
            break;
        }
        // left half sorted
        if(nums[low] <= nums[mid]){
            if(nums[low]<=target && target<nums[mid]){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        // right half sorted
        else{
            if(nums[high]>=target && target>nums[mid]){
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }
    }
}

int first_occurence(vector<int> &nums, int trg){
    int n = nums.size();
    int low = 0, high = n-1;
    int ans = -1;

    while(low<=high){
        int mid = low + (high-low)/2;
        if(nums[mid]<trg){
            low = mid+1;
        }
        else if(nums[mid]>trg){
            high = mid-1;
        }
        else{
            ans = mid;
            high = mid-1;
        }
    }
    return ans;
}

int last_occurence(vector<int> &nums, int trg){
    int n = nums.size();
    int low = 0, high = n-1;
    int ans = -1;

    while(low<=high){
        int mid = low + (high-low)/2;
        if(nums[mid]<trg){
            low = mid+1;
        }
        else if(nums[mid]>trg){
            high = mid-1;
        }
        else{
            ans = mid;
            low = mid+1;
        }
    }
    return ans;
}

string amazonQues(string shipmentData){
    int n = shipmentData.size();

    int ones = count(shipmentData.begin(), shipmentData.end(), '1');

    vector<int> order;

    // odd positions from end
    for(int i = n - 1; i >= 0; i -= 2)
        order.push_back(i);

    // even positions
    int start = (n % 2 == 0) ? 0 : 1;
    for(int i = start; i < n; i += 2)
        order.push_back(i);

    vector<char> ans(n, '0');

    for(int i = 0; i < ones; i++)
        ans[order[i]] = '1';

    return string(ans.begin(), ans.end());
}

int main(){
    
    string ship = "1101";

    cout<<amazonQues(ship);

    return 0;
}