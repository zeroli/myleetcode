#include "utils.h"

// 练习插入排序算法
std::vector<int> InsertionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int tmp = arr[i];
        while (j >= 0 && arr[j] > tmp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j+1] = tmp;
    }
    return arr;
}

int main()
{
    {
        std::vector<int> arr = { 2, 3, 1, 5, 8, 3, 9, 10, 5, 2 };
        std::cout << InsertionSort(arr) << "\n";  // 1, 2, 2, 3, 3, 5, 5, 8, 9, 10
    }
    {
        std::vector<int> arr = { 0, 0, 0, 0, 0, 0 };
        std::cout << InsertionSort(arr) << "\n";  // 0,0,0,0,0,0
    }
    {
        std::vector<int> arr = { 0, 1,2,3,4,5 };
        std::cout << InsertionSort(arr) << "\n";  // 0,1,2,3,4,5
    }
    {
        std::vector<int> arr = { 5,4,3,2,1,0 };
        std::cout << InsertionSort(arr) << "\n";  // 0,1,2,3,4,5
    }
}
