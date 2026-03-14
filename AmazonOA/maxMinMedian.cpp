#include <vector>
#include <algorithm>

using namespace std;

/**
 * find the maximum and minimum median overall subsequences of length k.
 * @param values: array of integers
 * @param k: length of subsequences
 * @return: vector containing {max_median, min_median}
 */
vector<int> medians(vector<int> values, int k) {
    int n = values.size();
    if (n == 0 || k == 0) return {};

    // 1. Sort the array to easily pick elements for subsequences
    sort(values.begin(), values.end());

    // 2. Identify the median index in a sorted subsequence of length k
    // Based on the example (k=2, median is smaller of middle two), index is (k-1)/2
    int m = (k - 1) / 2;

    // 3. Calculate the minimum possible median
    // This is the m-th element in the sorted array.
    int minMedian = values[m];

    // 4. Calculate the maximum possible median
    // This is the element that has at least (k-1-m) elements after it.
    // Index = (total_elements - 1) - (elements_needed_after_median)
    // Index = (n - 1) - (k - 1 - m) = n - k + m
    int maxMedian = values[n - k + m];

    // Return as [max, min] as per standard problem phrasing
    return {maxMedian, minMedian};
}
