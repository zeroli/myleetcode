#include "utils.h"

// 去除重复元素，使其重复元素最多出现2次
int RemoveDuplicates(std::vector<int>& arr, int m)
{
    int k = 0;
    int j = 0;  // 每个unique元素
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != arr[j]) {
            arr[++j] = arr[i];
            k = 0;  // 碰到不同的，需要重置为0
        } else {
            k++;
            // 可以重复出现，做拷贝
            if (k < m) {
                arr[++j] = arr[i];
            }
        }
    }
    arr.resize(j + 1);
    return j + 1;
}

int main()
{
    {
        std::vector<int> arr = { -1, 0, 1, 1, 2, 9, 9 };
        std::cout << RemoveDuplicates(arr, 2) << "->";  // 7
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { -10, 1, 3, 6, 6, 6, 6, 10 };
        std::cout << RemoveDuplicates(arr, 2) << "->";  // 6
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { 10, 20, 30, 33, 45 };
        std::cout << RemoveDuplicates(arr, 2) << "->";  // 5
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { 1, 1, 1, 1, 1, 1 };
        std::cout << RemoveDuplicates(arr, 2) << "->";  // 2
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { -10, 1, 3, 6, 6, 6, 6, 10 };
        std::cout << RemoveDuplicates(arr, 3) << "->";  // 7
        std::cout << arr << "\n";
    }
    {
        std::vector<int> arr = { 1, 1, 1, 1, 1, 1 };
        std::cout << RemoveDuplicates(arr, 4) << "->";  // 4
        std::cout << arr << "\n";
    }
}
