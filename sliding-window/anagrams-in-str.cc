#include "utils.h"

// 这个题目跟permutation-in-str一样
std::vector<int> AnagramsInStr(const std::string& str, const std::string& pat)
{
    std::map<char, int> patFreq;
    for (auto&& p : pat) {
        patFreq[p]++;
    }

    std::vector<int> results;
    int start = 0;
    int match = 0;  // how many distinct char matched?
    for (int end = 0; end < str.size(); end++) {
        char c = str[end];
        if (patFreq.count(c) > 0) {  // contains?
            if (--patFreq[c] == 0) {  // we got all matches for one char
                match++;
            }
        }
        // we got all matches for the entire pattern?
        if (match == patFreq.size()) {
            results.push_back(start);
        }

        // we don't get all matches, but we do have more chars traversed than pattern
        // then we need shrink left side, to remove one char not in pattern
        if (end >= (int)pat.size() - 1) {
            char leftc = str[start++];
            if (patFreq.count(leftc) > 0) {  // contains?
                if (patFreq[leftc] == 0) {
                    match--; // we need remove one match due to this leftc
                }
                patFreq[leftc]++;
            }
        }
    }
    return results;
}

int main()
{
    {
        std::string str = "oidbcaf";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";
    }
    {
        std::string str = "bcdxabcdy";
        std::string pat = "bcdyabcdx";
        std::cout << AnagramsInStr(str, pat) << "\n";
    }
    {
        std::string str = "aaacb";
        std::string pat = "abc";
        std::cout << AnagramsInStr(str, pat) << "\n";
    }
}
