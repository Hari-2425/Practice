#include <vector>
#include <set>
#include <algorithm>

using namespace std;

vector<int> calculateKthMinimumReliability(int k, int m, vector<int> reliability) {
    int n = reliability.size();
    vector<int> result;
    multiset<int> low, high;

    // Helper function to maintain the size and ordering of the two sets
    auto balance = [&]() {
        // Ensure low has at most k elements
        while (low.size() > k) {
            high.insert(*low.rbegin());
            low.erase(prev(low.end()));
        }
        // Ensure low gets elements from high if it has fewer than k
        while (low.size() < k && !high.empty()) {
            low.insert(*high.begin());
            high.erase(high.begin());
        }
        // Ensure all elements in low are <= all elements in high
        if (!low.empty() && !high.empty() && *low.rbegin() > *high.begin()) {
            int l_max = *low.rbegin();
            int h_min = *high.begin();
            low.erase(prev(low.end()));
            high.erase(high.begin());
            low.insert(h_min);
            high.insert(l_max);
        }
    };

    for (int i = 0; i < n; ++i) {
        // 1. Add the new element
        if (low.empty() || reliability[i] <= *low.rbegin()) {
            low.insert(reliability[i]);
        } else {
            high.insert(reliability[i]);
        }

        // 2. Remove the element that is sliding out of the window
        if (i >= m) {
            int to_remove = reliability[i - m];
            auto it = low.find(to_remove);
            if (it != low.end()) {
                low.erase(it);
            } else {
                high.erase(high.find(to_remove));
            }
        }

        // 3. Re-balance the sets
        balance();

        // 4. Capture the k-th minimum (the largest of the 'low' set)
        if (i >= m - 1) {
            result.push_back(*low.rbegin());
        }
    }

    return result;
}
