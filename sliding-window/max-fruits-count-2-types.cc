#include "utils.h"

// 小于等于2种类型的最大窗口长度
int MaxFruitsCount2Types(const std::string& fruits)
{
    std::map<char, int> fruitFreqs;

    int maxLen = 0;
    int start = 0;
    for (int end = 0; end < fruits.size(); end++){
        fruitFreqs[fruits[end]]++;

        // <= 2 types, we will continue to calculate its length
        // 窗口内不满足要求了，则缩小窗口左边
        while (fruitFreqs.size() > 2) {
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
