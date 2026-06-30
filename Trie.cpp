#include<bits/stdc++.h>
using namespace std;

class Node{
    unordered_map<char, Node*> mp;
    bool end;
public:
    Node(){
        end = false;
    }

    void insertFunc(string s) {
        int n = s.length();
        Node* curr = this;
        for (int i = 0; i < n; i++) {
            if (curr->mp.count(s[i])) {
                curr = curr->mp[s[i]];
            } else {
                curr->mp[s[i]] = new Node();
                curr = curr->mp[s[i]];
            }
            if (i == n - 1) {
                curr->end = true;  // mark the last node as end of word
            }
        }
    }

    bool searchWord(string s){
        int n = s.length();
        Node* curr = this;
        for (int i = 0; i < n; i++) {
            if (curr->mp.find(s[i]) == curr->mp.end()) {
                return false;  // character not found
            }
            curr = curr->mp[s[i]];
        }
        return curr->end;  // only true if it's a complete word
    }

};

class TrieNode{

    public:
    bool isEndofWord;
    vector<TrieNode*> nbr;
    unordered_map<string, int> langFreq;
    int wordCount;
    int prefixCount;

    TrieNode(){
        isEndofWord = 0;
        wordCount = 0;
        prefixCount = 0;
        nbr.resize(26, nullptr);
    }

    void insertFunc(string& word, string& lang){
        int n = word.length();
        TrieNode* curr = this;
        for(int i=0;i<n;i++){
            char ch = word[i];
            if(curr->nbr[ch-'a'] == nullptr){
                curr->nbr[ch-'a'] = new TrieNode();
            }
            curr = curr->nbr[ch-'a'];
            curr->prefixCount++;
        }
        curr->isEndofWord = 1;
        curr->langFreq[lang]++;
        curr->wordCount++;
    }

    bool search(string& word){
        int n = word.length();
        TrieNode* curr;
        curr = this;
        for(int i=0;i<n;i++){
            char ch = word[i];
            if(curr->nbr[ch-'a'] == nullptr){
                return false;
            }
            else{
                curr = curr->nbr[ch-'a'];
            }
        }
        return curr->isEndofWord;
    }

    TrieNode* findNode(string& word){
        TrieNode* curr = this;
        for(char ch: word){
            int idx = ch-'a';
            if(curr->nbr[idx] == nullptr)
                return nullptr;
            else{
                curr = curr->nbr[idx];
            }
        }
        return curr;
    }

    void dfs(TrieNode* node, vector<string> &ans, string &word){
        if(!node){
            return;
        }
        if(node->isEndofWord){
            ans.push_back(word);
        }
        for(int i=0;i<26;i++){
            if(node->nbr[i] != nullptr){
                word.push_back('a'+i);
                dfs(node->nbr[i], ans, word);
                word.pop_back();
            }
        }
    }

    vector<string> startsWith(string& word){
        TrieNode* node = findNode(word);
        if(!node){
            return {};
        }
        vector<string> ans;
        dfs(node, ans, word);
        return ans;
    }

    void deleteWord(string &word){
        // here we should invoke this func only if we know that the full word exist in Trie
        TrieNode* curr = this;
        for(auto ch: word){
            int idx = ch - 'a';
            curr = curr->nbr[idx];
            curr->prefixCount--;
        }
        curr->wordCount--;
        if(curr->wordCount == 0){
            curr->isEndofWord = 0;
        }
    }
};

class HitCounter{
    public:
    vector<int> freq;
    int lastTimeStamp;
    int count;

    HitCounter(int cap){
        freq.resize(cap+1, 0);
        count = 0;
    }

    void hit(int timeStamp){
        count++;
        freq[timeStamp] = count;
        lastTimeStamp = timeStamp;
    }

    int getHit(int timeStamp){
        cout<<freq[timeStamp]<<" - "<<freq[timeStamp-300]<<"\n";
        return (freq[timeStamp] - freq[timeStamp-300]);
    }
};

bool isValid(int x, int y, vector<vector<char>> &grid){
    if(x>=0 && x<grid.size() && y>=0 && y<grid[0].size() && grid[x][y]=='X'){
        return true;
    }
    return false;
}

void dfs(int r, int c, vector<vector<char>> &grid, vector<vector<int>> &owner, int count){
    if(!isValid(r, c, grid)){
        return;
    }
    owner[r][c] = count;
    dfs(r-1, c, grid, owner, count); // up
    dfs(r, c+1, grid, owner, count); // right
    dfs(r+1, c, grid, owner, count); // down
    dfs(r, c-1, grid, owner, count); // left
}

int minDistBwIslands(vector<vector<char>> &grid){
    int count = 0;
    int m = grid.size();
    int n = grid[0].size();
    using pii = pair<int, int>;
    queue<pii> qu;
    vector<vector<int>> owner(m, vector<int>(n, 0));
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

    // components marking...
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(owner[i][j] != 0){
                count++;
                dfs(i, j, grid, owner, count);
            }
        }
    }

    // component insertion
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j] != 'O'){
                qu.push({i, j});
                dist[i][j] = 0;
            }
        }
    } 
    int ans = INT_MAX;
    while(!qu.empty()){
        pii node = qu.front();
        qu.pop();
        int x = node.first;
        int y = node.second;
        vector<int> dx = {-1, 0, 1, 0};
        vector<int> dy = {0, 1, 0, -1};

        for(int i=0;i<4;i++){
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx>=0 && nx<grid.size() && ny>=0 && ny<grid[0].size()){
                if(owner[nx][ny] == 0){ // own the water cell
                    dist[nx][ny] = dist[x][y] + 1;
                    owner[nx][ny] = owner[x][y];
                    qu.push({nx, ny});
                }
                else if(owner[nx][ny] != owner[x][y]){ // candidate 
                    ans = min(ans, dist[nx][ny] + dist[x][y]);
                }
            }
        }
    }
    return ans;
}

int main(){
    // Node* Trie = new Node();
    // Trie->insertFunc("apple");
    // Trie->insertFunc("apps");
    // Trie->insertFunc("application");
    // Trie->insertFunc("oppo");

    // if(Trie->searchWord("app")){
    //     cout<<"Found\n";
    // }
    // else{
    //     cout<<"Not Found\n";
    // }

    HitCounter counter(1000);
    counter.hit(1);
    counter.hit(2);
    counter.hit(3);
    counter.hit(300);
    counter.hit(400);
    cout<<counter.getHit(300);
    
    return 0;
}