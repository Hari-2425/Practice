#include <bits/stdc++.h>
using namespace std;

void Display(vector<int> &vec){
    for(auto it: vec){
        cout<<it<<", ";
    }
    cout<<"\n";
}

void Displayll(vector<long long> &vec){
    for(auto it: vec){
        cout<<it<<", ";
    }
    cout<<"\n";
}

vector<int> findRequestTarget(const int n, const vector<int>& requests) {
    vector<int> assigned(n);
    unordered_map<int, int> next;
    vector<int> ret; ret.reserve(requests.size());
    for (const auto r : requests) {
        const int cnt = assigned[r], idx = next[cnt];
        ret.push_back(idx);
        assigned[idx]++;
        next[cnt]++;
    }
    return ret;
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

vector<int> solve_lexico_smallest_perm(int n, vector<int> &data){
    using vi = vector<int>;
    priority_queue<vi, vector<vi>, greater<vi>> pq;
    for(int i=0;i<data.size();i++){
        pq.push({data[i], i+1});
    }
    vector<int> ans;
    while(!pq.empty()){
        ans.push_back(pq.top()[1]);
        pq.pop();
    }
    return ans;
}

int solve_beautiful_painting(int k, int m, int n, vector<vector<int>> &paint) {
    vector<vector<int>> grid(m, vector<int>(n, 0));
    vector<vector<int>> cnt(m, vector<int>(n, 0));

    int painted = 0;

    for (int t = 0; t < paint.size(); t++) {
        int x = paint[t][0]-1;
        int y = paint[t][1]-1;

        // Mark cell as black
        grid[x][y] = 1;
        painted++;

        // Early pruning
        // if (painted < k * k) continue;

        // Update affected k×k windows
        for (int i = max(0, x - k + 1); i <= x && i + k <= m; i++) {
            for (int j = max(0, y - k + 1); j <= y && j + k <= n; j++) {
                cnt[i][j]++;
                if (cnt[i][j] == k * k) {
                    return t;  // earliest time
                }
            }
        }
    }
    return -1;
}

int totalStrength(vector<int>& s) {
    int n=s.size(), mod=1e9+7;

    //Use these 2 prefix sums A, B to find sum of sums for subarrays
    vector<long long> A(n+1, 0LL), B(n+1, 0LL);
    for(int i=0; i<n; i++){
        A[i+1]=(A[i]+s[i])%mod;
        B[i+1]=(B[i]+A[i+1])%mod;
    }
    

    vector<int> stack;
    long long ans=0;
    // 2, 3, 2, 1
    for(int r=0; r<=n; r++){
        //monotonic increasing stack storing the index
        while(!stack.empty() && (r==n||s[r]<=s[stack.back()]))
        {
            int m=stack.back();
            stack.pop_back();
            int l=stack.empty()?-1:stack.back();
            
            long long sum =(2*mod+(m-l)*(B[r]-B[m])%mod-(r-m)*(B[m]-B[max(l, 0)])%mod);
            ans = (ans+sum*s[m]) % mod;
        }
        stack.push_back(r);
    }
    return ans;
}

int NoOfWays(string s, int k){
    int n=s.length(), l=0,r=k-1, ans=0;

    while(r<n){
        if(s[r]<s[l]){
            ans++;
        }
        else if(s[r]==s[l]){
            int i=l, j=r;
            while(s[i] == s[j]){
                i++;
                j--;
            }
            if(i < j){
                ans++;
            }
        }
        l++;
        r++;
    }
    return ans;
}

vector<int> next_greater(vector<int> &nums){
    int n = nums.size();
    stack<int> st;
    vector<int> res(n, -1);
    for(int i=n-1;i>=0;i--){
        while(!st.empty() && nums[st.top()]<=nums[i]){
            st.pop();
        }
        if(!st.empty()){
            res[i] = st.top();
        }
        st.push(i);
    }
    return res;
}

int max_cost_hlpr(int i, int m, vector<int> &a, vector<int> &b, 
    map<tuple<int, int>, int> &dp, vector<int> &j_value){
    if(i==a.size() || m==0)
        return 0;
    if(dp.find({i, m}) != dp.end()){
        return dp[{i, m}];
    }
    
    // take
    int take = a[i] + ((j_value[i]-1)*b[i]) + max_cost_hlpr(i, m-1, a, b, dp, j_value);

    // not take
    int notTake = max_cost_hlpr(i+1, m, a, b, dp, j_value);

    return dp[{i, m}] = max(take, notTake);
    
}

int min_cost(vector<int> &a, vector<int> &b, int m){
    int n = a.size();
    vector<int> j_val(n, 0);
    using tiiii = tuple<int, int, int, int>;
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for(int i=0;i<n;i++){
        pq.push({a[i], 1, a[i], b[i]});
    }
    int ans = 0;
    while(m--){
        vector<int> tp = pq.top();
        pq.pop();
        ans += tp[0];
        tp[1]++;
        int cost = tp[2] + (tp[1]-1)*tp[3];
        tp[0] = cost;
        pq.push(tp);
    }
    return ans;
}

int getMaxTotalArea(vector<int>& sideLengths) {
    unordered_map<int, int> freq;
    long long MOD = 1e9 + 7;
    for (int x : sideLengths) {
        freq[x]++;
    }

    vector<int> sides;

    // Max possible stick length is 10^4
    for (int x = 10000; x >= 1; x--) {
        if (freq[x] >= 2) {
            int pairs = freq[x] / 2;
            for (int i = 0; i < pairs; i++) {
                sides.push_back(x);
            }
            freq[x] %= 2;
        }

        // Move leftover stick to x-1 (reduce by 1)
        if (freq[x] == 1 && x > 1) {
            freq[x - 1]++;
        }
    }
    Display(sides);
    // Form rectangles from largest sides
    long long ans = 0;
    for (int i = 0; i + 1 < sides.size(); i += 2) {
        ans = (ans + 1LL * sides[i] * sides[i + 1]) % MOD;
    }

    return (int)ans;
}

int remove_max_char(string s){
    int n = s.length();
    if(n==0 || n==1) 
        return 0;
    char first=s[0], last=s.back();
    if(first == last) 
        return n-1;
    
    int ans = 0;

    for(int i=1;i<n-1;i++){
        if(s[i]==last){
            ans = max(ans, n-1-i);
        }
        else if(s[i]==first){
            ans = max(ans, i);
        }
    }
    return ans;
}

int maxPackages(vector<int>& itemCost) {
    int n = itemCost.size();
    sort(itemCost.begin(), itemCost.end());

    long long totalSum = 0;
    for (int x : itemCost) totalSum += x;

    int maxVal = itemCost.back();
    int ans = 1; // at least 1 package always possible

    // Try all possible target sums
    for (long long S = maxVal; S <= totalSum; S++) {
        if (totalSum % S != 0) continue;

        int packages = totalSum / S;
        int l = 0, r = n - 1;
        bool ok = true;

        while (l <= r) {
            if (itemCost[r] > S) {
                ok = false;
                break;
            }

            if (itemCost[r] == S) {
                r--;
            } else {
                if (itemCost[l] + itemCost[r] == S) {
                    l++; r--;
                } else if (itemCost[l] + itemCost[r] < S) {
                    l++;
                } else {
                    ok = false;
                    break;
                }
            }
        }

        if (ok)
            ans = max(ans, packages);
    }

    return ans;
}


int main(){
    
    // string s = "amazon";
    // cout<<NoOfWays(s, 3);

    // vector<int> sideLen = {2, 3, 3, 4, 6, 6, 8, 8};
    // cout<<getMaxTotalArea(sideLen);

    vector<int> arr = {1,2,3,4,5};
    cout<<maxPackages(arr);

    return 0;
}