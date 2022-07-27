#include "utils.h"

int MaxFruitsCount2Types(const std::string& fruits)
{
    std::map<char, int> fruitFreqs;

    int maxLen = 0;
    int start = 0;
    for (int end = 0; end < fruits.size(); end++){
        fruitFreqs[fruits[end]]++;

        // <= 2 types, we will continue to calculate its length
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
        std::string fruits = "ABCAC";
        std::cout << MaxFruitsCount2Types(fruits) << "\n";  // 3
    }
    {
        std::string fruits = "ABCBBC";
        std::cout << MaxFruitsCount2Types(fruits) << "\n";  // 5
    }
}
