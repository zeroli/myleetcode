#include "utils.h"

/*
Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return compute the researcher's h-index.

According to the definition of h-index on Wikipedia:
 A scientist has an index h if h of their n papers have at least h citations each,
 and the other n − h papers have no more than h citations each.

If there are several possible values for h, the maximum one is taken as the h-index.


Example 1:

Input: citations = [3,0,6,1,5]
Output: 3
Explanation: [3,0,6,1,5] means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively.
Since the researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, their h-index is 3.

Example 2:

Input: citations = [1,3,1]
Output: 1

*/

int HIndex(const std::vector<int>& arr)
{
    int n = arr.size();
    // citation# for each index, its paper# for same citation will be value
    // citation# >=n will be aggregated at last index
    std::vector<int> counts(n+1);
    for (auto citation : arr) {
        if (citation >= n) {
            counts[n]++;
        } else {
            counts[citation]++;
        }
    }
    int count = 0;
    for (int h = n; h >= 0; h--) {
        // count how many paper# which each paper's citation is at least h
        count += counts[h];
        if (count >= h) {
            return h;
        }
    }
    return 0;
}

int main()
{
    {
        std::vector<int> arr = { 3, 0, 5, 6, 1 };
        std::cout << HIndex(arr) << "\n";
    }
}
