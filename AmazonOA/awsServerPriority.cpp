#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

vector<int> getFinalPriorities(vector<int> priority) {
    int n = priority.size();
    
    // map: priority -> set of indices (automatically sorted lowest to highest)
    map<int, set<int>> priority_to_indices;
    // set of priorities currently shared by >= 2 processes (only for p > 0)
    set<int> dups;
    // Track the current priority of each index
    vector<int> current_p = priority;
    // Track if an index has been executed (removed)
    vector<bool> is_active(n, true);

    // Initial population
    for (int i = 0; i < n; ++i) {
        priority_to_indices[priority[i]].insert(i);
        if (priority_to_indices[priority[i]].size() >= 2 && priority[i] > 0) {
            dups.insert(priority[i]);
        }
    }

    while (!dups.empty()) {
        // 1. Find max priority p shared by at least 2 processes
        int p = *dups.rbegin(); 
        
        // Per Rule 1.1: If p = 0, terminate.
        // Our 'dups' set only contains p > 0, so if empty, we are done.
        
        auto& indices = priority_to_indices[p];
        
        // 2. Select two lowest indexes i1 and i2
        int i1 = *indices.begin();
        indices.erase(indices.begin());
        
        int i2 = *indices.begin();
        indices.erase(indices.begin());

        // Update 'dups' set for priority p if it no longer has 2+ processes
        if (indices.size() < 2) {
            dups.erase(p);
        }

        // 3. Process 1 is executed and removed from the queue
        is_active[i1] = false;

        // 4. Reduce priority of process 2 to floor(p/2)
        int next_p = p / 2;
        current_p[i2] = next_p;
        priority_to_indices[next_p].insert(i2);
        
        // If the new priority next_p now has 2+ processes, add to 'dups'
        // (Only if next_p > 0, as p=0 cannot be a 'p' per rule 1.1)
        if (next_p > 0 && priority_to_indices[next_p].size() >= 2) {
            dups.insert(next_p);
        }
    }

    // 5. Build result from remaining active processes in original index order
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (is_active[i]) {
            result.push_back(current_p[i]);
        }
    }
    return result;
}
