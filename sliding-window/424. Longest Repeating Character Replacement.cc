#include "utils.h"

/*
You are given a string s and an integer k.
 You can choose any character of the string and change it to any other uppercase English character.
  You can perform this operation at most k times.

Return the length of the longest substring containing
 the same letter you can get after performing the above operations.

 Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
*/

// 窗口内维护除了最多元素外的其他小众元素个数不超过k
int CountK(std::map<char, int>& freqs)
{
    int n = 0;
    int m = 0;
    for (auto&& f : freqs) {
        n += f.second;
        m = std::max(m, f.second);
    }
    return n - m;
}

int LongestRepeatAtMostKReplaces(const std::string& str, int k)
{
    int start = 0;
    int longest = 0;
    std::map<char, int> freqs;
    for (int i = 0; i < str.size(); i++) {
        freqs[str[i]]++;

        while (CountK(freqs) > k) {
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            start++;
        }
        longest = std::max(longest, i - start + 1);
    }
    return longest;
}

int main()
{
    {
        std::string str = "ABAB";
        std::cout << LongestRepeatAtMostKReplaces(str, 2) << "\n";  // 4
    }
    {
        std::string str = "AABABBA";
        std::cout << LongestRepeatAtMostKReplaces(str, 1) << "\n";  // 4
    }
}
