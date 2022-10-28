/*
compute x/y, x and y are unsigned integers, find the quotient,
using only addition, subtraction, and shifting operations
*/

#include "utils.h"

/*
思路：
假设: x/y = k
x = y + y + ... + y (k个y)
暴力解法就是从x中迭代的减去y，直到最后x小于y位置，统计其中减去的个数，就是k
或者不断的加y，直到加和大于x了，前面加和的次数就是k
*/

uint32_t Divide0(uint32_t x, uint32_t y)
{
    int k = 0;
    int sum = y;
    while (sum <= x) {
        sum += y;
        k++;
    }
    return k;
}

/*
但是暴力解法效率不高，比如x很大，y很小，这样的迭代的次数很大
x/y = k = (1+1+1+...+1)
k是由k个1加和的结果
如果我们看k的二进制数，就是很多1/0组合
k = (k1...k2...k3...km.0...0)
k = (2^k1 + 2^k2 + 2^k3 + ... + 2^km)
其中32>k1>k2>k3>...>km>=0
x/y = (2^k1 + 2^k2 + 2^k3 + ... + 2^km)
我们每次不再以减一个y的速度来计算k，而是以翻倍的速度来计算
y => (2^1)*y => (2^2)*y => (2^3)*y => ...一直到(2^31)*y
具体的算法代码就是不断的用right shift右移位操作来实现
k1从31开始尝试，与x比较，如果小，则k1可取，否则减1(右移1位)
k2从k1-1开始尝试，与(x-(2^k1)*y)比较，以此类推
*/
uint32_t Divide(uint32_t x, uint32_t y)
{
    uint32_t result = 0;
    int k = 32;
    while (x >= y) {
        uint64_t yp = ((uint64_t)y << k);
        while (x < yp) {
            // 这里不用每次计算(2^k) * y，由最开始的yp不断移位来得到下一个值，一半
            yp >>= 1;
            k--;
        }
        result += (1u << k);
        x -= yp;
    }
    return result;
}

int main()
{
    {
        uint32_t x = 10, y = 7;
        std::cout << Divide0(x, y) << std::endl;  // 1
        std::cout << Divide(x, y) << std::endl;  // 1
    }
    {
        uint32_t x = 0xffffff, y = 7;
        std::cout << Divide0(x, y) << std::endl;  // 2396745
        std::cout << Divide(x, y) << std::endl;  // 2396745
    }
    {
        uint32_t x = 0xffffffff, y = 1;
        //std::cout << Divide0(x, y) << std::endl;  // too slow
        std::cout << Divide(x, y) << std::endl;  // 0xffffffff (4294967295)
    }
}
