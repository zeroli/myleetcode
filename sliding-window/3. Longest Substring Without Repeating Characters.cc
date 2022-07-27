/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.



Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.



Constraints:

    0 <= s.length <= 5 * 104
    s consists of English letters, digits, symbols and spaces.


*/

#include "utils.h"

// without duplication
int LongestSubstr(const std::string& str)
{
    std::map<char, int> freqs;
    int j = 0;
    int maxLen = 0;
    for (int i = 0; i < str.size(); i++) {
#if 1
        if (freqs[str[i]]++ > 0) {
            while (i - j + 1 > freqs.size()) {  // has duplicates
                if (--freqs[str[j]] == 0) {
                    freqs.erase(str[j]);
                }
                j++;
            }
        }
#else
        auto c = str[i];
        freqs[c]++;
        // xxxyyyCxxxxxC
        while (freqs[c] > 1) {  // c has duplicates, until c doesn't duplicate
            if (--freqs[str[j]] == 0) {
                freqs.erase(str[j]);
            }
            j++;
        }
#endif
        maxLen = std::max(maxLen, i - j + 1);
        //std::cout << j << ": " << i << "=>" << maxLen << "\n";
    }
    return maxLen;
}

int main()
{
    {
        std::string str = "abcabcbb";
        std::cout << LongestSubstr(str) << "\n";  // 3
    }
    {
        std::string str = "bbbbb";
        std::cout << LongestSubstr(str) << "\n";  // 1
    }
    {
        std::string str = "pwwkew";
        std::cout << LongestSubstr(str) << "\n";  // 3
    }
}
