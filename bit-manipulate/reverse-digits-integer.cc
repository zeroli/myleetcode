/*
42 => 24
-234 => -432
*/

#include "utils.h"

int ReverseDigits(int x)
{
    int result = 0;
    // 这里其实不用区分x是正负数，在x%10的时候
    // 对于负数，就会得到模的结果为负数
    while (x) {
        result = result * 10 + x % 10;
        x /= 10;
    }
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
