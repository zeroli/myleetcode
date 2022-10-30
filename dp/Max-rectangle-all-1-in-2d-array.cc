/*
Given a 2D binary matrix filled with 0’s and 1’s,
find the largest rectangle containing all ones and return
its area
*/

#include "utils.h"

/*
0 1 1 0
1 1 1 1
1 1 1 1
1 1 0 0

此题可以理解为每多看一行，就形成一个新的柱状图
求柱状图的最大矩形面试，我们之前解决过
*/

int MaxRectInHist(const std::vector<int>& hist)
{
    // 单调递增栈，因为对于一个位置，如果后面比它大，
    // 它暂时不用计算，一旦碰到一个比当前小的位置，就需要将它推出栈顶
    // 然后计算，比它小的位置，不一定是紧接着它的那一个
    // 单调递增栈，记录位置
    std::stack<int> stk;
    int maxRect = 0;
    int n = hist.size();
    for (int i = 0; i <= n; i++) {
        // 碰到一个比当前栈顶小的数，得开始推出栈顶元素进行处理
        int curVal = i < n ? hist[i] : -1;  // 比所有值都小的值触发栈中元素进行处理
        while (!stk.empty() && hist[stk.top()] > curVal) {
            int cur = stk.top();
            int height = hist[cur];
            stk.pop();
            // 以cur位置到i位置，期间应该都大于cur位置
            // 在cur位置左边的，应该都小于cur位置的值
            // 但是在以前push(cur)之前，我们已经把所有大于`cur`
            // 全部处理掉了(弹出栈了)，换句话说栈上cur左边的位置
            // 不一定就是cur的左手边的index
            // 所以我们需要计算cur位置左右两边的跨度
            // 左边达到去掉cur之后的新的栈顶位置，右边就是i了，excluding both
            if (stk.empty()) {
                int dist = i - 0;  // 想象i就在cur右边，dist就为1
                maxRect = std::max(maxRect, height * dist);
            } else {
                int dist = i - stk.top() - 1;
                maxRect = std::max(maxRect, height * dist);
            }
        }
        stk.push(i);  // 压入位置，之后栈顶对应的值就是最大值了
    }
    // 如果元素是排好序的，最后没有一个小的数触发上面的计算

    return maxRect;
}

int MaxRectArea(Array2D_t<int>& arr2d)
{
    int m = arr2d.size(), n = arr2d[0].size();
    int maxArea = MaxRectInHist(arr2d[0]);
    std::cout << "0: " << maxArea << "\n";
    for (int i = 1; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr2d[i][j] == 1) {
                arr2d[i][j] += arr2d[i-1][j];  // 累加上面行的累计结果
            }
        }
        maxArea = std::max(maxArea, MaxRectInHist(arr2d[i]));
        std::cout << i << ": " << maxArea << "\n";
    }
    return maxArea;
}

int MaxRectArea0(const Array2D_t<int>& arr2d)
{
    int m = arr2d.size(), n = arr2d[0].size();
    std::vector<std::vector<int>> dp(m+1,
        std::vector<int>(n+1, 0));
    int result = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr2d[i-1][j-1] == 0) {
                dp[i][j] = 0;
            } else {
                auto A = dp[i-1][j-1];
                auto B = dp[i-1][j];
                auto C = dp[i][j-1];
                if (B > 0 && C > 0) {
                    dp[i][j] = B + C - A + 1;
                } else if (B > 0) {
                    dp[i][j] = B + 1;
                } else if (C > 0) {
                    dp[i][j] = C + 1;
                }
            }
            result = std::max(result, dp[i][j]);
        }
    }
    return result;
}

int main()
{
    {
        Array2D_t<int> arr2d = {
            { 1, 0, 0, 1 },
            { 0, 1, 1, 1 },
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 },
        };
        std::cout << MaxRectArea(arr2d) << "\n";
    }
}
