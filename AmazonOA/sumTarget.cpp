#include <iostream>
#include <string>
#include <queue>
#include <unordered_set>

using namespace std;

// We are given an array representing the number of instances available for each machine type. Customers arrive one by one (M customers total).

// For each customer:

// Allocate an instance from the machine type having the maximum available instances.

// The cost incurred by that customer =
// (maximum instances before allocation) + (minimum non-zero instances currently present).

// After allocation, reduce that machine’s instance count by 1.

// Continue until all customers are processed or instances run out.

// We need to return the total cost incurred by all customers.

// Example:
// Instances = [1, 3, 2, 4]
// Customer 1 → max=4, min=1 → cost=5 → array becomes [1,3,2,3]
// …and so on.


struct State {
    int sum;
    int targetIdx;
    string path;
};

string findSmallestString(string target, int x, int y) {
    queue<State> q;
    // Initial state: sum 0, looking for 1st digit of target, empty string
    q.push({0, 0, ""});

    // To prevent infinite loops (if the sum repeats)
    unordered_set<string> visited;

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        // Process additions x and y (smaller one first for lexicographical order)
        int ops[] = {min(x, y), max(x, y)};
        
        for (int op : ops) {
            int nextSum = curr.sum + op;
            string nextPath = curr.path + to_string(nextSum).back();
            int nextIdx = curr.targetIdx;

            // Check if the last digit of the new sum matches our current target digit
            if (nextPath.back() == target[nextIdx]) {
                nextIdx++;
            }

            // If we've matched the whole target subsequence
            if (nextIdx == target.length()) {
                return nextPath;
            }

            // Create a unique key for visited states to avoid redundant paths
            string stateKey = to_string(nextSum % 10) + "_" + to_string(nextIdx);
            
            // Limit path length to prevent memory crash (optional safety)
            if (nextPath.length() < 15 && visited.find(nextPath + "_" + to_string(nextIdx)) == visited.end()) {
                q.push({nextSum, nextIdx, nextPath});
                visited.insert(nextPath + "_" + to_string(nextIdx));
            }
        }
    }

    return "-1";
}

int main() {
    string target = "27";
    int x = 2, y = 3;
    cout << "Smallest String: " << findSmallestString(target, x, y) << endl;
    return 0;
}


// Optimal approach
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

string solve(string config, int x, int y) {
    int n = config.length();
    int dx = x % 10;
    int dy = y % 10;

    // State: {last_digit, matched_idx}
    // matched_idx is how many chars of config we've matched as a subsequence
    map<pair<int, int>, string> curr_layer;

    // Rule: The first character of config must match the first addition
    if ((config[0] - '0') == dx) {
        curr_layer[{dx, 1}] = to_string(dx);
    }
    // Use if (not else if) in case dx == dy to pick smaller string if needed
    if ((config[0] - '0') == dy) {
        string s = to_string(dy);
        if (curr_layer.find({dy, 1}) == curr_layer.end() || s < curr_layer[{dy, 1}]) {
            curr_layer[{dy, 1}] = s;
        }
    }

    if (curr_layer.empty()) return "-1";

    // Visited table to ensure we only process the shortest path to each state
    bool visited[10][2005]; 
    memset(visited, 0, sizeof(visited));

    while (!curr_layer.empty()) {
        // Since BFS processes by length, the first layer that finds a full match is the shortest
        string best_finished = "";
        for (auto const& it : curr_layer) {
            if (it.first.second == n) {
                if (best_finished == "" || it.second < best_finished) {
                    best_finished = it.second;
                }
            }
        }
        if (best_finished != "") return best_finished;

        map<pair<int, int>, string> next_layer;
        for (auto const& it : curr_layer) {
            int d = it.first.first;
            int idx = it.first.second;
            string path = it.second;

            if (visited[d][idx]) continue;
            visited[d][idx] = true;

            int ops[2] = {dx, dy};
            for (int op : ops) {
                int next_d = (d + op) % 10;
                int next_idx = idx;
                
                // If this digit matches the next needed digit in the subsequence
                if (next_idx < n && next_d == (config[next_idx] - '0')) {
                    next_idx++;
                }

                pair<int, int> next_state = {next_d, next_idx};
                if (visited[next_state.first][next_state.second]) continue;

                string next_path = path + (char)('0' + next_d);
                
                // Keep only the lexicographically smallest string for this state in the next layer
                if (next_layer.find(next_state) == next_layer.end() || next_path < next_layer[next_state]) {
                    next_layer[next_state] = next_path;
                }
            }
        }
        curr_layer = next_layer;
    }

    return "-1";
}

