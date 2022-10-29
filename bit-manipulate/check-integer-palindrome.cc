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
    /*
    计算ndigit，可以不用下面的C函数来计算
    */
    #if 0
    int d = 1;
    while (x / d >= 10) d *= 10;
    // 比如9999 => d=1000
    while (x > 0) {
        if (x / d != x % 10) {
            return false;
        }
        x %= d;  // 去掉最高位
        x /= 10;  // 去掉最低位
        d /= 100; // 一次去掉了2位d
    }
    #endif
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

// 还有一种方法就是求出输入数字的reversed number，然后进行比较
// 但是这种方法有个问题就是数字有可能会溢出，reversed之后
// 所以方法不可取
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
