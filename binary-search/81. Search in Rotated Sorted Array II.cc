#include "utils.h"

// 返回索引，-1代表没找到
// 旋转有序数组包含重复元素
int SearchTarget(const std::vector<int>& arr, int target)
{
    int left = 0, right = arr.size() - 1;
    // 用right=n-1，是因为下面代码有用`right`作为索引获取元素
    // 用<= 作为判断条件是因为下面总是会更改left/right，最终会导致left/right相等，
    // 直至left > right，退出循环
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (target == arr[mid]) {
            return mid;
        }

        // 下面开始3个判断条件是过滤掉重复元素存在的情况
        if (arr[left] == arr[mid] && arr[mid] == arr[right]) {
            left++;  // no one is equal to target
            right--;
        } else if (arr[left] == arr[mid]) {
            left = mid + 1;  // remove half of it, since [left... mid-1] not equal to target
        } else if (arr[right] == arr[mid]) {
            right = mid - 1;  // remove half of it, since [mid+1... right] not equal to target
        } else if (arr[mid] < arr[right]) {  // right part is ascending order
            if (arr[mid] < target && target <= arr[right]) {  // in range
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        } else {  // left part is ascending order
            if (arr[left] <= target && target < arr[mid]) {  // in range
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
    }
    return -1;
}

int main()
{
    {
        std::vector<int> arr = { 2,5,6,0,0,1,2 };
        int target = 0;
        std::cout << SearchTarget(arr, target) << "\n";
    }
    {
        std::vector<int> arr = { 2,5,6,0,0,1,2 };
        int target = 3;
        std::cout << SearchTarget(arr, target) << "\n";
    }
}
