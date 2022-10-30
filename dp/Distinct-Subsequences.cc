/*
Given a string S and a string T, count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can
be none) of the characters without disturbing the relative positions of the remaining characters.
 (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example: S = "rabbbit", T = "rabbit"
Return 3.
*/
#include "utils.h"

/*
这题类似于字符串编辑题目，不过这里只有一种操作就是从s中删除
定义dp[i][j]为长度i的S，长度j的T，T为S的subsequence的个数
dp[i][j]分两种情况来推导：
1. 如果S[i] != T[j]，肯定删除S[i]，dp[i][j] = dp[i-1][j] 之问题就是i-1长度S, j长度T
2. 如果S[i] == T[j]，注意这里有两种选择，要么是去除S[i], T[j]，因为他们相等
另外一种选择，就是不考虑S[i](删除S[i]), 子问题变成i-1长度S, 仍然长度j的T
dp[i][j] = dp[i-1][j] + dp[i-1][j-1]

降维到1维，需要从右到左遍历T，从而可以覆盖dp[i]
dp[i] += (S[i-1] == T[j-1] ? dp[i-1] : 0);  // 不等时，dp[i]不动
下一轮i--, looping T
*/

int SubseqNum(const std::string& s, const std::string& t)
{
    int n1 = s.size(), n2 = t.size();
    std::vector<int> dp(n2+1, 0);
    dp[0] = 1; // 都为空时，subseq number就是1
    for (int i = 1; i <= n1; i++) {
        for (int j = n2; j > 0; j--) {
            dp[j] += (s[i-1] == t[j-1] ? dp[j-1] : 0);
        }
    }
    return dp[n2];
}

int main()
{
    std::string s = "rabbbit", t = "rabbit";
    std::cout << SubseqNum(s, t) << "\n";  // 3
}
