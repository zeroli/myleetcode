/*
swap 2 bits: i, j in 64 bits number
*/
#include "utils.h"

int Swap2Bits(uint64_t x, int i, int j)
{
    // 如果两个bit相等， 就不需要swap，直接返回x
    // 否则，1=>0, 0=>1，flip 2 bits
    // flip bit，跟1进行异或，就会flip
    if (((x >> i) & 0x1) != ((x >> j) & 0x1)) {
        uint64_t mask = (1 << i) | (1 << j);
        x ^= mask;
    }
    return x;
}


int main()
{
    {
        uint64_t x = 0x00;
        std::cout << "0x" << std::hex << Swap2Bits(x, 1, 3) << "\n";  // 0x00
    }
    {
        uint64_t x = 0x10;
        std::cout << "0x" << std::hex << Swap2Bits(x, 0, 3) << "\n";  // 0x10
    }
}
