#include "utils.h"

int PalindromeSubstrCutNum(const std::string& str)
{
    int cnt = 0;
    std::vector<int> cuts(str.size());
    std::vector<std::vector<bool>> dp
        (str.size(), std::vector<bool>(str.size(), false));
    // dp[i][j] = true/false for substr[i,j] is palindrome
    // if str[i] == str[j]:
    //   dp[i][j] = true if dp[i+1][j-1] (or dp[i+1][j-1])
    //   dp[i][j] = true if i - j <= 1 (only one char, or 2 same chars)
    for (int j = 0; j < str.size(); j++) {
        int minCut = j;
        for (int i = j; i >= 0; i--) {  // j is on right of i
            if (str[i] == str[j]) {
                if (j - i <= 1 || dp[i+1][j-1]) {  // here i+1, is done for substr ending at j-1
                    dp[i][j] = true;
                    // prefix str[0, i-1] has min cut, then we need add one more cut at i
                    // since str[i...j] are one more palindrome
                    // i == 0, then no need cut, this time
                    minCut = std::min(minCut, (i == 0) ? 0 : (cuts[i-1] + 1));
                }
            }
        }
        cuts[j] = minCut;
    }
    return cuts[str.size()-1];
}

int main()
{
    {
        std::string str = "aba";
        std::cout << PalindromeSubstrCutNum(str) << "\n";  // 0
    }
    {
        std::string str = "aab";
        std::cout << PalindromeSubstrCutNum(str) << "\n";  // 1
    }
    {
        std::string str = "ababbbabbababa";
        std::cout << PalindromeSubstrCutNum(str) << "\n";  // 3
    }
}
