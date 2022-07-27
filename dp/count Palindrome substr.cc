#include "utils.h"

int PalindromeSubstrNum(const std::string& str)
{
    int cnt = 0;
    std::vector<std::vector<bool>> dp
        (str.size(), std::vector<bool>(str.size(), false));
    // dp[i][j] = true/false for substr[i,j] is palindrome
    // if str[i] == str[j]:
    //   dp[i][j] = true if dp[i+1][j-1] (or dp[i+1][j-1])
    //   dp[i][j] = true if i - j <= 1 (only one char, or 2 same chars)
    for (int i = str.size() - 1; i >= 0; i--) {
        for (int j = i; j < str.size(); j++) {  // j is on right of i
            if (str[i] == str[j]) {
                if (j - i <= 1) {
                    cnt++;
                    dp[i][j] = true;
                } else if (dp[i+1][j-1]) {
                    cnt++;
                    dp[i][j] = true;
                }
            }
        }
    }
    return cnt;
}

int main()
{
    {
        std::string str = "aaa";
        std::cout << PalindromeSubstrNum(str) << "\n";
        // a, a, a, aa, aa, aaa
    }
}
