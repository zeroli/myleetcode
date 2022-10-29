/*
计算x * y
不能采用常规的数值运算
可以采用赋值，位运算
*/

#include "utils.h"

/*
把输入的数以二进制来对待
13: 1101 (x)
09: 1001 (y)
固定y，判断x的当前位，要么照抄y，要么左移y，然后累加到最后的结果中
自己实现n比特位的两数加和
a, b, carry, sum
0, 0, 0, 0
0, 1, 0, 1
1, 0, 0, 1
1, 1, 1, 0
carry <= &
sum <= ^
*/

uint32_t Add(uint32_t x, uint32_t y)
{
    // 按照比特位加和，比特位加和可以用比特&和^来实现
    if (!x) return y;
    if (!y) return x;
    // carry位左移1位，再与sum进行加和
    return Add((x & y) << 1, (x ^ y));
}

// 按位加和的迭代版本
uint32_t Add2(uint32_t x, uint32_t y)
{
    uint32_t sum = 0, carry = 0;
    uint32_t k = 1;  // 第几位
    // x/y再迭代中没有变化，需要用这2个备份来迭代
    uint32_t tx = x, ty = y;
    while (tx || ty) {
        uint32_t bx = x & k;
        uint32_t by = y & k;
        sum |= (bx ^ by ^ carry);
        carry = (bx & by) | (bx & carry) | (by & carry);
        carry <<= 1;  // 给下一位运算做准备
        k <<= 1;
        tx >>= 1;
        ty >>= 1;
    }
    return sum | carry;
}

uint32_t Multiply(uint32_t x, uint32_t y)
{
    uint32_t result = 0;
    while (x) {
        if (x & 0x1) {
            result = Add(result, y);
        }
        x >>= 1;
        y <<= 1;
    }
    return result;
}

int main()
{
    {
        uint32_t x = 13, y = 9;
        std::cout << Multiply(x, y) << std::endl;
    }
}
