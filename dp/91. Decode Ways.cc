#include "utils.h"

/*
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26

Given a non-empty string containing only digits,
determine the total number of ways to decode it.
 The answer is guaranteed to fit in a 32-bit integer.
*/

int DecodeWays(const std::string& str)
{
    int n = str.size();
    if (str[0] == '0') {
        return 0;
    }
    // 定义dp[i]为长度为i的子字符串对应的解码方法个数
    std::vector<int> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;  //  长度为1的字符串解码为1
    for (int i = 2; i <= n; i++) {
        // str[i-1]为长度为i的字符串的最后字符
        if (str[i - 1] != '0') {  // 自己单独解码
            dp[i] += dp[i-1];
        }
        if (str[i - 2] != '0') {  // 与前面字符组合解码
            int x = (str[i - 2] - '0') * 10 + (str[i - 1] - '0');
            if (x <= 26) {
                dp[i] += dp[i-2];
            }
        }
        if (dp[i] == 0) {  // 无法解码，终止
            return 0;
        }
    }
    return dp[n];
}

int main()
{
    {
        std::string str = "12203";
        std::cout << DecodeWays(str) << "\n";  // 2
    }
    {
        std::string str = "20103";
        std::cout << DecodeWays(str) << "\n";  // 1
    }
    {
        std::string str = "2030";
        std::cout << DecodeWays(str) << "\n";  // 0
    }
}
