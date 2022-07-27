#include "utils.h"

int TrapRainWather1(const std::vector<int>& arr)
{
    std::vector<int> left_max(arr.size(), 0);
    left_max[0] = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        left_max[i] = std::max(left_max[i-1], arr[i]);
    }
    std::vector<int> right_max(arr.size(), 0);
    right_max[arr.size()-1] = arr.back();
    for (int i = (int)arr.size() - 2; i >= 0; i--) {
        right_max[i] = std::max(right_max[i+1], arr[i]);
    }

    int water = 0;
    for (int i = 1; i < (int)arr.size() - 1; i++) {
        int top = std::min(left_max[i-1], right_max[i+1]);
        if (top > arr[i]) {
            water += (top - arr[i]);
        }
    }
    return water;
}

int TrapRainWather2(const std::vector<int>& arr)
{
    int water = 0;
    int left_max = 0, right_max = 0;
    int left = 0, right = arr.size() - 1;
    // 这里是left < right
    while (left < right) {
        left_max = std::max(left_max, arr[left]);
        right_max = std::max(right_max, arr[right]);
        // 我们只关心两者的最小值，而不关心最大值
        // 也就是说right右边当前发现的最大值是不是left右边最大值不重要
        if (left_max < right_max) {
            water += left_max - arr[left];
            left++;
        } else {
            water += right_max - arr[right];
            right--;
        }
        #if 0
        if (arr[left] < arr[right]) {
            if (arr[left] > left_max) {
                left_max = arr[left];
            } else {
                water += left_max - arr[left];
            }
            left++;
        } else {
            if (arr[right] > right_max) {
                right_max = arr[right];
            } else {
                water += right_max - arr[right];
            }
            right--;
        }
        #endif
    }
    return water;
}

int TrapRainWather(const std::vector<int>& arr)
{
    int water = 0;
    std::stack<int> stk;
    for (int i = 0; i < arr.size(); i++) {
        // monotanic stack in descending order
        // when meeting a bigger one, we need calculate the trapped water at that top
        //           == (new arr[i])
        // ==                              ==> stk.top after pop below
        //      == stack top
        //
        while (!stk.empty() && arr[stk.top()] < arr[i]) {
            int cur = arr[stk.top()];
            stk.pop();
            if (stk.empty()) {
                break;
            }
            water += (std::min(arr[stk.top()], arr[i]) - cur) * (i - stk.top() - 1);
        }
        stk.push(i);
    }

    return water;
}

int main()
{
    {
        std::vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
        std::cout << TrapRainWather2(arr) << "\n";  // 6
    }
}
