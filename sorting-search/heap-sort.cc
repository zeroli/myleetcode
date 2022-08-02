#include "utils.h"

// heap排序，背后其实selection排序的思想，每一步选择一个最大的
// 但不会像selection排序那样每次都比较所有剩下的元素得到一个最大值

// heapify数组范围[idx, end)，使其满足最大堆属性
void Heapify(std::vector<int>& arr, int idx, int end)
{
    int left = idx * 2 + 1;
    int right = idx * 2 + 2;
    int largest = idx;  // 记录当前节点与左右子节点的最大者的index
    if (left < end && arr[left] > arr[idx]) {
        largest = left;
    }
    if (right < end && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != idx) {
        std::swap(arr[idx], arr[largest]);
        // 继续下沉，平衡下面的树节点
        Heapify(arr, largest, end);
    }
}

// 建立一个最大项堆，堆顶元素是最大值
void BuildHeap(std::vector<int>& arr)
{
    int n = arr.size();
    // 从n/2-1开始进行平衡，因为n/2开始的节点是叶子节点
    // 要么是在倒数第一层，要么是在倒数第二层
    // 叶子节点不需要平衡
    for (int i = n / 2 - 1; i >= 0; i--) {
        Heapify(arr, i, n);
    }
}

std::vector<int> HeapSort(std::vector<int>& arr)
{
    int n = arr.size();
    BuildHeap(arr);
    // 每次将最大元素放入数组后面
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[i], arr[0]);
        Heapify(arr, 0, i);
    }
    return arr;
}

int main()
{
    std::vector<int> arr = { 2, 3, 4, 7, 9, 1, 2, 0, 10, 5 };
    std::cout << HeapSort(arr) << "\n";
}
