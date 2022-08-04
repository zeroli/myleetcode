#include "utils.h"

/*
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
你需要让组成和的完全平方数的个数最少。

示例 1:

输入: n = 12
输出: 3
解释: 12 = 4 + 4 + 4.
示例 2:

输入: n = 13
输出: 2
解释: 13 = 4 + 9.
*/

/*
这题可以采用暴力穷举+memo的方式
对于一个数n，从1开始，进行尝试，用n减去这个尝试的数的平方，
剩下的数，再递归判断，还是从1开始，一直到它的平方到n
memo记住数n对应的完全平方数的最少个数
*/

using Memo_t = std::map<int, int>;
// 返回n作为根节点时，它的所有子树的最小层数
int Backtracking(int n, Memo_t& memo)
{
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }
    if (n == 0) {
        return 0;
    }

    int min = n;
    for (int i = 1; i * i <= n; i++) {
        // 子树的层数加上一层，就是以当前节点作为根节点的数的最小层数
        min = std::min(min, Backtracking(n - i * i, memo) + 1);
    }
    memo[n] = min;
    return min;
}

int PerfectSquare(int n)
{
    Memo_t memo;
    return Backtracking(n, memo);
}

// 这题可以采用DP迭代的方式来实现
int PerfectSquare1(int n)
{
    std::vector<int> dp(n+1);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int max = INT_MAX;
        for (int j = 1; j * j <= i; j++) {
            max = std::min(max, dp[i - j * j] + 1);
        }
        dp[i] = max;
    }
    return dp[n];
}

int main()
{
    {
        std::cout << PerfectSquare(12) << "\n";
        std::cout << PerfectSquare1(12) << "\n";
    }
    {
        std::cout << PerfectSquare(13) << "\n";
        std::cout << PerfectSquare1(13) << "\n";
    }
}
