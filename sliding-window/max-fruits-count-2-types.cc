#include "utils.h"

// 小于等于2种类型的最大窗口长度
// 窗口内不同字符个数最多2种, at most K (K=2)
// 泛化版本：sliding-window\Longest-Substring-with-At-Most-Two-Distinct-Characters.cc
int MaxFruitsCount2Types(const std::string& fruits)
{
    std::map<char, int> fruitFreqs;

    int maxLen = 0;
    int start = 0;
    for (int end = 0; end < fruits.size(); end++) {
        fruitFreqs[fruits[end]]++;

        // <= 2 types, we will continue to calculate its length
        // 窗口内不满足要求了，则缩小窗口左边
        while (fruitFreqs.size() > 2) {
            // 去除左边的字符，如果=0，说明剩下字符没有重复(以前是1)
            // 可以从map中安全删除
            if (--fruitFreqs[fruits[start]] == 0) {
                fruitFreqs.erase(fruits[start]);
            }
            start++;
        }
        maxLen = std::max(maxLen, end - start + 1);
    }
    return maxLen;
}

int main()
{
    {
        std::string fruits = "ABCAC";  // 'CAC'，只有2种类型，长度为3
        std::cout << MaxFruitsCount2Types(fruits) << "\n";  // 3
    }
    {
        std::string fruits = "ABCBBC";  // 'BCBBC'，窗口内有2个种类型，长度为5
        std::cout << MaxFruitsCount2Types(fruits) << "\n";  // 5
    }
}
