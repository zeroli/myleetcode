#include "utils.h"

/*
Given a positive 32-bit integer n,
 you need to find the smallest 32-bit integer which
  has exactly the same digits existing in the integer n and is greater in value than n.
   If no such positive 32-bit integer exists, you need to return -1.

Input:
 12

Output:
 21
*/

/*
  这题思路于next permutation类似
  1) 从后向前搜索第一个突然变小的数字arr[i] < arr[i + 1]，说明i+1, ... n-1是递减序列
  2) 针对arr[i]，对i+1, ..., n-1区间的数进行搜索(线性/二分)，
    从后往前遍历找到第一个大于arr[i]的数字，将它于arr[i]进行替换
  3) 替换之后，真个数就变大了很多。需要将i+1, ... n-1的递减序列反转变成递增序列
    从而得到大于原数的最小的数
*/

std::vector<int> Num2Array(int n)
{
    std::vector<int> res;
    while (n) {
        res.push_back(n % 10);
        n /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

// FIXME: 需要判断是否溢出？？
int Array2Num(const std::vector<int>& arr)
{
    int n = 0;
    for (auto num : arr) {
        n = n * 10 + num;
    }
    return n;
}

int NextGreater(int n)
{
    auto arr = Num2Array(n);
    int m = arr.size();
    int i = -1;
    for (i = m - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            break;
        }
    }
    if (i < 0) {  // 没办法得到下一个更大数
        return -1;
    }

    // 从后线性遍历，找到第一个大于它i的数
    for (int j = m - 1; j > i; j--) {
        if (arr[j] > arr[i]) {
            std::swap(arr[i], arr[j]);
            break;
        }
    }
    // 反转arr[i+1, ...]
    std::reverse(&arr[i+1], &arr[m]);
    return Array2Num(arr);
}

int main()
{
    {
        int n = 12;
        std::cout << NextGreater(n) << "\n";  // 21
    }
    {
        int n = 1234516530;
        std::cout << NextGreater(n) << "\n";  // 1234530156
    }
}
