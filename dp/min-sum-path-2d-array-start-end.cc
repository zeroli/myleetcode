/*
给定一个2维数组，数组元素都是正整数
从左上角走到右下角，只能向右或者向下走，到达右下角的路径中加和最小

*/

#include "utils.h"

/*
把m * n个格子想象成图的节点，那么题目就变成了求解从一个节点到另一个节点的最短路径。
经典解法就是dfs递归遍历算法+memo

但是我们可以采用从右下角反推到左上角，采用dp迭代的方式。
定义dp[i][j]为格子(i,j)到右下角的所有路径中最小加和，那么递推公式就是：
dp[i][j] = min(dp[i][j+1], dp[i+1][j]) + grid[i][j]
意思是说(i,j)，可以从右边格子和正下格子推出来。
起点就是(m-1, n-1)，右下角格子
*/

int MinPath(const Array2D_t<int>& grid)
{
    int m = grid.size(), n = grid[0].size();
    Array2D_t<int> dp(m, std::vector<int>(n, 0));
    dp[m-1][n-1] = grid[m-1][n-1];

    // 最后一列
    for (int i = m - 2; i >= 0; i--) {
        dp[i][n-1] = dp[i+1][n-1] + grid[i][n-1];
    }
    // 最后一行
    for (int i = n - 2; i >= 0; i--) {
        dp[m-1][i] = dp[m-1][i+1] + grid[m-1][i];
    }

    for (int i = m - 2; i >= 0; i--) {
        for (int j = n - 2; j >= 0; j--) {
            dp[i][j] = std::min(dp[i][j+1], dp[i+1][j]) + grid[i][j];
        }
    }
    return dp[0][0];
}

int MinPath1(const Array2D_t<int>& grid)
{
    int m = grid.size(), n = grid[0].size();
    // 补一个INT_MAX，方便后面越界时，可以访问而且不起作用
    std::vector<int> dp(n+1, INT_MAX);
    dp[n-1] = 0;
    // dp: MAX, MAX, 0, MAX
    //       3, 6, 5
    // dp: 14, 11, 5, MAX
    //       2, 1, 4
    // dp:  12(10 <14), 10 (9<11), 9 (5 < MAX)
    //       1, 2, 2
    // dp:  13(12=12), 12 (10<11), 11 (9<10)
    // dp[0]: 13

    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            dp[j] = std::min(dp[j], dp[j+1]) + grid[i][j];
        }
    }
    return dp[0];
}

int main()
{
    Array2D_t<int> grid = {
        { 1, 2, 2 },
        { 2, 1, 4 },
        { 3, 6, 5 }
    };
    std::cout << MinPath(grid) << "\n";  // 13
    std::cout << MinPath1(grid) << "\n";  // 13
}
