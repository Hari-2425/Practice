#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>


using namespace std;

// Given a list of order strings like:

// ["B03 B06 B08", "B06 B08", "B12 B06"]

// Each string contains product IDs bought together.

// Task:
// Generate all unique unordered pairs of products bought together.

// If an order has exactly 2 items → that pair itself counts.

// If more than 2 items → generate all combinations of size 2.

// Count frequency of each pair.

// Return the pair with highest frequency.

// If multiple pairs have same frequency → return lexicographically smallest pair.

// Example:
// "B03 B06 B08" → (B03,B06), (B03,B08), (B06,B08)


int main() {
    vector<string> orders = {"B03 B06 B08", "B06 B08", "B12 B06"};

    // 1. Map each Product ID to a bit position (0 to 63)
    unordered_map<string, int> productToBit;
    vector<string> bitToProduct;
    int bitCount = 0;

    for (const string& order : orders) {
        stringstream ss(order);
        string pid;
        while (ss >> pid) {
            if (productToBit.find(pid) == productToBit.end()) {
                productToBit[pid] = bitCount++;
                bitToProduct.push_back(pid);
            }
        }
    }

    // 2. Convert orders into Bitmasks (integers)
    vector<uint64_t> masks;
    for (const string& order : orders) {
        uint64_t mask = 0;
        stringstream ss(order);
        string pid;
        while (ss >> pid) {
            mask |= (1ULL << productToBit[pid]);
        }
        masks.push_back(mask);
    }

    // 3. Count Pair Frequencies using Bitwise AND
    // We iterate through all possible pairs of products
    map<pair<string, string>, int> counts;
    for (int i = 0; i < bitCount; ++i) {
        for (int j = i + 1; j < bitCount; ++j) {
            uint64_t pairMask = (1ULL << i) | (1ULL << j);
            
            for (uint64_t orderMask : masks) {
                // If both bits are set in the orderMask
                if ((orderMask & pairMask) == pairMask) {
                    string p1 = bitToProduct[i];
                    string p2 = bitToProduct[j];
                    if (p1 > p2) swap(p1, p2); // Ensure lexicographical order
                    counts[{p1, p2}]++;
                }
            }
        }
    }

    // 4. Find the Winner
    pair<string, string> bestPair;
    int maxFreq = 0;

    for (auto it = counts.begin(); it != counts.end(); ++it) {
        const pair<string, string>& pair = it->first;
        int freq = it->second;
        if (freq > maxFreq) {
            maxFreq = freq;
            bestPair = pair;
        } else if (freq == maxFreq) {
            if (bestPair.first == "" || pair < bestPair) {
                bestPair = pair;
            }
        }
    }

    cout << "Best Pair: (" << bestPair.first << ", " << bestPair.second << ") with " << maxFreq << " hits." << endl;

    return 0;
}
