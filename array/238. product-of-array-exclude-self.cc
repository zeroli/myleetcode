#include "utils.h"

/*
给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，
其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

示例:

输入: [1,2,3,4]
输出: [24,12,8,6]


提示：题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。

说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

进阶：
你可以在常数空间复杂度内完成这个题目吗？
（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）
*/

// 比较直接的方法就是采用2个数组，
// 一个用来存放对应i位置的前面i-1个元素的乘积
// 一个用来存放对应i位置的后面（n-i-1）个元素的乘积
// 这样接下来遍历，就可以直接将两个数组对应元素的成绩作为输出数组对应元素的值
// 然而其实我们不太需要两个数组，因为第二轮遍历原数组时，从后面开始遍历，
// 是可以不断计算出i位置后面元素的乘积的，
// 这样跟前缀乘积直接相乘就是对应位置的输出结果
std::vector<int> ProductOfArrayExcludeSelf(const std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> prod(n, 1);
    for (int i = 1; i < n; i++) {
        prod[i] = prod[i-1] * arr[i-1];
    }
    int tmp = 1;  // 代表i后面元素的乘积
    for (int i = n - 1; i >= 0; i--) {
        prod[i] *= tmp;
        tmp *= arr[i];
    }
    return prod;
}

// 但是进阶问题，如何不用额外的存储空间，但时间上仍然是O(n)?
// TODO

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3, 4 };
        std::cout << ProductOfArrayExcludeSelf(arr) << "\n";  // 24, 12, 8, 6
    }
}
