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
            using pii = pair<int, int>;
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

int_fast32_t main(){

    vector<vector<int>> edges = {
        {1, 2},
        {1, 3},
        {3, 4},
        {1, 5},
        {2, 3}
    };
    // Graph G(5, edges.size(), edges);
    // if(G.hasCycleUnDirectedGraph()){
    //     cout<<"Cycle exist in given graph.\n";
    // }
    // else{
    //     cout<<"Cycle does not exist in given graph.\n";
    // }

    DirectedGraph DG(5, edges.size(), edges);
    if(DG.hasCycleDirectedGraph()){
        cout<<"Cycle exist in given directed graph.\n";
    }
    else{
        cout<<"Cycle does not exist in given directed graph.\n";
    }
    return 0;
}