/*
Given an array of integers, every element appears three times except for one. Find that single one.
Note: Your algorithm should have a linear runtime complexity. Could you implement it without using
extra memory?

*/

#include "utils.h"

int SingleNum0(const std::vector<int>& arr)
{
    /*
    一个数只有一份，其它数都重复3次
    对每一位加和，重复三次的数，对应位要么是1，1，1，要么是0，0，0
    它们加和的结果一定是3个倍数，那个单独的数对应位要么是1，要么是0
    用一个32个元素的数组，每一个元素就是对应位加和的结果
    最后遍历这个32个元素的数组，将每一元素模3，
    结果就是那个单独数对应的值，要么是0，要么是1
    算法用到了额外的数组，固定大小，时间复杂度为O(n)
    但是怎么不用这额外的数组呢？
    */
    int n = arr.size();
    int sum[32] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 32; j++) {
            sum[j] += ((arr[i] >> j) & 0x1);
        }
    }
    int x = 0;
    for (int j = 0; j < 32; j++) {
        sum[j] %= 3;
        x |= (sum[j] << j);
    }
    return x;
}

int bitJ(int x, int j)
{
    return (x >> j) & 0x1;
}

// int SingleNum(const std::vector<int>& arr)
// {
//     int n = arr.size();
//     int sum1 = 0, sum2 = 0;  // 代表32bit的mod 3的结果
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < 32; j++) {
//             int bits = (bitJ(x, j) + bitJ(arr[i], j)) % 3;
//             // 将x的j对应位设置为新求解的bit
//             x = (x & ~(1 << j)) | (bits << j);
//         }
//     }

//     return x;
// }

int main()
{
    {
        std::vector<int> arr = { 1, 1, 3, 3, 1, 2, 3 };
        std::cout << SingleNum0(arr) << "\n";  // 2;
        std::cout << SingleNum(arr) << "\n";  // 2;
    }
}
