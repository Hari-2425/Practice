#ifdef __has_include
  #if __has_include(<bits/stdc++.h>)
    #include <bits/stdc++.h>
  #else
    #include <iostream>
    #include <vector>
    #include <string>
    #include <algorithm>
    #include <map>
    #include <unordered_map>
    #include <set>
    #include <unordered_set>
    #include <queue>
    #include <stack>
    #include <utility>
    #include <limits>
    #include <memory>
    #include <sstream>
    #include <cmath>
    #include <iomanip>
    #include <functional>
    #include <tuple>
    #include <bitset>
    #include <chrono>
    #include <cassert>
  #endif
#else
  #include <bits/stdc++.h>
#endif

using namespace std;

using ll = long long;
using pii = pair<int, int>;

class Graph{
    unordered_map<int, vector<int>> graph;
    int n, m;

public:
    Graph(int n, int m, vector<vector<int>> edges){
        this->n = n;
        this->m = m;
        for(int i=0;i<m;++i){
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }
    }
    
    // DFS (recursive) for cycle detection in an undirected graph.
    // Purpose:
    //  - Traverse the graph from `node` and detect any back-edge that indicates a cycle.
    // Parameters:
    //  - node : current vertex being visited.
    //  - par  : parent vertex in DFS tree (used to ignore the trivial edge back to parent).
    //  - vis  : visitation vector marking visited nodes (0/1).
    // Logic:
    //  - Mark current node visited.
    //  - For each neighbor:
    //      * If unvisited, recurse. If recursion finds a cycle -> propagate true.
    //      * If visited and not the parent, we've found a cycle in an undirected graph.
    // Complexity:
    //  - Time: O(V + E) where V = number of vertices, E = number of edges.
    //  - Space: O(V) for visitation array + recursion depth up to O(V).
    bool dfs(int node, int par, vector<int> &vis){
        vis[node] = true;
        for(auto nbr: graph[node]){
            if(!vis[nbr]){
                if(dfs(nbr, node, vis)){
                    return true;
                }
            }
            else if(nbr != par){
                // cycle detected
                return true;
            }
        }
        return false;
    }

    // Check graph for cycles (undirected):
    // Notes:
    //  - If the graph is connected, starting DFS from a single node (e.g., 1) suffices.
    //  - For general graphs that may be disconnected, iterate over all nodes and run DFS
    //    from each unvisited node to ensure all components are checked.
    // Returns true if any component contains a cycle.
    bool hasCycleUnDirectedGraph(){
        vector<int> vis(n+1, 0);
        // connected graph
        return dfs(1, -1, vis);
    }

    // BFS (iterative) cycle detection for undirected graphs.
    // Notes:
    //  - Uses parent[] to ignore the trivial edge back to the parent.
    //  - Iterates all components to handle disconnected graphs.
    bool hasCycleUnDirectedBFS(){
        vector<int> vis(n+1, 0), parent(n+1, -1);
        for(int s = 1; s <= n; ++s){
            if(vis[s]) continue;
            queue<int> q;
            vis[s] = 1;
            parent[s] = -1;
            q.push(s);
            while(!q.empty()){
                int u = q.front(); q.pop();
                for(int v : graph[u]){
                    if(!vis[v]){
                        vis[v] = 1;
                        parent[v] = u;
                        q.push(v);
                    } else if(parent[u] != v){
                        // visited and not parent -> cycle
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class DirectedGraph{
    unordered_map<int, vector<int>> graph;
    int n, m;

public:
    DirectedGraph(int n, int m, const vector<vector<int>> &edges){
        this->n = n;
        this->m = m;
        for(int i = 0; i < m; ++i){
            // directed edge from u -> v
            int u = edges[i][0];
            int v = edges[i][1];
            graph[u].push_back(v);
        }
    }

    // DFS with recursion stack to detect cycles in a directed graph.
    // vis: marks visited nodes, rec: marks nodes in current recursion stack.
    bool dfsDirected(int node, vector<int> &vis, vector<int> &rec){
        vis[node] = 1;
        rec[node] = 1;
        for(auto nbr : graph[node]){
            if(!vis[nbr]){
                if(dfsDirected(nbr, vis, rec)) return true;
            }
            else if(rec[nbr]){
                // back-edge to an ancestor in recursion stack -> cycle
                return true;
            }
        }
        rec[node] = 0;
        return false;
    }

    // Check for cycles in the directed graph across all components.
    bool hasCycleDirectedGraph(){
        vector<int> vis(n+1, 0), rec(n+1, 0);
        for(int i = 1; i <= n; ++i){
            if(!vis[i]){
                if(dfsDirected(i, vis, rec)) return true;
            }
        }
        return false;
    }

    // Kahn's algorithm (BFS / topological sort) to detect cycle in directed graph.
    // Notes:
    //  - Build indegree[], push nodes with indegree 0, process.
    //  - If processed count != n -> cycle exists.
    bool hasCycleKahn(){
        vector<int> indeg(n+1, 0);
        for(const auto &p : graph){
            for(int v : p.second) ++indeg[v];
        }
        queue<int> q;
        for(int i = 1; i <= n; ++i) if(indeg[i] == 0) q.push(i);
        int cnt = 0;
        while(!q.empty()){
            int u = q.front(); q.pop();
            ++cnt;
            for(int v : graph[u]){
                if(--indeg[v] == 0) q.push(v);
            }
        }
        return cnt != n; // true if cycle detected
    }
};

vector<int> dx = {0, -1, 0, 1};
vector<int> dy = {-1, 0, 1, 0};

bool check(int x, int y, int m, int n, vector<vector<int>> &matrix, int old_color){
    return (x>=0 && x<m && y>=0 && y<n && matrix[x][y]==old_color);
}

void dfsHlpr(int i, int j, vector<vector<int>> &matrix, vector<vector<bool>> &vis, int old_color, int new_color){
    vis[i][j] = 1;
    matrix[i][j] = new_color;
    for(int k=0;k<4;k++){
        int nx = dx[k] + i;
        int ny = dy[k] + j;
        if(check(nx, ny, matrix.size(), matrix[0].size(), matrix, old_color) && !vis[nx][ny]){
            dfsHlpr(nx, ny, matrix, vis, old_color, new_color);
        }
    }
}

void FloodFill(vector<vector<int>> &matrix, int x, int y, int new_color){
    int m=matrix.size(), n=matrix[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, 0));
    dfsHlpr(x, y, matrix, vis, matrix[x][y], new_color);
}


bool isValid(int x, int y, int m, int n){
    return (x>=0 && x<m && y>=0 && y<n);
}

int orangesRotting(vector<vector<int>>& grid) {
    int m=grid.size(), n=grid[0].size(), fresh=0;
    queue<pair<int, int>> qu;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(grid[i][j]==2){
                qu.push({i, j});
            }
            else if(grid[i][j]==1){
                fresh++;
            }
        }
    }
    if(fresh == 0) return 0;
    int time = -1;
    while(!qu.empty()){
        time++;
        int sz = qu.size();
        while(sz--){
            int x = qu.front().first;
            int y = qu.front().second;
            qu.pop();
            for(int k=0;k<4;k++){
                int nx = x + dx[k];
                int ny = y + dy[k];
                if(isValid(nx, ny, m, n) && grid[nx][ny]==1){
                    grid[nx][ny] = 2;
                    fresh--;
                    qu.push({nx, ny});
                }
            }
        }
    }
    return fresh==0 ? time : -1;
}

void countBattleships_dfs(int i, int j, vector<vector<char>> &board, vector<vector<bool>> &vis, int m, int n){
    vis[i][j] = true;
    for(int k=0;k<4;k++){
        int nx = i + dx[k];
        int ny = j + dy[k];
        if(isValid(nx, ny, m, n) && !vis[nx][ny] && board[nx][ny]=='X'){
            countBattleships_dfs(nx, ny, board, vis, m, n);
        }
    }
}

int countBattleships(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    int ans = 0;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            if(!vis[i][j] && board[i][j]=='X'){
                countBattleships_dfs(i, j, board, vis, m, n);
                ans++;
            }
        }
    }
    return ans;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size(), zeroes=0;
    vector<vector<int>> ans(m, vector<int>(n, -1));
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    queue<pair<int, int>> qu;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(mat[i][j] == 0){
                qu.push({i, j});
                vis[i][j] = 1;
                zeroes++;
            }
        }
    }
    if(zeroes == 0){
        return mat;
    }
    int d = -1;
    while(!qu.empty()){
        d += 1;
        int sz = qu.size();
        while(sz--){
            int u = qu.front().first;
            int v = qu.front().second;
            if(mat[u][v] == 1){
                mat[u][v] = d;
            }
            qu.pop();

            for(int k=0;k<4;k++){
                int nu = u + dx[k];
                int nv = v + dy[k];
                if(isValid(nu, nv, m, n) && !vis[nu][nv]){
                    qu.push({nu, nv});
                    vis[nu][nv] = 1;
                }
            }
        }
    }
    return mat;
}

void count_distinct_islands_dfs(int i, int j, vector<vector<int>> &grid, 
    vector<vector<bool>> &vis, string &vec, int row0, int col0){
        vis[i][j] = 1;
        string tmp = to_string(i-row0) + "," + to_string(j-col0) + ";";
        vec += tmp;
        vector<int> dx = {1, 0, -1, 0};
        vector<int> dy = {0, 1, 0, -1};

        for(int k=0;k<4;k++){
            int nx = i + dx[k];
            int ny = j + dy[k];

            if(nx>=0 && nx<grid.size() && ny>=0 && ny<grid[0].size() && !vis[nx][ny] && grid[nx][ny]==1){
                count_distinct_islands_dfs(nx, ny, grid, vis, vec, row0, col0);
            }
        }
}

int count_distinct_islands(vector<vector<int>> &grid){
    int m=grid.size(), n=grid[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    set<string> st;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(!vis[i][j] && grid[i][j]==1){
                
                string vec = ""; 
                // Make call to DFS
                count_distinct_islands_dfs(i, j, grid, vis, vec, i, j);
                st.insert(vec);
            }
        }
    }
    return st.size();
}

bool IsBipartite_bfs(vector<vector<int>> &graph, int n){
    unordered_map<int, vector<int>> adj;
    for(auto vec: graph){
        adj[vec[0]].push_back(vec[1]);
        adj[vec[1]].push_back(vec[0]);
    }
    vector<int> clr(n+1, -1);
    queue<int> qu;
    qu.push(1);
    clr[1] = 0;
    while(!qu.empty()){
        int node = qu.front();
        qu.pop();
        for(int nbr: adj[node]){
            if(clr[nbr] == -1){
                clr[nbr] = 1 - clr[node];
                qu.push(nbr);
            }
            else if(clr[nbr] == clr[node]){
                return false;
            }
        }
    }
    return true;
}

bool ISBipartite_dfs(vector<vector<int>> &edges, int n){
    // It is assumed that the edges given are of connected graph.
    // There is only 1 component.
    unordered_map<int, vector<int>> adj;
    for(auto x: edges){
        adj[x[0]].push_back(x[1]);
        adj[x[1]].push_back(x[0]);
    }
    vector<int> color(n+1, -1);
    
    stack<int> st;
    st.push(1);
    color[1] = 0;

    while(!st.empty()){
        int node = st.top();
        st.pop();
        for(auto nbr: adj[node]){
            if(color[nbr] == -1){
                color[nbr] = 1 - color[node];
                st.push(nbr);
            }
            else if(color[nbr] == color[node]){
                // odd cycle detected, not a Bipartite
                return false;
            }
        }
    }
    return true;
}

bool IsCyclePresentDirectedGraph_dfs(int n, vector<vector<int>> &edges){
    // Step 1: Build adjacency list for the directed graph (1-based nodes expected).
    // We create a map from each node to its outgoing neighbors.
    unordered_map<int, vector<int>> adj;
    for(auto &edge: edges){
        adj[edge[0]].push_back(edge[1]);
    }

    // Step 2: Prepare color/marking array.
    // 0 = unvisited, 1 = visiting (currently in stack / recursion path), 2 = finished (fully processed)
    vector<int> color(n+1, 0);

    // Step 3: Iterate through all nodes to ensure disconnected components are handled.
    for(int start = 1; start <= n; ++start){
        if(color[start] == 0){
            // We'll simulate recursive DFS using an explicit stack of pairs (node, state).
            // state == 0 -> node is being entered (pre-visit)
            // state == 1 -> node post-processing (all neighbors handled)
            
            stack<pii> st;

            // Push the start node in pre-visit state and mark it as visiting.
            st.push({start, 0});
            color[start] = 1; // mark as 'in current path'

            // Step 4: Process stack until empty
            while(!st.empty()){
                int node = st.top().first;
                int state = st.top().second;
                st.pop();

                if(state == 0){
                    // Pre-visit actions:
                    // - push a post-visit marker so we can mark this node finished after its neighbors
                    st.push({node, 1});

                    // - iterate neighbours
                    for(auto nbr : adj[node]){
                        if(color[nbr] == 0){
                            // Neighbor not visited yet: schedule it for processing and mark as visiting
                            st.push({nbr, 0});
                            color[nbr] = 1; // now in current path
                        }
                        else if(color[nbr] == 1){
                            // Neighbor is already in the current path -> back-edge -> cycle found
                            return true;
                        }
                        // if color[nbr] == 2, neighbor already fully processed -> ignore
                    }
                }
                else{
                    // Post-visit actions: all neighbours processed, mark node finished (no longer in path)
                    color[node] = 2;
                }
            }
        }
    }

    // No back-edge detected in any component -> no cycle
    return false;
}




bool directed_graph_cycle_bfs_kahn_algo(int n, vector<vector<int>> &edges){
    // Step 1: Build adjacency list and compute indegrees for every node.
    // - adj[u] contains all nodes v such that there is an edge u -> v.
    // - inDeg[v] counts the number of incoming edges to v.
    unordered_map<int, vector<int>> adj;
    vector<int> inDeg(n+1, 0);
    for(auto e: edges){
        adj[e[0]].push_back(e[1]);
        inDeg[e[1]]++;
    }

    // Step 2: Initialize queue with all nodes having indegree 0.
    // These nodes have no dependencies and can appear first in a topological order.
    queue<int> qu;
    for(int i=1;i<=n;i++){
        if(inDeg[i]==0)
            qu.push(i);
    }

    // Step 3: Process nodes in BFS manner (Kahn's algorithm)
    // - Pop a node, count it as processed.
    // - For each outgoing neighbour, decrement its indegree (we removed one incoming edge).
    // - If a neighbour's indegree becomes 0, it is ready to be processed; push to queue.
    int count=0;
    while(!qu.empty()){
        int node = qu.front();
        qu.pop();
        // This node is next in topological order
        count++;
        for(auto nbr: adj[node]){
            // remove edge node -> nbr by decrementing indegree
            inDeg[nbr]--;
            // if no more incoming edges, neighbour can be visited next
            if(inDeg[nbr] == 0){
                qu.push(nbr);
            }
        }
    }

    // Step 4: Result evaluation
    // - If we processed exactly n nodes, a topological ordering exists -> no cycle.
    // - If processed count < n, some nodes were never processed because they are part of cycles.
    // Return true if a cycle exists, false otherwise.
    return (count != n);
}

void dfs_topo(int node, vector<vector<int>> &adj, 
    vector<bool> &vis, stack<int> &st){
    vis[node] = 1;
    for(auto nbr: adj[node]){
        if(!vis[nbr]){
            dfs_topo(nbr, adj, vis, st);
        }
    }
    st.push(node);
}

vector<int> GetTopoOrder(vector<vector<int>> &adj){
    vector<bool> vis(adj.size(), 0);
    stack<int> st;
    for(int i=0;i<adj.size();i++){
        if(!vis[i]){
            dfs_topo(i, adj, vis, st);
        }
    }
    vector<int> ans;
    while(!st.empty()){
        ans.push_back(st.top());
        st.pop();
    }
    return ans;
}



vector<char> AllienDictionary(vector<string> &dict, int s){
    int n = dict.size();
    vector<vector<int>> adj(s, vector<int>());
    for(int i=1;i<n;i++){
        int k=0;
        while(k<dict[i].size() && k<dict[i-1].size() && dict[i][k]==dict[i-1][k]){
            k++;
        }
        if(k<dict[i-1].size() && k<dict[i].size())
            adj[dict[i-1][k]-'a'].push_back(dict[i][k]-'a');
        else if(k<dict[i-1].size() && k==dict[i].size()){
            return {};
        }
    }

    vector<bool> vis(s, 0);
    stack<int> st;
    for(int i=0;i<s;i++){
        if(!vis[i]){
            dfs_topo(i, adj, vis, st);
        }
    }
    vector<char> res;
    while(!st.empty()){
        res.push_back('a'+st.top());
        st.pop();
    }
    return res;
}

vector<int> ShortestPathDAG(vector<pair<int, pair<int, int>>> &edges, int src){
    unordered_map<int, vector<pair<int,int>>> adj;
    int max_node = 0;
    for(auto e: edges){
        int parent = e.first;
        int child = e.second.first;
        int weight = e.second.second;
        adj[parent].push_back({child, weight});
        max_node = max(max_node, max(parent, child));
    }

    // Topo sort
    vector<int> inDeg(max_node+1, 0);
    for(auto nodes: adj){
        for(auto node: nodes.second){
            inDeg[node.first]++;
        }
    }
    queue<int> qu;
    vector<int> topo;
    for(int i=1;i<=max_node;i++){
        if(inDeg[i]==0){
            qu.push(i);
        }
    }
    while(!qu.empty()){
        int node = qu.front();
        qu.pop();
        topo.push_back(node);
        for(auto nbr: adj[node]){
            inDeg[nbr.first]--;
            if(inDeg[nbr.first]==0){
                qu.push(nbr.first);
            }
        }
    }
    if(topo.size() != max_node){
        return {};
    }
    int i=0;
    while(topo[i]!=src){
        i++;
    }
    vector<int> dist(max_node+1, INT_MAX);
    dist[topo[i]] = 0;
    while (i < topo.size())
    {
        int node = topo[i];
        for(auto nbr: adj[node]){
            int v = nbr.first;
            int wt = nbr.second;
            if(dist[node]+wt < dist[v]){
                dist[v] = dist[node]+wt;
            }
        }
    }
    return dist;
}

pair<int, vector<int>> doc_processing(int m, vector<int> &queue_time,
    vector<int> &processing_time, int k){

    int n = queue_time.size(), totalProcessed = 0;
    vector<int> end_time(m, 0), cnt(m, 0);

    for(int i=0;i<n;i++){

        int pref = i%m;
        for(int j=0;j<m;j++){
            int idx = (pref + j)%m;

            if(end_time[idx] <= queue_time[i]){
                end_time[idx] = queue_time[i] + processing_time[i];
                cnt[idx]++;
                totalProcessed++;
                break;
            }
        }

    }
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for(int i=0;i<m;i++){
        pq.push({cnt[i], i});
        if(pq.size() > k){
            pq.pop();
        }
    }
    vector<int> topK;
    while(!pq.empty()){
        topK.push_back(pq.top().second);
        pq.pop();
    }
    return {totalProcessed, topK};
}

double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    using pdi=pair<double, int>;
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    for(int i=0;i<classes.size();i++){
        int pass=classes[i][0];
        int tot = classes[i][1];
        double ratio = (double)pass/(double)tot;
        pq.push({ratio, i});
    }
    for(int i=1;i<=extraStudents;i++){
        pdi top_class = pq.top();
        int cls = pq.top().second;
        pq.pop();
        double ratio = (double)(classes[cls][0]+1)/(double)(classes[cls][1]+1);
        classes[cls][0] += 1;
        classes[cls][1] += 1;
        pq.push({ratio, cls});
    }
    double sum, cnt=0;
    while (!pq.empty())
    {
        sum += pq.top().first;
        pq.pop();
        cnt++;
    }
    return sum/cnt;
    
}

string repeatLimitedString(string s, int repeatLimit) {
    vector<int> freq(26, 0);
    for(auto ch: s){
        freq[ch-'a']++;
    }
    priority_queue<pii> pq;
    for(int i=0;i<26;i++){
        pq.push({i, freq[i]});
    }
    string res = "";
    while(!pq.empty()){
        int ch = pq.top().first;
        int count = pq.top().second;
        pq.pop();
        int reqd = min(count, repeatLimit);
        count -= reqd;
        while(reqd--){
            res.push_back('a'+ch);
        }
        if(count > 0){
            if(pq.empty())
                break;
            int ch2 = pq.top().first;
            int count2 = pq.top().second;
            pq.pop();
            res.push_back('a'+ch2);
            count2 -= 1;
            if(count2>0){
                pq.push({ch2, count2});
            }
            pq.push({ch, count});
        }
    }
    return res;
}

int minSetSize(vector<int>& arr) {
    unordered_map<int, int> freq;
    for(auto ar: arr){
        freq[ar]++;
    }
    priority_queue<pair<int, int>> pq;
    for(auto fr: freq){
        pq.push({fr.second, fr.first});
    }
    int sum = 0, ans=0;

    while(sum<arr.size()/2){
        sum += pq.top().first;
        pq.pop();
        ans++;
    }
    return ans;
}

int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for(char ch: tasks){
        freq[ch-'A']++;
    }
    priority_queue<int> pq;
    for(int i=0;i<26;i++){
        if(freq[i]>0) pq.push(freq[i]);
    }
    int time=0;
    while(!pq.empty()){
        vector<int> tmp;
        int i=0;
        for(;i<=n && !pq.empty();i++){
            int tp = pq.top();
            pq.pop();
            if(--tp > 0) tmp.push_back(tp);
        }
        for(int v: tmp){
            pq.push(v);
        }
        time += pq.empty() ? i : (n+1);
    }
    return time;
}

long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k) {
    if(grid.size()==0 || grid[0].size()==0) return 0;
    int n = grid.size(), m = grid[0].size(), take=0;
    priority_queue<int, vector<int>, greater<int>> fpq;
    for(int i=0;i<n;i++){
        take += limits[i];
        for(int j=0;j<m;j++){
            fpq.push(grid[i][j]);
            if(fpq.size()>take){
                fpq.pop();
            }
        }
    }
    while(fpq.size()>k){
        fpq.pop();
    }
    long long sum = 0;
    while(!fpq.empty()){
        sum += fpq.top();
        fpq.pop();
    }
    return sum;
}

int word_ladder(string beginWord, string endWord, vector<string>& wordList){
    int n = wordList.size();
    set<string> list;
    for(int i=0;i<n;i++){
        list.insert(wordList[i]);
    } 
    queue<pair<string, int>> qu;
    qu.push({beginWord, 1});
    list.erase(beginWord);
    int ans = -1;
    while(!qu.empty()){
        string word = qu.front().first;
        int lvl = qu.front().second;
        qu.pop();
        if(word == endWord){
            ans = lvl;
            break;
        }
        for(int i=0;i<word.length();i++){
            for(int j=0;j<26;j++){
                string tmp = word;
                tmp[i] = 'a'+j;

                if(list.find(tmp)!=list.end()){
                    qu.push({tmp, lvl+1});
                    list.erase(tmp);
                }
            }
        }
    }
    return ans==-1 ? 0 : ans;
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    int n = wordList.size();
    unordered_set<string> st;
    for(auto w: wordList){
        st.insert(w);
    }
    queue<vector<string>> qu;
    qu.push({beginWord});
    st.erase(beginWord);
    int lvl = INT_MAX;
    vector<vector<string>> ans;
    while(!qu.empty()){
        
        int sz = qu.size();
        unordered_set<string> delWords;
        while(sz--){
            auto path = qu.front();
            string word = path.back();
            qu.pop();
            if(word == endWord){
                if(ans.size()==0 || ans[0].size()==path.size()){
                    ans.push_back(path);
                }
                else if(path.size()>ans[0].size()){
                    return ans;
                }
            }
            
            for(int i=0;i<word.size();i++){
                for(int j=0;j<26;j++){
                    string temp_word = word;
                    temp_word[i] = j + 'a';
                    if(st.find(temp_word)!=st.end()){
                        vector<string> temp_path = path;
                        temp_path.push_back(temp_word);
                        qu.push(temp_path);
                        delWords.insert(temp_word);
                    }
                }
            }
            
        }
        for(auto w: delWords){
            st.erase(w);
        }
    }
    return ans;
}

int GetParentNode(int node, vector<int> &par){
    if(par[node] == node) return node;
    return par[node] = GetParentNode(par[node], par);
}

bool Union(int u, int v, vector<int> &par, vector<int> &sz){
    int pu = GetParentNode(u, par);
    int pv = GetParentNode(v, par);

    if(pu == pv){
        return false;
    }
    par[pv] = pu;
    sz[pu] += sz[pv];
    return true;
}

vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    vector<int> parent(n + 1, 0);
    vector<int> candA, candB;
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        if (parent[v] == 0) {
            parent[v] = u;
        } else {
            candA = {parent[v], v};
            candB = edge;
            edge[1] = 0; // Temporarily remove this edge
        }
    }
    // Union-Find
    vector<int> par(n + 1);
    for (int i = 1; i <= n; ++i) par[i] = i;
    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        if (v == 0) continue; // skip removed edge
        int pu = u, pv = v;
        while (par[pu] != pu) pu = par[pu];
        while (par[pv] != pv) pv = par[pv];
        if (pu == pv) {
            if (candA.empty()) return edge;
            return candA;
        }
        par[pv] = pu;
    }
    return candB;
}

bool findOrder_dfs(int node, unordered_map<int, vector<int>> &adj,
    vector<int> &vis, vector<int> &ans_path, unordered_set<int> &inPath){
    
    inPath.insert(node);
    vis[node] = 1;
    for(auto nbr: adj[node]){
        if(!vis[nbr]){
            if(!findOrder_dfs(nbr, adj, vis, ans_path, inPath))
                return false;
        }
        else if(inPath.find(nbr) != inPath.end()){ // if nbr node is present in current traversing path
            return false;
        }
    }
    inPath.erase(node);
    ans_path.push_back(node);
    return true;
}

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    unordered_map<int, vector<int>> adj;
    vector<int> vis(numCourses, 0), ans_path;
    unordered_set<int> inPath;

    for(auto pre: prerequisites){
        adj[pre[0]].push_back(pre[1]);
    }
    for(int i=0;i<numCourses;i++){
        if(!vis[i]){
            if(!findOrder_dfs(i, adj, vis, ans_path, inPath)){
                return {};
            }
        }
    }
    return ans_path;
}

long long maxSumDivisibleby3(vector<int> &nums){
    long long n = nums.size(), totalSum=0;
    vector<int> mod1, mod2;
    for(auto it: nums){
        totalSum += it;
        if(it%3 == 1) mod1.push_back(it);
        if(it%3 == 2) mod2.push_back(it);
    }

    if(totalSum%3 == 0){
        return totalSum;
    }
    
    sort(mod1.begin(), mod1.end());
    sort(mod2.begin(), mod2.end());

    if(totalSum%3 == 1){
        int remove1 = (mod1.size()>=1) ? mod1[0] : INT_MAX;
        int remove2 = (mod2.size()>=2) ? mod2[0]+mod2[1] : INT_MAX;
        if(min(remove1, remove2) == INT_MAX)
            return 0;
        totalSum -= min(remove1, remove2);
    }

    else if(totalSum%3 == 2){
        int remove1 = (mod1.size()>=2) ? mod1[0]+mod1[1] : INT_MAX;
        int remove2 = (mod2.size()>=1) ? mod2[0] : INT_MAX;
        if(min(remove1, remove2) == INT_MAX)
            return 0;
        totalSum -= min(remove1, remove2);
    }
    return totalSum;
}

int_fast32_t main(){

    vector<int> nums = {2,2,2,1};
    cout<<"ANS: "<<maxSumDivisibleby3(nums)<<"\n";

    return 0;
}