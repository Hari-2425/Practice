#include<bits/stdc++.h>
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
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word = false;
    ~TrieNode() {
        for (auto &p : children) delete p.second;
    }
};

struct Trie {
    TrieNode* root;
    Trie() : root(new TrieNode()) {}
    ~Trie() { delete root; }

    void insert(const string &word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) node->children[ch] = new TrieNode();
            node = node->children[ch];
        }
        node->is_end_of_word = true;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty() || board[0].empty() || words.empty()) return {};

        Trie trie;
        for (auto &w : words) trie.insert(w);

        int rows = (int)board.size();
        int cols = (int)board[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        unordered_set<string> result_set;
        string path;
        path.reserve(32);

        function<void(int,int,TrieNode*)> backtrack = [&](int r, int c, TrieNode* node) {
            if (node->is_end_of_word) {
                result_set.insert(path);
                node->is_end_of_word = false; 
            }

            visited[r][c] = true;
            static const int DIRS[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
            for (auto &d : DIRS) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                if (visited[nr][nc]) continue;
                char next_char = board[nr][nc];
                auto it = node->children.find(next_char);
                if (it != node->children.end()) {
                    path.push_back(next_char);
                    backtrack(nr, nc, it->second);
                    path.pop_back();
                }
            }
            visited[r][c] = false;
        };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char start = board[r][c];
                auto it = trie.root->children.find(start);
                if (it != trie.root->children.end()) {
                    path.clear();
                    path.push_back(start);
                    backtrack(r, c, it->second);
                }
            }
        }
        vector<string> result(result_set.begin(), result_set.end());
        return result;
    }
};

TreeNode* flatten_hlpr(TreeNode* root){
    if(root == nullptr){
        return root;
    }
    TreeNode* res = new TreeNode(root->val);
    if(root->left){
        res->right = flatten_hlpr(root->left);
    }
    TreeNode* curr = res;
    while(curr->right != nullptr){
        curr = curr->right;
    }
    if(root->right){
        curr->right = flatten_hlpr(root->right);
    }
    return res;
}

void flatten(TreeNode* root) {
    
}

Node* connect(Node* root) {
    if(!root) return nullptr;
    queue<Node*> qu;
    qu.push(root);
    while(!qu.empty()){
        int qu_size = qu.size();
        while(qu_size>0){
            Node* node = qu.front();
            qu.pop();
            if(qu_size>1){
                node->next = qu.front();
            }
            if(node->left){
                qu.push(node->left);
            }
            if(node->right){
                qu.push(node->right);
            }
            qu_size--;
        }
    }
    return root;
}
int total;
void sumNumbers_hlpr(TreeNode* root, int sum){
    if(!root){
        return;
    }
    if(root->left==nullptr && root->right==nullptr){
        total += sum*10+root->val;
        return;
    }
    sumNumbers_hlpr(root->left, sum*10+root->val);
    sumNumbers_hlpr(root->right, sum*10+root->val);

}

int sumNumbers(TreeNode* root) {
    if(!root) return 0;
    total = 0;
    sumNumbers_hlpr(root, 0);
    return total;
}
int maxPathSum_val = INT_MAX;
int maxPathSum_hlpr(TreeNode* root){
    if(!root)
        return 0;
    int leftSum = maxPathSum_hlpr(root->left);
    int rightSum = maxPathSum_hlpr(root->right);

    maxPathSum_val = max(maxPathSum_val, root->val+leftSum+rightSum);
    return max(leftSum, rightSum) + root->val;
}

int maxPathSum(TreeNode* root) {
    if(!root) return 0;
    maxPathSum_hlpr(root);
    return maxPathSum_val;
}

int main(){
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };

    vector<string> words = {"oath","pea","eat","rain"};
    // vector<string> found = findWords(board, words);
    // for(auto w: found){
    //     cout<<w<<"\n";
    // }
    return 0;
}