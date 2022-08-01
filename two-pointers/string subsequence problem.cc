#include "utils.h"

// 判断一个字符串是否为另一个字符串的子序列

// 双指针方法，时间复杂度为O(m+n)
bool IsSubseq(const std::string& s, const std::string& t)
{
    int n = t.size();
    int m = s.size();
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == s[j]) {
            ++j;  // 找到一个匹配字符，递增，检查下一个字符
            // 一旦找到所有匹配的字符，返回true
            if (j == m) return true;
        }
    }
    return false;
}

// 也可以用动态规划的方法来解决，不过时间复杂度为O(m*n)，空间复杂度也为O(m*n)
bool IsSubseq2(const std::string& s, const std::string& t)
{
    int n = t.size();
    int m = s.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));
    // dp[i][j]代表以`i-1`为结尾的s中字符串和以`j-1`为结尾的t中字符串对应的相同字符序列长度
    // 有两种情况需要考虑，当要从dp[i-1][j-1]推导dp[i][j]时：
    // 1) 如果s[i] == t[j]，则dp[i][j] = dp[i-1][j-1] + 1
    // 2) 如果s[i] != t[j]，则dp[i][j] = dp[i][j-1]  (删除/不考虑t当前这个字符)
    // 如何初始化dp数组呢？
    // 任何一个字符串长度为0，则相同子序列长度为0
    // 也就是说所有的dp[0][j]和dp[i][0] = 0
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i] == t[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[m][n] == m;
}

int main()
{
    {
        std::string s = "abc";
        std::string t = "ahbgdc";
        std::cout << std::boolalpha << IsSubseq(s, t) << "\n";  // true
    }
    {
        std::string s = "abc";
        std::string t = "ahbgdc";
        std::cout << std::boolalpha << IsSubseq2(s, t) << "\n";  // true
    }
}
