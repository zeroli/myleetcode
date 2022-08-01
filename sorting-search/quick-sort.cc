#include "utils.h"

// 以第一个元素作为pivot
int Partition(std::vector<int>& arr, int left, int right)
{
    int p = left;  // 以第一个元素作为pivot
    int j = left;
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] <= arr[p]) {
            std::swap(arr[i], arr[++j]);
        }
    }
    // 最后j对应的元素肯定小于等于pivot，
    // 因为前面的swap操作实在arr[i] <= pivot条件下执行的
    std::swap(arr[p], arr[j]);
    return j;
}

// 以最后元素作为pivot (<算法导论> 代码版本)
int Partition2(std::vector<int>& arr, int left, int right)
{
    int p = right;  // 以最后元素作为pivot
    int j = left;
    for (int i = left; i < right; i++) {
        if (arr[i] <= arr[p]) {
            std::swap(arr[i], arr[j++]);
        }
    }
    // 此时`j`对应的元素肯定大于pivot
    // 因为前面swap操作是在arr[i] <= pivot条件下执行的，之后j++了
    std::swap(arr[p], arr[j]);
    return j;
}

// 从两端向中间遍历 (<算法4> 代码版本)
int Partition3(std::vector<int>& arr, int left, int right)
{
    int p = left;  // 以第一个元素为pivot
    int i = left, j = right + 1;
    while (true) {
        while (arr[++i] <= arr[p]) {
            if (i == right) {
                break;
            }
        }
        while (arr[--j] >= arr[p]) {
            if (j == left) {
                break;
            }
        }
        if (i >= j) {
            break;
        }
        std::swap(arr[i], arr[j]);
    }
    // 此时`j`对应的位置arr[j] < arr[p]
    // 因为`j`是因为不满足第二个while而终止循环的
    std::swap(arr[left], arr[j]);
    return j;
}

// 从两端向中间遍历 (<算法设计于应用> 代码版本）
int Partition4(std::vector<int>& arr, int left, int right)
{
    int p = right;  // 以最后元素为pivot
    int i = left, j = right - 1;
    while (i <= j) {
        while (i <= j && arr[i] <= arr[p]) {
            i++;
        }
        while (i <= j && arr[j] >= arr[p]) {
            j--;
        }
        if (i >= j) {
            break;
        }
        std::swap(arr[i], arr[j]);
    }
    // 此时`i`对应的位置arr[i] > arr[p]
    // 因为`i`是因为不满足第一个while而终止循环的
    std::swap(arr[p], arr[i]);
    return i;
}

void QuickSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right) return;
    int p = Partition(arr, left, right);
    QuickSort(arr, left, p - 1);
    QuickSort(arr, p + 1, right);
}

std::vector<int> QuickSort(std::vector<int>& arr)
{
    QuickSort(arr, 0, arr.size() - 1);
    return arr;
}

int main()
{
    {
        std::vector<int> arr = { 4, 5, 2, 1, 6, 7, 0, 9, 10 };
        std::cout << QuickSort(arr) << "\n";
    }
}
