/*
1248. Count Number of Nice Subarrays
Medium

Given an array of integers nums and an integer k.
 A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.



Example 1:

Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:

Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.

Example 3:

Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16



Constraints:

    1 <= nums.length <= 50000
    1 <= nums[i] <= 10^5
    1 <= k <= nums.length
*/

#include "utils.h"

int NumOfNiceSubArr1(const std::vector<int>& arr, int k)
{
    int match = 0;
    int beg = 0;
    int cnt = 0;  // this is very important for handling case 3 correctly
    int res = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] & 1) {
            match++;
            cnt = 0;
        }
        // if meeting one even number, previous cnt result is still there
        while (match >= k) {
            cnt++;
            if (arr[beg] & 1) {
                match--;
            }
            beg++;
        }
        res += cnt;
    }
    return res;
}

// 这个题目下面的解法与下面两题的解法一样
// Count number of substrings with exactly k distinct characters
// 992.Subarrays-with-K-Different-Integers
int NumOfNiceSubArr(const std::vector<int>& arr, int k)
{
    int match = 0;
    int beg = 0;
    int prefix = 0;
    int res = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] & 1) {
            match++;
        }
        if (match > k) {
            if (arr[beg] & 1) {
                match--;
            }
            beg++;
            prefix = 0;
        }
        while ((arr[beg] & 1) == 0) {
            beg++;
            prefix++;
        }
        if (match == k) {
            res += 1 + prefix;
        }
    }
    return res;
}
/*
int NumOfNiceSubArr(const std::vector<int>& A, int k)
{
    int res = 0, i = 0, count = 0, n = A.size();
    for (int j = 0; j < n; j++) {
        if (A[j] % 2 == 1) {
            --k;
            count = 0;
        }
        while (k == 0) {
            k += A[i++] & 1;
            ++count;
        }
        res += count;
    }
    return res;
}
*/

int main()
{
    {
        std::vector<int> arr = { 1,1,2,1,1 };
        int k = 3;
        std::cout << NumOfNiceSubArr(arr, k) << "\n";  // 2
    }
    {
        std::vector<int> arr = { 2,4,6 };
        int k = 1;
        std::cout << NumOfNiceSubArr(arr, k) << "\n";  // 0
    }
    {
        std::vector<int> arr = { 2,2,2,1,2,2,1,2,2,2 };
        int k = 2;
        std::cout << NumOfNiceSubArr(arr, k) << "\n";  // 16
    }

}
