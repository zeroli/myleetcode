#include "utils.h"

// 找到未排序数组中的第2大元素
// 只需要一轮遍历
// 这个思路也可以用来找到前3大的数组元素
int SecondLargest(const std::vector<int>& arr)
{
    int largest = 0;
    int secondLargest = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] > secondLargest) {
            secondLargest = arr[i];
        }
    }
    return secondLargest;
}

int main()
{
    std::vector<int> arr = {7,5,6,1,4,2};
    std::cout << SecondLargest(arr) << "\n";  // 6
}
