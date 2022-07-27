#include "utils.h"

/*
You are given an array of integers arr where each element represents the height of a bar in a histogram.
 The bars are placed in the exact same sequence as given in the array.
You need to find the area of the largest rectangle found in the histogram.
Input: [2, 4, 8, 10, 8, 4, 2]
Output: 24
*/

/* 最暴力的方法就是针对每一个数组元素，
 * 计算它左边第一个小于它的位置，同时计算它右边第一个小于它的位置
 * 形成一个以它为中心和底的U型凹槽，这样可以计算矩形面积
 * 但是如何快速计算左右第一个小于它的位置呢？
 * 可以这样考虑，当到达左/右第一小于它的位置前，那些元素都比它要大
 * 如果以一个栈来记录从左第一个小于它的位置到它当前的元素，
 * 而且以递增的方式来记录元素，当达到当前元素时，那些比它大的元素
 * 都可以不断的从栈中弹出来，一直到比它小时，停止弹出。
 * 这样我们就可以压入当前元素到栈中，栈中前一个元素就是左边第一个
 * 比它小的元素（从自己开始往左遍历），而且栈中元素仍然保持递增顺序
 * 直到碰到右边（从自己开始往右遍历）第一个比它小的数。那时也会弹出
 * 比那个元素大的栈中之前的元素。此时对于之前那个元素来说，
 * 想要的3个元素都直到了
 *   1）左边第一个比它小的，现在栈中就是它前一个
 *   2）自己，当前栈顶top
 *   3）右边第一个比它小的，现在被评估的数，i对应的元素
 * 有了这3个位置，就可以计算以top元素为中心的U型所形成的矩形面积了。
 */
int LargestRectArea(const std::vector<int>& arr)
{
    int n = arr.size();
    int maxArea = 0;
    std::stack<int> stk;
    // monotanic stack in ascending order

    for (int i = 0; i <= n; i++) {
        int cur = i < n ? arr[i] : INT_MIN;
        while (!stk.empty() && arr[stk.top()] > arr[i])
        {
            int h = arr[stk.top()];
            stk.pop();
            int dist = 0;
            if (stk.empty()) {
                dist = i;
            } else {
                dist = (i - stk.top() - 1);
            }
            maxArea = std::max(maxArea, h * dist);
        }
        stk.push(i);
    }
    return maxArea;
}

int main()
{
    {
        std::vector<int> arr = { 2, 4, 8, 10, 8, 4, 2 };
        std::cout << LargestRectArea(arr) << "\n";  // 24
    }
    {
        std::vector<int> arr = { 1, 2, 3 };
        std::cout << LargestRectArea(arr) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 3, 2, 1 };
        std::cout << LargestRectArea(arr) << "\n";  // 4
    }
}
