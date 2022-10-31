#include "utils.h"

// 这个题目跟permutation-in-str一样
std::vector<int> AnagramsInStr(const std::string& str, const std::string& pat)
{
    std::cout << "str: " << str << "\n";
    std::cout << "pat: " << pat << "\n";
    std::map<char, int> needs;
    for (auto&& p : pat) {
        needs[p]++;
    }

    std::vector<int> results;
    int start = 0;
    int match = 0;  // how many distinct char matched?
    for (int end = 0; end < str.size(); end++) {
        char c = str[end];
        if (needs.count(c) > 0) {  // contains?
            if (--needs[c] == 0) {  // we got all matches for one char
                match++;
            }
        }
        #if 1
        // 窗口长度大于pat长度？需要收缩窗口左边
        while (end - start + 1 >= pat.size()) {
            // 窗口已经满足了所有需要的字符?
            if (match == needs.size()) {
                results.push_back(start);
            }
            auto lc = str[start++];
            if (needs.count(lc) > 0) {
                // 以前全部满足了lc （=0)，现在要去除一个lc，需求加1，match--，不满足了
                // 或者以前满足太多了(<0)，现在去除一个lc，仍然满足，match不动
                if (needs[lc]++ == 0) {
                    match--;
                }
            }
        }

        #else
        // we got all matches for the entire pattern?
        if (match == needs.size()) {
            results.push_back(start);
        }

        // we don't get all matches, but we do have more chars traversed than pattern
        // then we need shrink left side, to remove one char not in pattern
        if (end >= (int)pat.size() - 1) {
            char leftc = str[start++];
            if (needs.count(leftc) > 0) {  // contains?
                if (needs[leftc] == 0) {
                    match--; // we need remove one match due to this leftc
                }
                needs[leftc]++;
            }
        }
        #endif
    }
    return results;
}

int main()
{
    {
        std::string str = "oidbcaf";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";  // 3
    }
    {
        std::string str = "oidbcafdbbcaa";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";  // 3, 9
    }
    {
        std::string str = "bcdxabcdy";
        std::string pat = "bcdyabcdx";
        std::cout << AnagramsInStr(str, pat) << "\n";  // 0
    }
    {
        std::string str = "aaacb";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";  // 2
    }
    {
        std::string str = "acba";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";  // 0, 1
    }
}
