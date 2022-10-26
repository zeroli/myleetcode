/*
题目要求给定一个64bits的正数，求出它的二进制表示中1的个数的奇偶性
*/

#include "utils.h"

// 时间复杂度为O(N) (N为bit=1的个数)
int parityOfNumBit1(uint64_t x)
{
    int n = 0;
    while (x) {
        n++;
        x &= (x-1);
    }
    return n & 1;
}

// x & (x-1) => 清除最末尾的bit1
// x & -(x-1) => 只留下最末尾的bit1，其它位清0

// 时间复杂度为O(N) (N为bit=1的个数)
int parityOfNumBit1_1(uint64_t x)
{
    int n = 0;
    while (x) {
        n ^= 1;  /// 异或1，flip bit，偶数变成奇数，奇数变成偶数
        x &= (x-1);
    }
    return n & 1;
}

// 时间复杂度为O(logN) (N为64)
int parityOfNumBit1_2(uint64_t x)
{
    // 折半的进行异或操作
    // 0 ^ 1 = 1, 1 ^ 0 = 1, 0 ^ 0 = 0, 1 ^ 1 = 0
    // 64 => 32
    x ^= (x >> 32);  // leading 32 bits, ignored
    x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    return x & 0x1;  // 我们只看最后一位
}

// 还有一种解法，就是将64bits分成4个16bits的小点的数
// 16bits最有有65536个数，每个数的奇偶性可提前算出来
// 重复多次求取不同数的bit1的奇偶性时，可以将数分成4个部分
// 然后针对每个部分的奇偶性，进行查表

int main()
{
    {
        uint64_t x = 0x01;
        std::cout << parityOfNumBit1(x) << "\n";  // 1
        std::cout << parityOfNumBit1_1(x) << "\n";  // 1
        std::cout << parityOfNumBit1_2(x) << "\n";  // 1
    }
    {
        uint64_t x = 0x00;
        std::cout << parityOfNumBit1(x) << "\n";  // 0
        std::cout << parityOfNumBit1_1(x) << "\n";  // 0
        std::cout << parityOfNumBit1_2(x) << "\n";  // 0
    }
    {
        uint64_t x = 0x11;
        std::cout << parityOfNumBit1(x) << "\n";  // 0
        std::cout << parityOfNumBit1_1(x) << "\n";  // 0
        std::cout << parityOfNumBit1_2(x) << "\n";  // 0
    }
}
