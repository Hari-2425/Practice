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

    int countNegatives(vector<vector<int>>& grid) {
        // [ 4, 3, 2,-1]
        // [ 3, 2, 1,-1]
        // [ 1, 1,-1,-2]
        // [-1,-1,-2,-3]
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
int main(){
    
    string s = "abvi";
    cout<<s.substr(0, 2)<<"\n";
    int x;
    cin>>x;
    
}