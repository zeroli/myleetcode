#include "utils.h"

// 这题目于sliding-window\76. Minimum Window Substring.cc，其实是一样的
// smallest window that contains all characters in another string str2
// this window may contains chars not in str2
std::string ShortestWindowForSubstrInStr(const std::string& str, const std::string& pat)
{
    std::map<char, int> patFreq;
    for (auto&& p : pat) {
        patFreq[p]++;
    }

    int minLen = INT_MAX;
    int minStart = -1;
    int start = 0;
    int match = 0;  // how many distinct char matched?
    for (int end = 0; end < str.size(); end++) {
        char c = str[end];
        if (patFreq.count(c) > 0) {  // contains?
            if (--patFreq[c] == 0) {  // we got all matches for one char
                match++;
            }
        }

        // we got all matches, then we could try shrink left
        while (match == patFreq.size()) {  // we got all matches
            // update min window
            if (end - start + 1 < minLen) {
                minLen = end - start + 1;
                minStart = start;
            }
            char leftc = str[start++];
            if (patFreq.count(leftc) > 0) {  // contains?
                // 之前那个字符都满足了，现在要去除它，就存在不满足了，match--
                if (patFreq[leftc]++ == 0) {
                    match--; // we need remove one match due to this leftc
                }
            }
        }
    }
    return minStart >= 0 ? str.substr(minStart, minLen) : "";
}

int main()
{
    {
        std::string str = "aabdec";
        std::string pat = "abc";
        std::cout << ShortestWindowForSubstrInStr(str, pat) << "\n";  // abdec
    }
    {
        std::string str = "abdabca";
        std::string pat = "abc";
        std::cout << ShortestWindowForSubstrInStr(str, pat) << "\n";  // abc
    }
    {
        std::string str = "adcad";
        std::string pat = "abc";
        std::cout << ShortestWindowForSubstrInStr(str, pat) << "\n";  // ''
    }
}
