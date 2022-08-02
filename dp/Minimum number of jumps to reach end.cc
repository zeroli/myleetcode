#include "utils.h"

/*
Given an array of non-negative integers arr[] of length n,
 where each element represents the max number of steps that can be made forward from that element.
 You are initially positioned at the first index of the array.
 Write a program to return the minimum number of jumps to reach the last index of the array.

Problem Note

    If it is not possible to reach the last index, return -1.
    If an element is 0, then you cannot move through that element.
*/

int MinJumps(const std::vector<int>& arr)
{
    int n = arr.size();
    // 这里dp[i]代表的是从位置`i`跳到最后的位置所需的最小步数
    // 因为本题要求从位置0跳到最后的位置所需要的最小步数，也即dp[0]
    // dp数组初始化为最大，在迭代过程中不断求每个位置的最小值
    std::vector<int> dp(n, INT_MAX);
    // 最后一个位置跳到最后位置，所需步数为0
    dp[n-1] = 0;  // last position going to last position will take 0 step
    // 从中间某一个位置跳到最后位置，需要后面位置的辅助，
    // 当然它也可以一步跳到最后，如果它可以的话。
    // 根据当前位置能够跳跃的能力，它可以选择一次跳1步，也可以一次跳2步，
    // 直到最大的跳跃，每次跳跃记为1次跳跃。
    // 从i位置跳1次到j位置 (j > i，同时j - i <= arr[i])，arr[i]代表这个位置的跳跃能力
    // 根据之前求解的j位置可以跳到最后位置的最小跳跃数，再加上此次从i一次跳到j位置
    // 对整个1...arr[i]所有可选的跳跃方式，求解此位置可跳到最后位置的跳跃数最小值，记为dp[i]
    for (int i = n - 1; i >= 0; i--) {
        // for this location, take 1, up to arr[i] steps to next position, try them
        // to see which one has minimum steps
        for (int j = 1; j <= arr[i]; j++) {
            if (i + j < n) {
                dp[i] = std::min(dp[i], dp[i + j] + 1);
                std::cout << i << ", " << j << ":" << dp << "\n";
            }
        }
    }
    return dp[0] == INT_MAX ? -1 : dp[0];
}

int main()
{
    {
        std::vector<int> arr = { 2, 1, 1 };
        std::cout << MinJumps(arr) << "\n";  // 1
    }
    {
        std::vector<int> arr = { 2, 3, 2, 4, 4 };
        std::cout << MinJumps(arr) << "\n";  // 2
    }
}
