#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

// Function to calculate how many units are sold if the cut-off price is 'mid'
ll countUnits(const vector<int>& stock, int mid) {
    ll count = 0;
    for (int s : stock) {
        if (s > mid) count += (s - mid);
    }
    return count;
}

ll maxRevenue(vector<int>& supplierStock, int orders) {
    int low = 0, high = 0;
    for (int s : supplierStock) high = max(high, s);

    int threshold = 0;
    // 1. Binary search to find the cut-off stock level
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (countUnits(supplierStock, mid) <= orders) {
            threshold = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    ll totalRevenue = 0;
    ll unitsSold = 0;

    // 2. Sell all units that have a price strictly greater than 'threshold'
    for (int s : supplierStock) {
        if (s > threshold) {
            ll n = s - threshold;
            // Sum of arithmetic progression from (threshold + 1) to s
            totalRevenue += n * (s + threshold + 1) / 2;
            unitsSold += n;
        }
    }

    // 3. Any remaining orders are sold at the 'threshold' price
    ll remainingOrders = orders - unitsSold;
    totalRevenue += remainingOrders * threshold;

    return totalRevenue;
}

int main() {
    vector<int> stock = {3, 5};
    int orders = 6;
    cout << "Maximum Revenue: " << maxRevenue(stock, orders) << endl; 
    // Output: 19
    return 0;
}
