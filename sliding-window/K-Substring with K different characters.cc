#include "utils.h"

/*
Given a string S and an integer K.
Calculate the number of substrings of length K and containing K different characters

String: "abcabc"
K: 3

Answer: 3
substrings:  ["abc", "bca", "cab"]

String: "abacab"
K: 3

Answer: 2
substrings: ["bac", "cab"]
*/

int KSubstr(const std::string& str, int k)
{
    int n = str.size();
    int start = 0;
    std::map<char, int> freqs;
    std::set<std::string> sets;
    for (int i = 0; i < n; i++) {
        freqs[str[i]]++;
        int len = i - start + 1;
        // 维护一个长度为K的窗口
        while (len > k) {
            if (--freqs[str[start]] == 0) {
                freqs.erase(str[start]);
            }
            start++;
            len--;
        }
        // 判断这个窗口是否符合要求
        if (freqs.size() == k && len == k) {
            sets.insert(str.substr(start, i - start + 1));
        }
    }
    return sets.size();
}

int main()
{
    {
        std::string str = "abcabc";
        int k = 3;
        std::cout << KSubstr(str, k) << "\n";
    }
    {
        std::string str = "abacab";
        int k = 3;
        std::cout << KSubstr(str, k) << "\n";
    }
}
