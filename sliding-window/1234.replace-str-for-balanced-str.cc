/*
1234. Replace the Substring for Balanced String

You are given a string s of length n containing only four kinds of characters: 'Q', 'W', 'E', and 'R'.

A string is said to be balanced if each of its characters appears n / 4 times where n is the length of the string.

Return the minimum length of the substring that can be replaced with any other string of the same length to make s balanced.
 If s is already balanced, return 0.

Example 1:

Input: s = "QWER"
Output: 0
Explanation: s is already balanced.

Example 2:

Input: s = "QQWE"
Output: 1
Explanation: We need to replace a 'Q' to 'R', so that "RQWE" (or "QRWE") is balanced.

Example 3:

Input: s = "QQQW"
Output: 2
Explanation: We can replace the first "QQ" to "ER".

Constraints:

    n == s.length
    4 <= n <= 105
    n is a multiple of 4.
    s contains only 'Q', 'W', 'E', and 'R'.

*/

#include "utils.h"

int MinWindow(const std::string& s)
{
    std::unordered_map<char, int> freqs;
    for (auto&& c : s) {
        freqs[c]++;
    }

    int n = s.size();
    int k = n / 4;

    int beg = 0;
    int len = INT_MAX;
    for (int j = 0; j < n; j++) {
        freqs[s[j]]--;

        // we decrement one char's freq by erasing this char (to change it to any other)
        // then it might trigger balanced string (someone less than k, could take this increment)
        while (beg < n &&
            freqs['Q'] <= k && freqs['W'] <= k && freqs['E'] <= k && freqs['R'] <= k)
        {
            len = std::min(len, j - beg + 1);
            ++freqs[s[beg]];
            beg++;
        }
    }
    return len;
}

int main()
{
    {
        std::string s = "QWER";
        std::cout << MinWindow(s) << "\n";  // 0
    }
    {
        std::string s = "QQWE";
        std::cout << MinWindow(s) << "\n";  // 1
    }
    {
        std::string s = "QQQW";
        std::cout << MinWindow(s) << "\n";  // 2
    }
}
