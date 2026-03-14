#include <vector>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

long long optimizeReservedConcurrency(vector<int>& conc, vector<int>& price) {
    int n = conc.size();
    if (n <= 1) return 0;

    // 1. Pair concurrency with price and sort by concurrency
    vector<pair<int, int>> functions(n);
    for (int i = 0; i < n; ++i) {
        functions[i] = {conc[i], price[i]};
    }
    sort(functions.begin(), functions.end());

    priority_queue<int> pq; // Max-heap for prices
    long long totalCost = 0;
    long long currentHeapSum = 0;
    int i = 0;
    int currentLimit = functions[0].first;

    // 2. Iterate through concurrency levels
    while (i < n || !pq.empty()) {
        // If no functions are waiting to be assigned, jump to the next available limit
        if (pq.empty() && i < n) {
            currentLimit = functions[i].first;
        }

        // Add all functions that start at the current limit to the heap
        while (i < n && functions[i].first == currentLimit) {
            pq.push(functions[i].second);
            currentHeapSum += functions[i].second;
            i++;
        }

        // Pick the most expensive function to stay at 'currentLimit'
        if (!pq.empty()) {
            int maxPrice = pq.top();
            pq.pop();
            currentHeapSum -= maxPrice;

            // Every other function in the heap must be moved to at least currentLimit + 1
            // So we add their prices to the total cost for this single-step increase
            totalCost += currentHeapSum;
        }

        currentLimit++;
    }

    return totalCost;
}
