/*
{0, 1, 1, 0, 1},
{1, 1, 0, 1, 0},
{0, 1, 1, 1, 0},
{1, 1, 1, 1, 0},
{1, 1, 1, 1, 1},
{0, 0, 0, 0, 0}};

最大的正方形，里面全是1
*/

#include "utils.h"

/*
定义dp[i][j]为以(i,j)为右下角的最大全是1的正方形的边长
它可以从它周围的3个方格推导出来
(i-1, j-1)  (i-1, j)
(i, j-1)     (i, j)
怎么推导呢？
以周围3个方格的最小边长，然后加1??? 怎么理解
*/

Array2D_t<int> MaxSquareAllOne(const Array2D_t<int>& arr2d)
{
    int m = arr2d.size(), n = arr2d[0].size();
    Array2D_t<int> dp(m, std::vector<int>(n, 0));
    // 第一行
    for (int i = 0; i < n; i++) {
        dp[0][i] = arr2d[0][i];  // 要么是0，要么是1
    }
    // 第一列
    for (int i = 0; i < m; i++) {
        dp[i][0] = arr2d[i][0];  // 要么是0，要么是1
    }

    int maxSquareLen = 0;
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (arr2d[i][j] == 0) {
                dp[i][j] = 0;
            } else {
                // 3者最小的边长
                dp[i][j] = std::min({
                    dp[i-1][j-1],
                    dp[i][j-1],
                    dp[i-1][j]
                }) + 1;
            }
            maxSquareLen = std::max(maxSquareLen, dp[i][j]);
        }
    }
    std::cout << "maxSquareLen: " << maxSquareLen << "\n";

    maxSquareLen = 0;
    int max_i = 0, max_j = 0;
    Array2D_t<int> maxSquare;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] > maxSquareLen) {
                maxSquareLen = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }
    for (int i = max_i - maxSquareLen + 1; i <= max_i; i++) {
        maxSquare.push_back({});
        for (int j = max_j - maxSquareLen + 1; j <= max_j; j++) {
            maxSquare.back().push_back(arr2d[i][j]);
        }
    }
    return maxSquare;
}

int main()
{
    Array2D_t<int> arr2d = {
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
    };
    std::cout << MaxSquareAllOne(arr2d) << "\n";
}
