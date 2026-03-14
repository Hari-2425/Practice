#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int findMinimumOperations(vector<int> arr) {
    int n = arr.size();
    if (n <= 1) return 0;

    // 1. Identify the starting state
    // dir 0: Increasing cyclic, dir 1: Decreasing cyclic
    int start_val = arr[0];
    int dir = 0;
    
    // Check direction based on first two elements
    // For n=2, [2,1] could be seen as either, but BFS handles both.
    if (arr[1] != (arr[0] % n) + 1) {
        dir = 1;
    }

    // 2. Setup BFS
    // dist[direction][start_value]
    vector<vector<int>> dist(2, vector<int>(n + 1, -1));
    queue<pair<int, int>> q;

    dist[dir][start_val] = 0;
    q.push({dir, start_val});

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        int d = curr.first;
        int v = curr.second;
        int step = dist[d][v];

        // Target: Increasing sequence starting with 1
        if (d == 0 && v == 1) return step;

        // Operation 1: Reverse
        // If S_v: [v, v+1...n, 1...v-1], reverse ends with v, starts with v-1
        // If R_v: [v, v-1...1, n...v+1], reverse ends with v, starts with v+1
        int next_v_rev, next_d_rev = 1 - d;
        if (d == 0) next_v_rev = (v == 1) ? n : v - 1;
        else next_v_rev = (v % n) + 1;

        if (dist[next_d_rev][next_v_rev] == -1) {
            dist[next_d_rev][next_v_rev] = step + 1;
            q.push({next_d_rev, next_v_rev});
        }

        // Operation 2: Rotate Left
        // If S_v, becomes S_{v+1}
        // If R_v, becomes R_{v-1}
        int next_v_rot, next_d_rot = d;
        if (d == 0) next_v_rot = (v % n) + 1;
        else next_v_rot = (v == 1) ? n : v - 1;

        if (dist[next_d_rot][next_v_rot] == -1) {
            dist[next_d_rot][next_v_rot] = step + 1;
            q.push({next_d_rot, next_v_rot});
        }
    }

    return -1; // Guaranteed reachable per problem statement
}

int main() {
    // Example from image: n=10, arr=[2,3,4,5,6,7,8,9,10,1]
    vector<int> arr = {2, 3, 4, 5, 6, 7, 8, 9, 10, 1};
    cout << "Min Operations: " << findMinimumOperations(arr) << endl; 
    // Output: 3
    return 0;
}
