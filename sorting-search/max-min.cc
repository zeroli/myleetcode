#include "utils.h"

// 时间复杂度为O(3n/2)的算法求得max/min
std::pair<int, int> MaxMin(const std::vector<int>& arr)
{
    int n = arr.size();
    if (n == 2) {
        return { std::max(arr[0], arr[1]), std::min(arr[0], arr[1]) };
    }
    if (n == 1) {
        return { arr[0], arr[0] };
    }

    // 每2个元素一起比较，从而求得最大最小
    int max = std::max(arr[0], arr[1]);
    int min = std::min(arr[0], arr[1]);
    int i = 2;
    for (i = 2; i < n - 1; i += 2) {
        // 每次进行了3次比较，共有n/2次
        if (arr[i] > arr[i + 1]) {
            max = std::max(max, arr[i]);
            min = std::min(min, arr[i + 1]);
        } else {
            max = std::max(max, arr[i + 1]);
            min = std::min(min, arr[i]);
        }
    }
    if (i < n) {
        max = std::max(max, arr[i]);
        min = std::min(min, arr[i]);
    }
    return { max, min };
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
        std::cout << MaxMin(arr) << "\n";
    }
}
