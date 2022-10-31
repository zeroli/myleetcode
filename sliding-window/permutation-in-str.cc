#include "utils.h"

bool PermutationInStr(const std::string& str, const std::string& pat)
{
    std::map<char, int> patFreq;
    for (auto&& p : pat) {
        patFreq[p]++;
    }

    int start = 0;
    int match = 0;  // how many distinct char matched?
    for (int end = 0; end < str.size(); end++) {
        char c = str[end];
        if (patFreq.count(c) > 0) {  // contains?
            if (--patFreq[c] == 0) {  // we got all matches for one char
                match++;
            }
        }
        while (end - start + 1 >= pat.size()) {
            if (match == patFreq.size()) {
                return true;
            }
            char leftc = str[start++];
            if (patFreq.count(leftc) > 0) {
                if (patFreq[leftc]++ == 0) {
                    match--;
                }
            }
        }
    }
    return false;
}

int main()
{
    {
        std::string str = "oidbcaf";
        std::string pat = "abc";
        std::cout << std::boolalpha << PermutationInStr(str, pat) << "\n";  // true
    }
    {
        std::string str = "bcdxabcdy";
        std::string pat = "bcdyabcdx";
        std::cout << std::boolalpha << PermutationInStr(str, pat) << "\n";  // true
    }
    {
        std::string str = "aaacb";
        std::string pat = "abc";
        std::cout << std::boolalpha << PermutationInStr(str, pat) << "\n";  // true
    }
    {
        std::string str = "eidboaoo";
        std::string pat = "ab";
        std::cout << std::boolalpha << PermutationInStr(str, pat) << "\n";  // false
    }
}
