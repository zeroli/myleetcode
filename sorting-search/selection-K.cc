#include "utils.h"

// 练习使用selection算法查找数组中第K小的数
int Partition(std::vector<int>& arr, int left, int right)
{
    int p = left;  // 选第一个为pivot
    int j = left;
    for (int i = left + 1; i <= right; i++) {
        if (arr[i] <= arr[p]) {
            std::swap(arr[i], arr[++j]);
        }
    }
    // 此时arr[j]<=arr[p]
    std::swap(arr[p], arr[j]);
    return j;
}

int SelectK(std::vector<int>& arr, int left, int right, int K)
{
    int p = Partition(arr, left, right);
    if (p == K) {
        return arr[p];
    } else if (p > K) {  // 第K小在p的左边
        return SelectK(arr, left, p - 1, K);
    } else {  // 第K小在p的右边
        return SelectK(arr, p + 1, right, K);
    }
}

// K从1开始
int SelectK(std::vector<int>& arr, int K)
{
    int n = arr.size();
    assert(K >= 1 && K <= n);
    return SelectK(arr, 0, n - 1, K - 1);
}

int main()
{
    {
        std::vector<int> arr = { 2, 3, 5, 7, 8, 19, 20, 4 };
        std::cout << SelectK(arr, 2) << "\n";  // 3
    }
}
