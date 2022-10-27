
/*
一个数，它的二进制表示中1的个数表示它的weight
给定义一个数x，写一个函数返回另一个数，有相同的weight，
而且跟x最接近，|x-y|最小
*/
#include "utils.h"

int NumBits1(uint64_t x)
{
    int n = 0;
    while (x) {
        n++;
        x &= (x-1);
    }
    return n;
}

uint64_t ClosestNumSameWeight0(uint64_t x)
{
    /* 暴力解法就是：
    1. 先求解x的weight，也就是bit1的个数
    2. 从x开始向两边探索，x-1, x+1, x-2, x+2, ...，查看每一个数的weight
    如果与x的weight相同，则找到一个数满足条件

    但是这个算法效率非常不高
    比如x = 2 ^ k(=8)(1000b)，算法需要搜索7,9,6,10,5,11,4，才能找到4
    如果k比较大，找到下一个2^(k-1)或者2^(k+1)，所需要遍历很多元素
    从这个思路可以看出，8(1000b)，找到对应的数4(0100b)，其实就是交换两个位置的bit
    */
    if (x == 0 || x == uint64_t(-1)) return -1;
    int wx = NumBits1(x);
    int x1 = x, x2 = x;
    while (1) {
        if (x1-- > 0) {
            int wx1 = NumBits1(x1);
            if (wx1 == wx) {
                return x1;
            }
        }
        if (x2++ < (uint64_t(-1))) {
            int wx2 = NumBits1(x2);
            if (wx2 == wx) {
                return x2;
            }
        }
    }
    return -1;  // cannot find it
}

uint64_t ClosestNumSameWeight(uint64_t x)
{
    /*
    新的思路就是：
    1. 我们要保持bit1的个数不变
    2. 下一个比x大的数，或者比x小的数
    如果我们从后向前找，
    a. 找到01，那么它的下一个大点的数就是10，而且bit1个数相同
    b. 找到10，那么它的下一个小点的数就是01，而且bit1个数相同
    找到这样的2个相邻bits，然后进行交换，就是满足条件的数
    这样的2个相邻bits，就是从后往前找2个不同的bits
    这个思路有点类似于next permutation
    */
    if (x == 0 || x == uint64_t(-1)) return -1;
    int n = 64;
    for (int i = 0; i < n-1; i++) {
        if (((x >> i) & 0x1) != ((x >> (i+1)) & 0x1)) {
            uint64_t mask = (1ull << i) | (1ull << (i+1));  // 两个bit都是1： 0x0...0110...0
            return x ^ mask;
        }
    }
    return -1;
}

int main()
{
    {
        uint64_t x = 0x2;
        std::cout << "0x" << std::hex << ClosestNumSameWeight0(x) << "\n";  // 0x1
        std::cout << "0x" << std::hex << ClosestNumSameWeight(x) << "\n";  // 0x1
    }
    {
        uint64_t x = 0x0;
        std::cout << "0x" << std::hex << ClosestNumSameWeight0(x) << "\n";  // -1
        std::cout << "0x" << std::hex << ClosestNumSameWeight(x) << "\n";  // -1
    }
    {
        uint64_t x = 0x8000000000000000;
        //std::cout << "0x" << std::hex << ClosestNumSameWeight0(x) << "\n";  // too slow
        std::cout << "0x" << std::hex << ClosestNumSameWeight(x) << "\n";  // 0x4000 0000 0000 0000
    }
}
