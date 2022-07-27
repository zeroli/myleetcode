#include "utils.h"

/*
Given two strings s and t of lengths m and n respectively,
return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

*/

std::string MinWindowSubstr(const std::string& str1, const std::string& str2)
{
    std::string ret;
    std::map<char, int> needs;
    for (auto c : str2) {
        needs[c]++;
    }

    int start = 0;
    int match = 0;
    int minLen = INT_MAX;
    for (int i = 0; i < str1.size(); i++) {
        auto c = str1[i];
        if (needs.count(c) > 0) {
            if (--needs[c] == 0) {  // 对于这个c，没有需求了，我们match了一个字符
                match++;
            }
        }
        // 当我们match所有unique字符后，我们就需要进行更新了。
        while (match >= needs.size()) {
            if (minLen > (i - start + 1)) {
                minLen = (i - start + 1);
                ret = str1.substr(start, minLen);
            }
            // 去除最左边的字符，会重新要求字符匹配么，还是剩余窗口里面有多余的？
            int t = str1[start];
            if (needs.count(t) > 0) {
                if (++needs[t] > 0) {
                    match--;
                }
            }
            start++;
        }
    }
    return ret;
}

int main()
{
    {
        std::string str1 = "ADOBECODEBANC", str2 = "ABC";
        std::cout << MinWindowSubstr(str1, str2) << "\n";
    }
    {
        std::string str1 = "a", str2 = "a";
        std::cout << MinWindowSubstr(str1, str2) << "\n";
    }
    {
        std::string str1 = "a", str2 = "aa";
        std::cout << MinWindowSubstr(str1, str2) << "\n";
    }
}
