#include "utils.h"

/*
Given an array of n integers nums and a target,
 find the number of index triplets i, j, k with 0 <= i < j < k < n that
  satisfy the conditionnums[i] + nums[j] + nums[k] < target.

Input:
nums = [-2,0,1,3], and target = 2
Output: 2

Explanation:
 Because there are two triplets which sums are less than 2:
             [-2,0,1]
             [-2,0,3]
*/

int ThreeSumSmaller(std::vector<int>& arr, int target)
{
    int n = arr.size();
    // 先排序，不断固定一个值，再用双指针从两边选定另外2个元素
    std::sort(arr.begin(), arr.end());
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        int j = i + 1;
        int k = n - 1;
        while (j < k) {
            if (arr[i] + arr[j] + arr[k] >= target) {
                k--;
            } else {
                // 从k一直递减到j + 1，都会导致与arr[j]加和小于<target
                // 因为arr[k]是此时较大元素，k-1到j+1都比它小
                count += (k - j);
                j++;
            }
        }
    }
    return count;
}

int main()
{
    std::vector<int> arr = { -2,0,1,3 };
    int target = 2;
    std::cout << ThreeSumSmaller(arr, target) << "\n";  // 2
}
