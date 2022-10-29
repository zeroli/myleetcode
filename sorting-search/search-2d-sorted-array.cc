/*
给定一个2d数组，行和列都排序了，但是下一行不全部大于上一行
-1   2  4  4   6
 1   5  5  9  21
 3   6  6  9  22
 3   6  8 10  24
 6   8  9 12  25
 8 10 12 13 40
搜索7，返回false
搜索8，返回true
=========>
======== ||
                   ||
                   ||
                   ||
                  \||/
不同视角来看待这个2d array：
每一行，行进到底，然后转弯，顺着列行进到底，是一个升序排序的序列
下一行，行进到底，然后转弯。。。
如果每遍历一行时，查看当前行最后一个值（转弯处），与目标值进行比较
如果目标值大，那么那一行转弯之前的值都会比目标值小，我们可以排除当前行的元素
递进到下一行的开头，重复这个过程，一直遍历完所有行
*/

#include "utils.h"

// 时间复杂度为O(m+n)
bool Search2DArray(const Array2D_t<int>& arr2d, int target)
{
    int m = arr2d.size(), n = arr2d[0].size();
    int r = 0, c = n - 1;
    while (r < m && c < n) {
        if (arr2d[r][c] == target) {
            return true;
        }
        if (arr2d[r][c] < target) {
            r++;  // 当前行都比target要小，查看下一行，列不动
        } else {
            c--;  // 当前列都比target要大，查看下一列，行不动
        }
    }
    return false;
}

int main()
{
    {
        Array2D_t<int> arr2d = {
            { -1, 2,  4,  4,   6 },
            { 1,  5,  5,  9, 21 },
            { 3,  6,  6,  9,  22},
            { 3,  6,  8, 10,  24},
            { 6,  8,  9, 12,  25},
            { 8, 10, 12, 13, 40}
        };
        std::cout << Search2DArray(arr2d, 7) << std::endl; // false
        std::cout << Search2DArray(arr2d, 8) << std::endl; // true
    }
}
