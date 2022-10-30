#include "utils.h"

// 最大子数组和，数组元素包括正数和负数
std::vector<int> MaxSubArray(const std::vector<int>& arr)
{
    int n = arr.size();
    // 元素类型：起始位置索引和累加和
    // dp[i]定义为以索引i结尾的元素最大的连续子数组
    std::vector<std::pair<int, int>> dp(n);
    int maxSum = arr[0];
    int start, end;
    for (int i = 1; i < n; i++) {
        // 当前有2种选择：
        // 要么将这个数加入到前面的子数组中
        // 要么单独作为一个子数组的开头
        // 最后选择哪一种要看累加和哪个更大
        int tmp = dp[i-1].second + arr[i];
        if (tmp > arr[i]) {
            dp[i].first = dp[i-1].first;
            dp[i].second = tmp;
        } else {
            dp[i].first = i;
            dp[i].second = arr[i];
        }
        if (dp[i].second > maxSum) {
            maxSum = dp[i].second;
            start = dp[i].first;
            end = i;
        }
        // 如果只求最大子数组和
        // dp[i] = std::max(dp[i-1] + arr[i], arr[i]);
        // maxSum = std::max(maxSum, dp[i]);
    }
    std::cout << "max subarray sum: " << maxSum << "\n";
    return std::vector<int>(arr.begin() + start, arr.begin() + end + 1);
}

int MaxSubArray1(const std::vector<int>& arr)
{
    int sum = 0;
    int maxSum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];
        // 如果前面累加和变成了负数，最好不要将当前数加入前面子数组中
        // 让其单独成为一个子数组得开头
        if (sum < 0) {
            sum = 0;
        }
        maxSum = std::max(maxSum, sum);
    }
    return maxSum;
}

int main()
{
    std::vector<int> arr = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    std::cout << MaxSubArray(arr) << "\n"; // 6
    std::cout << MaxSubArray1(arr) << "\n";  // 6
}
