#include <iostream>
#include <vector>
#include <queue>
#include <map>

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

long long solve(vector<int>& instances, int M) {
    // 1. Max-Heap to always get the machine with the most instances
    priority_queue<int> maxHeap;
    
    // 2. Map to track frequencies of instance counts (to find the minimum non-zero)
    // std::map is sorted by key, so map.begin() is always the smallest count
    map<int, int> counts;

    for (int x : instances) {
        if (x > 0) {
            maxHeap.push(x);
            counts[x]++;
        }
    }

    long long totalCost = 0;

    for (int i = 0; i < M; ++i) {
        if (maxHeap.empty()) break; // No more instances available

        // Get the current Max and Min-non-zero
        int currentMax = maxHeap.top();
        int currentMin = counts.begin()->first;

        // Calculate cost for this customer
        totalCost += (currentMax + currentMin);

        // Update Max-Heap: Remove one instance from the max machine
        maxHeap.pop();
        
        // Update Frequency Map
        if (counts[currentMax] == 1) {
            counts.erase(currentMax);
        } else {
            counts[currentMax]--;
        }

        // Re-insert the machine if it still has instances left
        if (currentMax - 1 > 0) {
            maxHeap.push(currentMax - 1);
            counts[currentMax - 1]++;
        }
    }

    return totalCost;
}

int main() {
    vector<int> instances = {1, 3, 2, 4};
    int customers = 4;
    cout << "Total Cost: " << solve(instances, customers) << endl;
    return 0;
}


/**
 * Computes the total revenue after serving m customers.
 * Cost per customer = (current max instances) + (current min non-zero instances)
 */
long long maximizeRentalRevenue(vector<int>& vmStock, int m) {
    priority_queue<int> maxHeap;
    map<int, int> freqMap;

    // 1. Initial Load: Add all non-zero stocks to our tracking structures
    for (int stock : vmStock) {
        if (stock > 0) {
            maxHeap.push(stock);
            freqMap[stock]++;
        }
    }

    long long totalRevenue = 0;

    // 2. Process each customer
    for (int i = 0; i < m; ++i) {
        if (maxHeap.empty()) break; 

        // Find the current max and min non-zero
        int currentMax = maxHeap.top();
        int currentMin = freqMap.begin()->first;

        // Calculate revenue for this customer
        totalRevenue += (long long)currentMax + currentMin;

        // 3. Update structures: decrement the count of the chosen machine type
        maxHeap.pop();
        
        // Remove one instance of the value 'currentMax' from frequency tracking
        if (freqMap[currentMax] == 1) {
            freqMap.erase(currentMax);
        } else {
            freqMap[currentMax]--;
        }

        // If the machine still has instances left, put it back
        int remaining = currentMax - 1;
        if (remaining > 0) {
            maxHeap.push(remaining);
            freqMap[remaining]++;
        }
    }

    return totalRevenue;
}

int main() {
    // Example from the image:
    // vmStock = [2, 1, 1, 3], m = 4
    vector<int> vmStock = {2, 1, 1, 3};
    int m = 4;
    
    cout << maximizeRentalRevenue(vmStock, m) << endl; 
    // Expected Output: 12
    
    return 0;
}

