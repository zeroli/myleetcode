#include "utils.h"

/*
给定一个未排序的数组，判断这个数组中是否存在长度为 3 的递增子序列。

数学表达式如下:

如果存在这样的 i, j, k,  且满足 0 ≤ i < j < k ≤ n-1，
使得 arr[i] < arr[j] < arr[k] ，返回 true ; 否则返回 false 。
说明: 要求算法的时间复杂度为 O(n)，空间复杂度为 O(1) 。

示例 1:

输入: [1,2,3,4,5]
输出: true
示例 2:

输入: [5,4,3,2,1]
输出: false
*/

/*
这题只要求递增的三元素子序列，而不是最长的递增子序列
维护两个值，代表最小，次小，依次遍历数组
记录遇到的最小值，遇到的次小值，一旦遇到一个比最小和次小值都大的元素
可以肯定已经遍历到了递增的三元素子序列了。
*/

std::vector<int> IncreasingTripletSubseq(const std::vector<int>& arr)
{
    std::vector<int> ret(3);
    ret[0] = INT_MAX;
    ret[1] = INT_MAX;
    bool exist = false;
    for (auto num : arr) {
        if (num < ret[0]) {
            ret[0] = num;
        } else if (num < ret[1]) {
            ret[1] = num;
        } else {
            ret[2] = num;
            exist = true;
            break;
        }
    }
    if (exist) return ret;
    else return {};
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        std::cout << IncreasingTripletSubseq(arr) << "\n";  // 1,2,3
    }
    {
        std::vector<int> arr = { 5,4,3,2,1 };
        std::cout << IncreasingTripletSubseq(arr) << "\n";  // xxxx
    }
}
