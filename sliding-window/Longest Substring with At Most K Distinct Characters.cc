#include "utils.h"

/*
Given a string s, find the length of the longest substring T that
contains at most k distinct characters.

For example, Given s = "eceba", k = 3,
T is "eceb" which its length is 4
*/

std::string LongestSubstrAtMostK(const std::string& str, int k)
{
    int n = str.size();
    int start = 0;
    int longest = 0;
    std::string res;
    std::map<char, int> freqs;
    for (int i = 0; i < n; i++) {
        freqs[str[i]]++;
        // 当有不同的字符过来时，我们就需要收缩窗口，
        // 使其窗口内的不同字符个数重新小于等于k
        while (freqs.size() > k) {
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            start++;
        }
        if (longest < i - start + 1) {
            longest = i - start + 1;
            res = str.substr(start, longest);
        }
    }
    return res;
}

int main()
{
    {
        std::string str = "eceba";
        std::cout << LongestSubstrAtMostK(str, 3) << "\n";
    }
}
