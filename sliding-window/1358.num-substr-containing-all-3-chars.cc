/*
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb".

Example 3:

Input: s = "abc"
Output: 1



Constraints:

    3 <= s.length <= 5 x 10^4
    s only consists of a, b or c characters.

*/

#include "utils.h"

int NumOfSubstr(const std::string& s)
{
    int freqs[3] = { 1, 1, 1 };
    int match = 0;
    int cnt = 0;
    int beg = 0;
    for (int i = 0; i < s.size(); i++) {
        if (--freqs[s[i] - 'a'] == 0) {
            match++;
        }
        while (match >= 3) {
            cnt += (s.size() - i);  // all substrs starting from this `beg`
            // shrink left ?
            ++freqs[s[beg] - 'a'];
            if (freqs[s[beg] - 'a'] == 1) {
                match--;
            }
            beg++;
        }
    }
    return cnt;
}

int main()
{
    {
        std::string s = "abcabc";
        std::cout << NumOfSubstr(s) << "\n";  // 10
    }
    {
        std::string s = "aaacb";
        std::cout << NumOfSubstr(s) << "\n";  // 3
    }
    {
        std::string s = "abc";
        std::cout << NumOfSubstr(s) << "\n";  // 1
    }
}

/* anothe simpler solution
    int numberOfSubstrings(string s) {
        int count[3] = {0, 0, 0},res = 0 , i = 0, n = s.length();
        for (int j = 0; j < n; ++j) {
            ++count[s[j] - 'a'];
            // if shrink i, still match, then shrink times will be added to res
            // means how many substr matches ending with this 'j'
            while (count[0] && count[1] && count[2])
                --count[s[i++] - 'a'];
            res += i;
        }
        return res;
    }
*/
