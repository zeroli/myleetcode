/*
1 => true
121 => true

-212 => false
17 => false
*/

#include "utils.h"
#include <cmath>

bool CheckIntegerPalindrome(int x)
{
    if (x < 0) return false;

    /* 我们可以将数字转换成字符串，然后利用字符串的数组特性来判断是否为回文
        但是需要额外的n的存储空间，n为x数字的个数
        获取lsb的数字比较容易，但是怎么获取msb的数字呢？
        如果是二进制，位长度我们知道，获取当前msb位，可以直接移位
        移位就是代表log2操作
        那么对于10进制，我们可以调用log10来获取数字总位数，后面每次都除以100
    */
    int ndigits = int(std::floor(std::log10(x))) + 1;
    int msb = int(std::pow(10, ndigits-1));
    for (int i = 0; i < ndigits/2; i++) {
        if (x / msb != x % 10) {
            return false;
        }
        x %= msb;  // 去掉msb位
        x /= 10;  // 去掉lsb位
        msb /= 100;  // 因为我们去掉了2个数字，所以要除以100
    }
    return true;
}

int main()
{
    {
        int x = 1;
        std::cout << std::boolalpha<< CheckIntegerPalindrome(x) << std::endl;  // true
    }
    {
        int x = -1;
        std::cout << std::boolalpha<< CheckIntegerPalindrome(x) << std::endl;  // false
    }
    {
        int x = 12344321;
        std::cout << std::boolalpha<< CheckIntegerPalindrome(x) << std::endl;  // true
    }
    {
        int x = 123421;
        std::cout << std::boolalpha<< CheckIntegerPalindrome(x) << std::endl;  // false
    }
}
