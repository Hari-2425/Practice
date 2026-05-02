#include <bits/stdc++.h>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


void dfs(TreeNode* root, int &len, int currLen){
    if(!root){
        len = max(len, currLen);
        return;
    }

    if(root->left){
        dfs(root->left, len, currLen+1);
    }
    if(root->right){
        dfs(root->right, len, currLen+1);
    }
}

int maxDepth(TreeNode* root) {
    if(!root) return 0;
    int ans = 1;
    dfs(root, ans, 1);
    return ans;
}

int ANS = 0;
int diameterOfBinaryTree_dfs(TreeNode* root){
    if(!root){
        return 0;
    }
    int leftAns = diameterOfBinaryTree_dfs(root->left);
    int rightAns = diameterOfBinaryTree_dfs(root->right);
    ANS = max(ANS, leftAns + rightAns);
    return 1 + max(leftAns, rightAns);
}

int diameterOfBinaryTree(TreeNode* root) {
    return diameterOfBinaryTree_dfs(root);
}

struct folder{
    string path;
    vector<folder*> children;
};

void removeSubfolders_dfs(){

}

bool checkFolder(string path, set<string> &paths){
    string tmp = "";
    for(int i=0;i<path.size();){
        while(path[i]!='/' && i<path.size()){
            tmp += path[i];
            i++;
        }
        if(paths.find(tmp) != paths.end()){
            return true;
        }
        i++;
    }
    return false;
}

vector<string> removeSubfolders(vector<string>& folder) {
    set<string> paths;
    for(int i=0;i<folder.size();i++){
        if(!checkFolder(folder[i], paths)){
            paths.insert(folder[i]);
        }
    }
    vector<string> ans;
    for(auto str: paths){
        ans.push_back(str);
    }
    return ans;
}

TreeNode* lowestCommonAncestor_hlpr(TreeNode* root, TreeNode* p, TreeNode* q){
    if(!root || root==p || root==q)
        return root;
    
    TreeNode* leftAns = lowestCommonAncestor_hlpr(root->left, p, q);
    TreeNode* rightAns = lowestCommonAncestor_hlpr(root->right, p, q);

    if(leftAns && rightAns){
        return root;
    }

    return leftAns ? leftAns : rightAns;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return lowestCommonAncestor_hlpr(root, p, q);
}

class TimeMap {
public:
    using pis = pair<int, string>;
    unordered_map<string, vector<pis>> tmap;
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        tmap[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if(!tmap.count(key)){
            return "";
        }
        vector<pis> nums = tmap[key];
        if(nums.size()!=0){
            int low=0, high=nums.size()-1;
            int ans = -1;
            while(low <= high){
                int mid = low + (high-low)/2;
                if(nums[mid].first == timestamp){
                    ans = mid;
                    low = mid+1;
                }
                else if(nums[mid].first < timestamp){
                    low = mid+1;
                }
                else{
                    high = mid-1;
                }
            }

            return (ans == -1) ? nums[low].second : nums[ans].second;
        }
        return "";
    }
};

vector<int> finalSellingPrice(vector<int> &prices){
    int n = prices.size();
    stack<int> stk;
    vector<int> ans(n);
    for(int i=n-1;i>=0;i--){
        while(!stk.empty() && prices[stk.top()]>prices[i]){
            stk.pop();
        }
        if(stk.empty()){
            ans[i] = prices[i];
        }
        else{
            ans[i] = prices[i] - prices[stk.top()];
        }
        stk.push(i);
    }
    return ans;
}

int findJudge(int n, vector<vector<int>>& trust) {
    vector<int> inDeg(n+1, 0), outDeg(n+1, 0);
    for(int i=0;i<trust.size();i++){
        int u = trust[i][0];
        int v = trust[i][1];
        inDeg[v]++;
        outDeg[u]++;
    }
    for(int i=1;i<=n;i++){
        if(inDeg[i]==n-1 && outDeg[i]==0){
            return i;
        }
    }
    return -1;
}



int maxAreaOfIsland_dfs(int x, int y, vector<vector<int>>& grid,
    vector<vector<bool>> &vis){
    if(x<0 || x>=grid.size() || y<0 || y>=grid[0].size() || grid[x][y]==0 || vis[x][y]){
        return 0;
    }
    vis[x][y] = 1;
    
    int area = 0;
    area += maxAreaOfIsland_dfs(x-1, y, grid, vis); // Top
    area += maxAreaOfIsland_dfs(x+1, y, grid, vis); // Bottom
    area += maxAreaOfIsland_dfs(x, y-1, grid, vis); // Left
    area += maxAreaOfIsland_dfs(x, y+1, grid, vis); // Right

    return 1 + area;
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    int maxArea = 0;
    vector<vector<bool>> vis(n, vector<bool>(m, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j]){
                int area = maxAreaOfIsland_dfs(i, j, grid, vis);
                maxArea = max(area, maxArea);
            }
        }
    }
    return maxArea;
}

int openLock(vector<string>& deadends, string target) {
    set<string> notAllowed;
    set<string> vis;
    for(string de: deadends){
        notAllowed.insert(de);
    }

    if(notAllowed.find("0000")!=notAllowed.end()){
        return -1;
    }
    using psi = pair<string, int>;

    queue<psi> qu;
    qu.push({"0000", 0});
    while(!qu.empty()){
        int qu_sz = qu.size();

        while(qu_sz--){
            psi node = qu.front();
            qu.pop();
            if(node.first == target){
                return node.second;
            }

            for(int i=0;i<4;i++){
                int dig = node.first[i]-'0';
                string inc = node.first;
                string dec = node.first;
                inc[i] = (dig+1+10)%10 + '0';
                dec[i] = (dig-1+10)%10 + '0';
                if(!vis.count(inc) && !notAllowed.count(inc)){
                    vis.insert(inc);
                    qu.push({inc, node.second+1});
                }
                if(!vis.count(dec) && !notAllowed.count(dec)){
                    vis.insert(dec);
                    qu.push({dec, node.second+1});
                }
            }
        }
    }
    return -1;
}

vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    vector<vector<bool>> reach(numCourses+1, vector<bool>(numCourses+1, 0));
    vector<int> inDeg(numCourses+1, 0);
    vector<vector<int>> adj(numCourses+1);
    for(auto preq: prerequisites){
        int u = preq[0];
        int v = preq[1];
        inDeg[v]++;
        adj[u].push_back(v);
    }
    queue<int> qu;
    for(int i=1;i<=numCourses;i++){
        if(inDeg[i]==0){
            qu.push(i);
        }
    }
    while(!qu.empty()){
        int node = qu.front();
        qu.pop();
        for(int nb: adj[node]){
            
        }
    }
}

int main(){
    vector<int> prices = {5, 1, 3};
    vector<int> ans = finalSellingPrice(prices);
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<", ";
    }

    return 0;
}