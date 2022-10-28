/*
从一个数组中找到第一个缺失的正整数，数组包含正数，负数和0
1,2,0 => 3
3,4,-1,1 => 2
*/
#include "utils.h"

int FindPositiveMissingNum(std::vector<int>& arr)
{
    // 数组里面包含负数和0，
    // 我们就不能采用传统方法将元素变为其负数的方式来标记是谁将它变成负数的
    // 我们采用的思路是：
    // 如果某个位置上的数是非负数而且范围小于数组长度，则将它交换到它的值对应的索引位置上，
    // 如果这个非负数超出范围，将这个数变成-1，继续下一个位置的数
    // 如果这个数是负数，跳过这个数，继续下一个位置的数
    // 对于交换回来的数需要重复上述步骤，直到它等于它的位置索引，
    // 或者变成上面2种情况中的一种后跳过
    for (int i = 0; i < arr.size(); i++) {
        // 非负数，而且在数组长度范围内，交换到对应位置，否则跳过
        while (arr[i] != i) {
            if (arr[i] >= 0 && arr[i] < arr.size()) {
                std::swap(arr[i], arr[arr[i]]);
            } else {  // 交换回来为负数，或者超出数组范围，跳到下一个
                break;
            }
        }
    }
    // 检查每个元素，如果位置上的数不等于其位置索引，
    // 则返回对应的位置索引
    // 我们需要跳过0，因为不管0有没有匹配，
    // 都不是我们要找的正整数
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] != i) {
            return i;
        }
    }
    return arr.size();
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 0 };
        assert(3 == FindPositiveMissingNum(arr));
    }
    {
        std::vector<int> arr = { 3,4,-1,1 };
        assert(2 == FindPositiveMissingNum(arr));
    }
}
