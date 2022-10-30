/*
Given a triangle, find the minimum path sum from top to bottom.
Each step you may move to adjacent numbers on the row below.
For example, given the following triangle
{
{2},
{3,4},
{6,5,7},
{4,1,8,3}
}
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
Note: Bonus point if you are able to do this using only O(n) extra space,
where n is the total number of rows in the triangle
*/

#include "utils.h"

/*
此题第一眼就是可以利用DFS来递归求解从顶点到最底一行元素的路径和，从上到下，
递归终止条件就是到底最下一行元素，但是时间复杂度会比较高O(2^n)
因为这棵树类似于二叉树，遍历完所有节点就会有1+2+4+8+...=O(2^n) (n为triangle的高度)

不过我们发现在遍历过程中，其实有很多节点被重复遍历，譬如3->5, 4->5，5被遍历了两次。
因此可以利用递归+memo的方式来减少计算量。
递归是从上到下，可以利用dp从下到上，从最底层开始遍历，最后都遍历到最顶层一个节点
定义dp{i}{j}为第i行第j列节点时，从下到上遍历最小累加和。
它可以从下面两个节点来变换过来: dp{i+1}{j}, dp{i+1}{j+1}，取最小值
dp{i}{j} = min(dp{i+1}{j}, dp{i+1}{j+1}) + tri{i}{j}
i/j，从m-1/n-1开始遍历，也就是最后一行，最后一列，遍历到(0, 0)

    {i, j}
     /|\  \
      |     \
{i+1,j} {i+1,j+1}
*/

int MinPathTopDown0(const Array2D_t<int>& tri)
{
    int m = tri.size(), n = tri.back().size();
    Array2D_t<int> dp(m, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        dp[m-1][i] = tri[m-1][i];
    }
    for (int i = m-2; i >= 0; i--) {
        for (int j = i; j >= 0; j--) {  // 注意，j从i开始，斜对角线处
            dp[i][j] = std::min(dp[i+1][j], dp[i+1][j+1]) + tri[i][j];
        }
    }
    return dp[0][0];
}

// 降维到1D，减少空间复杂度
int MinPathTopDown(const Array2D_t<int>& tri)
{
    int m = tri.size(), n = tri.back().size();
    std::vector<int> dp(n, 0);
    for (int i = 0; i < n; i++) {
        dp[i] = tri[m-1][i];
    }
    for (int i = m-2; i >= 0; i--) {
        int tmp1 = dp[i+1];
        int tmp2 = 0;
        for (int j = i; j >= 0; j--) {  // 注意，j从i开始，斜对角线处
            // 不能直接overwrite dp[j]，因为它下一轮迭代需要它的原始值
            // 所需要保存到tmp变量中。
            // 在下一轮迭代用完之后，那时候需要将tmp值写到那里，
            // 注意下一轮迭代时，索引是j+1
            // dp[j] = std::min(dp[j], dp[j+1]) + tri[i][j];
            tmp2 = std::min(dp[j], dp[j+1]) + tri[i][j];
            dp[j+1] = tmp1;
            tmp1 = tmp2;  // 保存到tmp1中，下一轮迭代后会更新dp值
        }
        dp[0] = tmp1;
    }
    return dp[0];
}

int main()
{
    {
        Array2D_t<int> tri = {
            {2},
            {3,4},
            {6,5,7},
            {4,1,8,3}
        };
        std::cout << MinPathTopDown(tri) << "\n";  // 11
    }
}
