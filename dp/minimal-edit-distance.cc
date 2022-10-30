#include "utils.h"

// 从一个字符串变到另一个字符串的最小编辑距离
// 插入，删除，替换，每个的花销都是1
int MinimalEditDist(const std::string& str1, const std::string& str2)
{
    int m = str1.size();
    int n = str2.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));
    // 从空的str1变到部分str2的花销就是部分str2的长度，不断插入
    for (int i = 0; i <= n; i++) {
        dp[0][i] = i;
    }
    // 从部分str1变到空的str2的花销就是部分str1的长度，不断删除
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];  // 没有编辑距离，两个字符相等
            } else {
                dp[i][j] = std::min(std::min(
                    dp[i-1][j],  // 删除str1[i-1]字符
                    dp[i][j-1]  // 插入一个匹配str2[j-1]的字符
                ), dp[i-1][j-1]  // 替换str1[i-1]成为str2[j-1]字符
                ) + 1;
            }
        }
    }
    return dp[m][n];
}

// 降维到1维
int MinimalEditDist1(const std::string& str1, const std::string& str2)
{
    int m = str1.size(), n = str2.size();
    std::vector<int> dp(n+1, 0);
    int tmp1 = 1;  // 从空的str2变成1字符长度的str1，只要一步插入
    // 从空的str1变成任意长度的str2，需要相应的字符插入
    for (int i = 0; i <= n; i++) {
        dp[i] = i;
    }
    // 纵轴(行)为str1, 横轴(列)为str2
    for (int i = 1; i <= m; i++) {
        /*
           dp[j-1]   dp[j]       => (old_tmp1) dp[j]
                     \     |
           tmp1 -->(cost)                          (tmp1)
        */
        for (int j = 1; j <= n; j++) {
            int cost = 0;
            if (str1[i-1] == str2[j-1]) {
                cost = dp[j-1];
            } else {
                cost = std::min({dp[j-1], dp[j], tmp1}) + 1;
            }
            dp[j-1] = tmp1;
            tmp1 = cost;
        }
        dp[n] = tmp1;
    }
    return dp[n];
}

int main()
{
    {
        std::string str1 = "abbc";
        std::string str2 = "babb";
        std::cout << MinimalEditDist(str1, str2) << "\n";  // 2
        std::cout << MinimalEditDist1(str1, str2) << "\n";  // 2
        // 先插入b，再删除c
    }
}
