#include "utils.h"

/*
You are given two arrays (without duplicates) nums1 and nums2
wherenums1’s elements are subset ofnums2.
Find all the next greater numbers fornums1's elements in the corresponding places ofnums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right innums2.
 If it does not exist, output -1 for this number.

Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.

Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
*/

std::vector<int> NextGreaters(const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    std::map<int, int> map;
    std::stack<int> stk;
    for (int i = 0; i < arr2.size(); i++) {
        // 单调栈，栈内元素维持递减，一旦碰到一个大的
        // 就直到一个新的next greater过来了，
        // 需要弹出一些比较小的元素，因为它们的next greater即使当前元素arr[i]
        while (!stk.empty() && stk.top() < arr2[i]) {
            map[stk.top()] = arr2[i];
            stk.pop();
        }
        stk.push(arr2[i]);
    }
    std::vector<int> res;
    for (int i = 0; i < arr1.size(); i++) {
        if (map.count(arr1[i]) > 0) {
            res.push_back(map[arr1[i]]);
        } else {
            res.push_back(-1);
        }
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr1 = { 4, 1, 2 };
        std::vector<int> arr2 = { 1, 3, 4, 2 };
        std::cout << NextGreaters(arr1, arr2) << "\n";  // -1,3,-1
    }
    {
        std::vector<int> arr1 = { 2, 4 };
        std::vector<int> arr2 = { 1, 2, 3, 4 };
        std::cout << NextGreaters(arr1, arr2) << "\n";  // 3, -1
    }
}
