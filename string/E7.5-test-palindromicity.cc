/*
实现一个函数，测试给定的字符串是否是一个palindrome。
注意这个字符串包含非字母，测试应该忽略非字母，而且不用考虑大小写。
*/

#include "utils.h"

bool TestPalindromicity(const std::string& s)
{
    int i = 0, j = s.size() - 1;
    while (i < j) {
        while (i < j && !std::isalnum(s[i])) {
            i++;
        }
        while (i < j && !std::isalnum(s[j])) {
            j--;
        }
        if (std::tolower(s[i]) != std::tolower(s[j])) {
            return false;
        }
        i++, j--;  // ****
    }
    return true;
}

int main()
{
    {
        std::string str = "A man, a plan, a canal, Panama.";
        std::cout << TestPalindromicity(str) << "\n";  // 1
    }
    {
        std::string str = "Able was I, ere I saw Elba!";
        std::cout << TestPalindromicity(str) << "\n";  // 1
    }
    {
        std::string str = "Ray a Ray";
        std::cout << TestPalindromicity(str) << "\n";  // 0
    }
}
