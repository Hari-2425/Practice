#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

// Standard GCD function
long long get_gcd(long long a, long long b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Function to find all divisors of a number
vector<int> find_divisors(int n) {
    vector<int> divs;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) divs.push_back(n / i);
        }
    }
    return divs;
}

vector<int> solve_packages(string packages) {
    int n = packages.length();
    // pref[i][c] = frequency of character (c + 'A') in packages[0...i-1]
    vector<vector<int>> pref(n + 1, vector<int>(26, 0));

    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i];
        pref[i + 1][packages[i] - 'A']++;
    }

    vector<int> result;
    for (int i = 1; i <= n; ++i) {
        // Find the GCD of length and all existing character counts
        int common_gcd = i;
        for (int c = 0; c < 26; ++c) {
            if (pref[i][c] > 0) {
                common_gcd = get_gcd(common_gcd, pref[i][c]);
            }
        }

        // Candidates for k are divisors of the common_gcd
        vector<int> candidates = find_divisors(common_gcd);
        sort(candidates.rbegin(), candidates.rend()); // Start with largest k

        int max_k = 1;
        for (int k : candidates) {
            if (k == 1) break; // 1 is always valid, so we stop here

            int s = i / k; // length of each part
            bool isValid = true;

            for (int c = 0; c < 26; ++c) {
                int target_per_part = pref[i][c] / k;
                // Check if every segment j has the correct cumulative count
                for (int j = 1; j < k; ++j) {
                    if (pref[j * s][c] != j * target_per_part) {
                        isValid = false;
                        break;
                    }
                }
                if (!isValid) break;
            }

            if (isValid) {
                max_k = k;
                break;
            }
        }
        result.push_back(max_k);
    }
    return result;
}

int main() {
    string packages = "ABAB";
    vector<int> ans = solve_packages(packages);
    for (int x : ans) cout << x << " "; 
    // Output for ABAB: 1 1 1 2
    return 0;
}
