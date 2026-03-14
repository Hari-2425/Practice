#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Returns the minimum number of proper substring sorts to sort the string.
 */
int getMinimumOperations(string strValue) {
    int n = strValue.length();
    
    // 1. Check if already sorted (0 operations)
    bool isSorted = true;
    for (int i = 0; i < n - 1; ++i) {
        if (strValue[i] > strValue[i + 1]) {
            isSorted = false;
            break;
        }
    }
    if (isSorted) return 0;

    // 2. Identify the global minimum and maximum characters
    char minChar = 'z' + 1;
    char maxChar = 'a' - 1;
    for (char c : strValue) {
        if (c < minChar) minChar = c;
        if (c > maxChar) maxChar = c;
    }

    // 3. Case for 1 operation: At least one boundary is already correct
    if (strValue[0] == minChar || strValue[n - 1] == maxChar) {
        return 1;
    }

    // 4. Case for 3 operations: The extremes are at the exact wrong ends
    // (First is Max AND Last is Min)
    if (strValue[0] == maxChar && strValue[n - 1] == minChar) {
        return 3;
    }

    // 5. Default case: 2 operations
    return 2;
}

int main() {
    // Example from image: zyxpqa
    // min = 'a', max = 'z'. str[0] == 'z' and str[5] == 'a'.
    cout << "Operations for zyxpqa: " << getMinimumOperations("zyxpqa") << endl; // Output: 3
    
    // Another example: xabx
    // min = 'a', max = 'x'. str[3] == 'x' (max).
    cout << "Operations for xabx: " << getMinimumOperations("xabx") << endl; // Output: 1
    
    return 0;
}
