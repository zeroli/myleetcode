/*
  从一个排序的数组中去除重复的元素，允许最多K次重复，返回去重后的数组长度
  1, 1, 2, 2, 3 => 1, 2, 3, if K=1
  1, 1, 2, 2, 3 => 1, 1, 2, 2, 3, if K=2
  1, 1, 1, 2, 2, 3 => 1, 1, 2, 2, 3, if K=2
*/
#include "utils.h"

int RemoveDuplicateByK(const std::vector<int>& arr0, int K)
{
    if (K <= 0) return 0;
    if (K >= arr0.size()) return arr0.size();

    std::vector<int> arr = arr0;
    int index = K - 1;
    for (int i = K; i < arr.size(); i++) {
        // Invariant: arr[index - (K-1)], ..., arr[index]，最多K个重复，满足条件
        // 现在来一个新元素，判断是否可以放在index+1所在位置，还是丢弃跳过
        // 假设arr[index - (K-1)] = x, 新元素是y
        // if x == y, 因为数组是排序的，所以index-(K-1)到index的元素都是重复相等的
        // y不能放在index+1所在位置，不然会出现K+1个重复元素
        // if x != y, 那么新形成的K个元素就最多只会有K个重复，满足条件
        // 这时y就要放入index+1所在位置
        if (arr[i] != arr[index - (K - 1)]) {
            arr[++index] = arr[i];
        }
    }
    // index是最后一个修改的位置，那么长度就是index+1
    return index + 1;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3 };
        std::cout << RemoveDuplicateByK(arr, 1) << "\n";  // 3
        std::cout << RemoveDuplicateByK(arr, 2) << "\n";  // 3
    }
    {
        std::vector<int> arr = { 1, 2, 2, 2, 3 };
        std::cout << RemoveDuplicateByK(arr, 1) << "\n";  // 3
        std::cout << RemoveDuplicateByK(arr, 2) << "\n";  // 4
    }
    {
        std::vector<int> arr = { 1, 1, 2, 2, 3 };
        std::cout << RemoveDuplicateByK(arr, 1) << "\n";  // 3
        std::cout << RemoveDuplicateByK(arr, 2) << "\n";  // 5
    }
    {
        std::vector<int> arr = { 1, 1, 1, 2, 2, 3 };
        std::cout << RemoveDuplicateByK(arr, 1) << "\n";  // 3
        std::cout << RemoveDuplicateByK(arr, 2) << "\n";  // 5
    }
}
