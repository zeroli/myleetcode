#include "utils.h"

/*
Given an integer array nums and an integer k,
 return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.



Example 1:

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true
Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

Example 2:

Input: nums = [1,2,3,4], k = 3
Output: false

*/

// 有2种视角：
/*  有n个元素数组，有k个桶，每个桶最后要放入相同和的数组元素
 1） 以数组元素为视角，放入K个桶中，每个元素有当时有k个选择；
 2）以桶为视角，选择一个元素放入其中，可以有n种选择；
*/
// 以数组元素为视角，回溯算法
// index代表当前遍历到哪一个元素数组
/*
  一个数组，for循环遍历，迭代法：
  for (int i = 0; i < arr.size(); i++)
      print(arr[i]);
  也可以递归遍历，递归法：
  if (index == arr.size()) return;
  print(arr[index]);
  RecursiveCall(arr, index + 1);
  回溯算法采用的就是递归法。

  O(k^n)
  每个元素有k个桶可放
*/
bool backtracking(const std::vector<int>& arr, int index, std::vector<int>& buckets, int target)
{
    if (index == arr.size()) return true;

    // 遍历所有的bucket, 看下是否装入这个bucket
    for (int i = 0; i < buckets.size(); i++) {
        if (buckets[i] + arr[index] > target) {
            continue;
        }
        buckets[i] += arr[index];  // 做选择
        if (backtracking(arr, index + 1, buckets, target)) {
            return true;
        }
        buckets[i] -= arr[index];  // 撤销选择
    }
    return false;
}

bool CanPartition(const std::vector<int>& arr, int k)
{
    int sum = 0;
    for (auto& num : arr) {
        sum += num;
    }
    if (sum % k != 0) return false;
    int target = sum / k;
    std::vector<int> buckets(k);
    return backtracking(arr, 0, buckets, target);
}

/*
以bucket为视角，来选择数组元素放入
不同数组元素可以放入相同的bucket中
O(k * 2 ^ n)
每个元素有2个选择，放入或不放入，共有k个桶可放
*/
bool backtracking1(const std::vector<int>& arr, std::vector<int>& buckets, int iBucket, int target, std::vector<int>& skip)
{
    if (iBucket == buckets.size()) return true;

    // 遍历数组元素, 看下是否装入这个bucket(iBucket)
    for (int i = 0; i < arr.size(); i++) {
        if (skip[i]) {  // has been put into bucket
            continue;
        }
        if (buckets[iBucket] + arr[i] > target) {
            continue;
        }
        buckets[iBucket] += arr[i];  // 做选择
        if (buckets[iBucket] == target) {
            iBucket++;  // 装下一个bucket
        }
        skip[i] = 1;
        if (backtracking1(arr, buckets, iBucket, target, skip)) {
            return true;
        }
        buckets[iBucket] -= arr[i];  // 撤销选择
        skip[i] = 0;  // 撤销选择, 不装入
    }
    return false;
}

bool CanPartition1(const std::vector<int>& arr, int k)
{
    int sum = 0;
    for (auto& num : arr) {
        sum += num;
    }
    if (sum % k != 0) return false;
    int target = sum / k;
    std::vector<int> buckets(k);
    std::vector<int> skip(arr.size());
    return backtracking1(arr, buckets, 0, target, skip);
}

int main()
{
    {
        std::vector<int> arr = { 4,3,2,3,5,2,1 };
        int k = 4;
        std::cout << std::boolalpha << CanPartition(arr, k) << "\n";
    }
    {
        std::vector<int> arr = { 1,2,3,4 };
        int k = 3;
        std::cout << std::boolalpha << CanPartition(arr, k) << "\n";
    }
    {
        std::vector<int> arr = { 4,3,2,3,5,2,1 };
        int k = 4;
        std::cout << std::boolalpha << CanPartition1(arr, k) << "\n";
    }
    {
        std::vector<int> arr = { 1,2,3,4 };
        int k = 3;
        std::cout << std::boolalpha << CanPartition1(arr, k) << "\n";
    }
}
