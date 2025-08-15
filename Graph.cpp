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
};



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