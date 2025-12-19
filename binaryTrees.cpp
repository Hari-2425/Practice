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

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

vector<int> rightSideView(TreeNode* root) {

    // Approach: 
    // 1. BFS lagana hai, level wise

    vector<int> res;
    if(root == nullptr) return res;
    queue<TreeNode*> qu;
    qu.push(root);
    while(!qu.empty()){
        int qu_size = qu.size();
        // har ek level pe queue ke last element ki value ko result mei
        // store krna hai.
        // hum queue k size ko save kr ke while loop laga sakte hai, aur
        // jab bhi last element aayega usko save kr lenge.
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
            qu_size--;
        }
    }
    return res;
}

int visitCount = 0;
int ans = -1;

void hlpr(TreeNode* root, int k){
    if(!root || visitCount>=k){
        return;
    }
    hlpr(root->left, k);
    visitCount++;
    if(visitCount == k){
        ans = root->val;
        return;
    }
    hlpr(root->right, k);
}

int kthSmallest(TreeNode* root, int k) {
    hlpr(root, k);
    return ans;
}

bool isValidBST_hlpr(TreeNode* root, int left_max, int right_min){
    if(!root) return;
    if(root->val <= left_max || root->val >= right_min) return false;
    bool is_left_fine = isValidBST_hlpr(root->left, left_max, root->val);
    bool is_right_fine = isValidBST_hlpr(root->right, root->val, right_min);
    return is_left_fine && is_right_fine;
}

bool isValidBST(TreeNode* root) {

    // Approach:
    // Use BFS
    // queue ek object push krna hai, Object mei 3 values hongi:
    // first - current node
    // second - left min
    // third - right max


    // using pii = pair<int, int>;
    // if(!root) return true;
    // queue<pair<TreeNode*, pii>> qu;
    // qu.push({root, {INT_MIN, INT_MAX}});
    // while(!qu.empty()){

    //     auto node = qu.front();
    //     qu.pop();
    //     int left_val = node.second.first;
    //     int right_val = node.second.second;

    //     if(node.first->val<=left_val || node.first->val>=right_val)
    //         return false;
        
    //     if(node.first->left != nullptr){
    //         qu.push({node.first->left, {left_val, node.first->val}});
    //     }

    //     if(node.first->right != nullptr){
    //         qu.push({node.first->right, {node.first->val, right_val}});
    //     }

    // }

    // return true;
    int left = INT_MIN, right = INT_MAX;
    return isValidBST_hlpr(root, left, right);
}

int goodNodes_hlpr(TreeNode* root, int max_node){
    if(!root) return 0;
    int count = 0;
    if(root->val > max_node){
        count++;
        max_node = root->val;
    }
    count += goodNodes_hlpr(root->left, max_node);
    count += goodNodes_hlpr(root->right, max_node);
    return count;
}

int goodNodes(TreeNode* root) {
    return 1 + goodNodes_hlpr(root, root->val);
}

vector<int> topKFrequent(vector<int>& nums, int k) {
    using pii = pair<int, int>;
    int n = nums.size();
    // unordered_map<int, int> freq;
    vector<int> freq(2001, 0);
    for(int i=0;i<n;i++){
        freq[nums[i]+1000]++;
    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for(int i=0;i<2001;i++){
        pq.push({freq[i], i-1000});
        if(pq.size() > k){
            pq.pop();
        }
    }
    vector<int> ans;
    while(!pq.empty()){
        ans.push_back(pq.top().second);
        pq.pop();
    }
    return ans;
}

bool isValidSudoku(vector<vector<char>>& board) {
    int n = board.size();
    
    for(int row=0;row<n;row++){
        unordered_set<char> us;
        for(int i=0;i<n;i++){
            if(board[row][i] == '.')
                continue;
            if(us.find(board[row][i]) != us.end()){
                return false;
            }
            us.insert(board[row][i]);
        }
    }

    for(int col=0;col<n;col++){
        unordered_set<char> us;
        for(int i=0;i<n;i++){
            if(board[i][col] == '.')
                continue;
            if(us.find(board[i][col]) != us.end()){
                return false;
            }
            us.insert(board[i][col]);
        }
    }
    using pii = pair<int, int>;
    unordered_map<string, unordered_set<char>> store;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(board[i][j] == '.')
                continue;
            string key = to_string(i/3) + to_string(j/3);
            if(store[key].find(board[i][j]) != store[key].end()){
                return false;
            }
            store[key].insert(board[i][j]);
        }
    }
    return true;
}

bool isSubtree_hlpr(TreeNode* root, TreeNode* subRoot){
    if(root==nullptr && subRoot==nullptr)
        return true;
    if(root && subRoot && root->val==subRoot->val){
        return isSubtree_hlpr(root->left, subRoot->left) &&
        isSubtree_hlpr(root->right, subRoot->right);
    }
    return false;
}

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if(!subRoot)
        return true;
    if(!root)
        return false;
    return isSubtree_hlpr(root, subRoot) ||
            isSubtree(root->left, subRoot) ||
            isSubtree(root->right, subRoot);
    
}

Node* clone(Node* node, unordered_map<Node*, Node*> &oldToNew){
    if(!node) return nullptr;
    if(oldToNew.count(node)){
        return oldToNew[node];
    }
    Node* node_copy = new Node(node->val);
    oldToNew[node] = node_copy;
    for(auto nbr: node->neighbors){
        node_copy->neighbors.push_back(clone(nbr, oldToNew));
    }
    return node_copy;
}

Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> oldToNew;
    return clone(node, oldToNew);
}

int nain(){
    vector<int> arr = {1,2,2,3,3,3};
    vector<int> ans = topKFrequent(arr, 2);

    for(auto it: ans){
        cout<<it<<", ";
    }

    return 0;
}