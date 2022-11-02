/*
找到min/max，从一个数组中，一次性
*/

#include "utils.h"

std::pair<int, int> FindMinMax(const std::vector<int>& arr)
{
    int n = arr.size();
    if (n < 2) return { arr[0], arr[0] };
    if (n < 3) return { arr[0] < arr[1] ? arr[0] : arr[1], arr[0] < arr[1] ? arr[1] : arr[0] };

    int min = std::min(arr[0], arr[1]), max = std::max(arr[0], arr[1]);
    for (int i = 2; i < n-1; i += 2) {  // *** n - 1，因为下面要访问i+1
        if (arr[i] < arr[i+1]) {
            if (arr[i] < min) {
                min = arr[i];
            }
            if (arr[i+1] > max) {
                max = arr[i+1];
            }
        } else {
            if (arr[i+1] < min) {
                min = arr[i+1];
            }
            if (arr[i] > max) {
                max = arr[i];
            }
        }
    }
    min = std::min(arr.back(), min);
    max = std::max(arr.back(), max);
    return { min, max };
}

int main()
{
    {
        std::vector<int> arr = { 2, 3, 1, 4, 5, 6 };  // 偶数个
        std::cout << FindMinMax(arr) << "\n"; // 1, 6
    }
    {
        std::vector<int> arr = { 2, 3, 1, 4, 5, 6, 7 };  // 奇数个
        std::cout << FindMinMax(arr) << "\n"; // 1, 7
    }
}
