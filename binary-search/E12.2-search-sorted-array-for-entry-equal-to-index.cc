/*
写一个程序，输入排序数组，查找一个元素，它的值等于它的index
-2, 0, 2, 3, 6, 7, 9 => 2 or 3
有可能满足条件的元素有很多个，只要返回一个就可以
*/

#include "utils.h"

/*
排序数组，查找满足特定要求的元素，一般想到的是二分查找
*/

int Search(const std::vector<int>& arr)
{
    int left = 0, right = arr.size() -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == mid) {
            return mid;
        }
        // 如果中间元素大于它的index，
        // 那么它后面比它大的元素肯定也大于它们对应的index
        // 比如:
        //   arr[mid]: 1, (3), 4, 6
        //         mid:  1, (2), 3, 4
        // => 所以需要到左半部分继续搜索
        // 如果中间元素小于它的index，
        // 那么它前面比它小的元素肯定也小于它们对应的index
        // 比如：
        //   arr[mid]: 1  (2), 4, 6
        //         mid:  2  3,   4, 5
        // => 所以需要到后半部分继续搜索
        if (arr[mid] > mid) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return -1;
}

int main()
{
    {
        std::vector<int> arr = { -2, 0, 2, 3, 6, 7, 9 };
        std::cout << Search(arr) << "\n";  // 3
    }
}
