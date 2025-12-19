#include <bits/stdc++.h>
using namespace std;

vector<int> Solve(vector<int> &arr, int target){

    int n = arr.size();
    unordered_map<int, int> h_map;
    int sum = 0;
    vector<int> ans = {-1, -1};
    sort(arr.begin(), arr.end());
    int l=0, r=n-1;
    while (l < r)
    {
        if(arr[l] + arr[r] < target){
            if(arr[l]+arr[r] > sum){
                sum = arr[l] + arr[r];
                ans[0] = l;
                ans[1] = r;
            }
            l++;
        }
        else{
            r--;
        }
    }
    return ans;
}

bool Check(vector<int> &arr, int d, int m, int n){
    int count = 1, last= 0;
    for(int i=1;i<n;i++){
        if(arr[i]-arr[last] <= d){
            count++;
            last = i;
        }
        if(count == m) return true;
    }
    return false;
}

int magneticForce(vector<int> &arr, int m){
    int n = arr.size();
    int l =  1;
    int r = arr[n-1]-arr[0];
    int ans = INT_MIN;
    while(l <= r){
        int d = l + (r-l)/2;
        bool isOk = Check(arr, d, m, n);
        if(isOk){
            ans = max(ans, d);
            l = d+1;
        }
        else{
            r = d-1;
        }
    }
    return ans;
}

int DFS(int node, vector<vector<int>> &adj, vector<bool> &vis){
    vis[node] = 1;
    int count = 1;
    for(auto nbr: adj[node]){
        if(!vis[nbr]){
            count += DFS(nbr, adj, vis);
        }
    }
    return count;
}

int SolveBombQues(vector<vector<int>>& bombs){
    int n = bombs.size();
    vector<vector<int>> adj(n);
    for(int i=0;i<n;i++){
        int x1=bombs[i][0], y1=bombs[i][1], r1=bombs[i][2];
        for(int j=0;j<n;j++){
            if(i == j) continue;
            int x2=bombs[j][0], y2=bombs[j][1], r2=bombs[j][2];
            int X = abs(x1-x2), Y=abs(y1-y2);
            if(X*X + Y*Y <= r1*r1){
                adj[i].push_back(j);
            }
        }
    }
    int max_count = INT_MIN, ans = -1;
    for(int i=0;i<n;i++){
        vector<bool> vis(n, 0);
        int curr = DFS(i, adj, vis);
        if(curr > max_count){
            max_count = curr;
            ans = i;
        }
    }
    return ans;
}

int MaxKModifications(string s, int k){
    int n = s.size();
    int l=0, r=0, maxFreq=0, ans=0;
    vector<int> freq(26, 0);
    for(;r<n;r++){
        freq[s[r]-'a']++;
        maxFreq = max(maxFreq, freq[s[r]-'a']);
        while(r-l+1 - maxFreq > k){
            freq[s[l]-'a']--;
            l++;
        }
        ans = max(ans, r-l+1);
    }
    return ans;
}

void MakeRowCol0(vector<vector<int>> &matrix){
    int n = matrix.size(), m = matrix[0].size();
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int val = matrix[i][j];
            if(val==0){
                for(int k=0;k<n;k++){
                    if(matrix[k][j]!=0 && matrix[k][j]!=-1){
                        matrix[k][j] = -1;
                    }
                }
                for(int k=0;k<n;k++){
                    if(matrix[i][k]!=0 && matrix[i][k]!=-1){
                        matrix[i][k] = -1;
                    }
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(matrix[i][j]==-1){
                matrix[i][j] = 0;
            }
        }
    }
}

class MinStack{
    public:
    stack<int> orgStack, minStack;
    MinStack() {
    }
    
    void push(int val) {
        orgStack.push(val);
        if(!minStack.empty()){
            if(val < minStack.top()){
                minStack.push(val);
            }
            else{
                minStack.push(minStack.top());
            }
        }
        else{
            minStack.push(val);
        }
    }

    void pop() {
        orgStack.pop();
        minStack.pop();
    }
    
    int top() {
        return orgStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    stack<int> store; // stores index valuse
    vector<int> res(n, 0);
    for(int i=n-1;i>=0;i--){
        while(!store.empty() && temperatures[i]>temperatures[store.top()]){
            store.pop();
        }
        if(!store.empty()){
            res[i] = store.top()-i;
            
        }
        store.push(i);
    }
    return res;
}

int carFleet(int target, vector<int>& position, vector<int>& speed) {
    vector<vector<int>> ps;
    for(int i=0;i<position.size();i++){
        ps.push_back({position[i], speed[i]});
    }
    sort(ps.begin(), ps.end());
    stack<double> timeStore;
    for(int i=ps.size()-1;i>=0;i--){
        double time = (double)(target-ps[i][0])/(double)(ps[i][1]);
        if((!timeStore.empty() && time>timeStore.top()) || timeStore.empty()){
            timeStore.push(time);
        }
    }
    return timeStore.size();
}

int toInt(string s){
    int ans = 0;
    for(int i=s.length()-1;i>=0;i--){
        if(s[i] == '-'){
            return -ans;
        }
        int dig = s[i]-'0';
        ans = ans*10 + dig;
    }
    return ans;
}

int evalRPN(vector<string>& tokens) {
    int n = tokens.size();
    stack<int> store;
    for(int i=0;i<n;i++){
        if(tokens[i] == "+"){
            int val1 = store.top();
            store.pop();
            int val2 = store.top();
            store.pop();
            store.push(val1 + val2);
        }
        else if(tokens[i] == "-"){
            int val1 = store.top();
            store.pop();
            int val2 = store.top();
            store.pop();
            store.push(val2 - val1);
        }
        else if(tokens[i] == "*"){
            int val1 = store.top();
            store.pop();
            int val2 = store.top();
            store.pop();
            store.push(val1 * val2);
        }
        else if(tokens[i] == "/"){
            int val1 = store.top();
            store.pop();
            int val2 = store.top();
            store.pop();
            store.push(val2 / val1);
        }
        else{
            int val = toInt(tokens[i]);
            store.push(val);
        }
    }
    return store.top();
}

int characterReplacement(string s, int k) {
    vector<int> freq(26, 0);
    int n = s.length(), mostFreq = 0;
    int start=0, end=0, ans=0;
    for(;end<n;end++){
        freq[s[end]-'A']++;
        mostFreq = max(mostFreq, freq[s[end]-'A']);
        while(end-start+1-mostFreq > k){
            freq[s[start]-'A']--;
            start++;
        }
        ans = max(ans, end-start+1);
    }   
    return ans;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<int> rightSideView(TreeNode* root) {
    vector<int> res;
    if(root == nullptr) return res;
    queue<TreeNode*> qu;
    qu.push(root);
    while(!qu.empty()){
        int qu_size = qu.size();
        while(qu_size>0){
            TreeNode* node = qu.front();
            qu.pop();
            if(qu_size==1){
                res.push_back(node->val);
            }
            if(node->left != nullptr){
                qu.push(node->left);
            }
            if(node->right != nullptr){
                qu.push(node->right);
            }
        }
    }
    return res;
}

int kthSmallest(TreeNode* root, int k) {
    
}

int main(){

    vector<int> arr = {1,0,4,0,5,6};
    vector<int> res = Solve(arr, 10);

    for(int i=0;i<res.size();i++){
        cout<<res[i]<<", ";
    }
    
    return 0;
}