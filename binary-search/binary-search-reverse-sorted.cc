#include "utils.h"

/*
  数组逆序排序，从中找出lower-bound/upper-bound
*/

int FirstSmallerOrEqualTo(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size();
    // left的取值范围就是[0, n]
    while (left < right) {  // 循环终止条件就是left == right，right最大取到n
        int mid = left + (right - left) / 2;
        if (target >= arr[mid]) {
            right = mid;  // arr[mid]有可能是目标值(first smaller/equal to)
        } else {  // target <= arr[mid]
            //  绝对不能将left=mid，因为两个元素时，left总是等于mid
            left = mid + 1;
        }
    }
    // 返回值的范围从[0, n]
    // 0: 表示所有元素都比`target`要小，第一个元素就是目标
    // n: 表示所有元素都比`target`要大
    return left;
}
// 似乎没有办法通过类似上面的方法获取last larger or equal to的位置

int LastLargerOrEqualTo(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size();
    // left的取值范围就是[0, n]
    while (left < right) {  // 循环终止条件就是left == right，right最大取到n
        int mid = left + (right - left) / 2;
        if (target > arr[mid]) {
            right = mid;
        } else {  // target <= arr[mid]
           // 绝对不能将left=mid，因为两个元素时，left总是等于mid
           // 我们最后要将left - 1
            left = mid + 1;
        }
    }
    // 返回值的范围从[-1, n-1]
    // -1: 表示所有元素都比`target`要小，第一个元素就是目标
    // n-1: 表示所有元素都比`target`要大
    return left - 1;
}

int main()
{
    {
        std::vector<int> arr = { 6, 5, 4, 2, 1 };
        std::cout << FirstSmallerOrEqualTo(arr, 7) << "\n";  // 0 (=6)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 2, 1 };
        std::cout << FirstSmallerOrEqualTo(arr, 0) << "\n";  // 5 (none)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 2, 1 };
        std::cout << FirstSmallerOrEqualTo(arr, 3) << "\n";  // 3 (=2)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 3, 2, 1 };
        std::cout << FirstSmallerOrEqualTo(arr, 3) << "\n";  // 3 (=3)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 3, 3, 2, 1 };
        std::cout << FirstSmallerOrEqualTo(arr, 3) << "\n";  // 3 (=3)
    }

    {
        std::vector<int> arr = { 6, 5, 4, 3, 3, 2, 1 };
        std::cout << LastLargerOrEqualTo(arr, 3) << "\n";  // 4 (=3)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 2, 1 };
        std::cout << LastLargerOrEqualTo(arr, 3) << "\n";  // 2 (=4)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 3, 3, 2, 1 };
        std::cout << LastLargerOrEqualTo(arr, 0) << "\n";  // 6 (=1)
    }
    {
        std::vector<int> arr = { 6, 5, 4, 3, 3, 2, 1 };
        std::cout << LastLargerOrEqualTo(arr, 7) << "\n";  // -1 (none)
    }
}
