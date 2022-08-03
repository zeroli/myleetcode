#include "utils.h"

// 仍然采用快速排序里面的partition算法，不过这次是
// 左边大于等于pivot，右边小于pivot
// 这题解法也可以是采用最小堆，存储K个元素，堆顶是最小值
// 遍历数组，维护K个元素的最小堆，遍历完之后堆顶就是第K个最大值
int Partition(std::vector<int>& arr, int left, int right)
{
    int p = left;  // left as pivot
    int j = left;
    for (int i  = left + 1; i <= right; i++) {
        if (arr[i] >= arr[p]) {
            std::swap(arr[++j], arr[i]);
        }
    }
    std::swap(arr[p], arr[j]);
    return j;
}

int SelectKth(std::vector<int>& arr, int left, int right, int K)
{
    int p = Partition(arr, left, right);
    if (p == K) {
        return arr[p];
    } else if (p > K) {
        return SelectKth(arr, left, p - 1, K);
    } else {
        return SelectKth(arr, p + 1, right, K);
    }
}

int KthLargest(std::vector<int>& arr, int K)
{
    K -= 1;
    return SelectKth(arr, 0, arr.size() - 1, K);
}

int main()
{
    std::vector<int> arr = { 3,2,1,5,6,4 };
    std::cout << KthLargest(arr, 2) << "\n";  // 5
}
