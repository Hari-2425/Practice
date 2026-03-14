#include <bits/stdc++.h>
using namespace std;

int calculateValidSegments(string codeSequence) {
    int n = codeSequence.length();
    int totalValid = 0;

    for (int i = 0; i < n; ++i) {
        vector<int> freq(26, 0);
        int uniqueCount = 0;
        int maxFreq = 0;

        // Optimization: Any substring longer than 26*26 is automatically invalid
        int limit = min(n, i + 676);

        for (int j = i; j < limit; ++j) {
            int charIdx = codeSequence[j] - 'a';
            
            if (freq[charIdx] == 0) {
                uniqueCount++;
            }
            freq[charIdx]++;
            
            // Track the highest frequency in the current substring
            if (freq[charIdx] > maxFreq) {
                maxFreq = freq[charIdx];
            }

            // Apply the Rule: Max Frequency <= Number of Unique Characters
            if (maxFreq <= uniqueCount) {
                totalValid++;
            } 
            // Optional: if maxFreq > 26, it can never become valid again by adding more chars
            else if (maxFreq > 26) {
                break;
            }
        }
    }

    return totalValid;
}
