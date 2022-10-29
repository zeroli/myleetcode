/*
42 => 24
-234 => -432
*/

#include "utils.h"

int ReverseDigits(int x)
{
    long result = 0;
    // 这里其实不用区分x是正负数，在x%10的时候
    // 对于负数，就会得到模的结果为负数
    while (x) {
        result = result * 10 + x % 10;
        x /= 10;
    }
    // 但是上面的解法有一个问题就是result在计算过程中会溢出
    // 因此需要用long来存储result，然后判断是否超过32bit正数表示的范围
    // 超过则返回0
    // 正数反转之后超过2147483647，就是正溢出
    // 负数反转之后小于-2147483648，就是负溢出
    return result;
}

int main()
{
    {
        int x = 42;
        std::cout << ReverseDigits(x) << std::endl;
    }
    {
        int x = -234;
        std::cout << ReverseDigits(x) << std::endl;
    }
}
