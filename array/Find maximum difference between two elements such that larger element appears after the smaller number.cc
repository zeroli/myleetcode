#include "utils.h"

/*
Given array of integers,
find Maximum difference between two elements
such that larger element appears after the smaller number
*/

/* 最初的想法就是建立一个后缀最大值数组
   从后往前记录每个数组元素对应位置右边元素的最大值
   想法类似于前缀数组和
比如：14, 12, 70, 15, 95, 65, 22, 30
它的后缀最大值数组为：
95, 95, 95, 95, 65, 30, 30, 0
30对应位置：30对应右边最大数为0
22对应位置：22右边最大数为30
65对应位置：将之前求得最大数与65比较，最大值
95对应位置：之前最大值为65，max(65, 95)=95
...
这样当要求数组每一个数的与右边最大值的最大diff时，
只需要将对应的后缀最大值数组中的数与原数组同一位置数相减
*/
int MaxDiff(const std::vector<int>& arr)
{
    int n = arr.size();
    std::vector<int> suffixMax(n);
    for (int i = n-2; i >=0; i--) {
        suffixMax[i] = std::max(suffixMax[i+1], arr[i]);
    }
    std::cout << "suffix max: " << suffixMax << "\n";
    int maxDiff = INT_MIN;
    for (int i = 0; i < n; i++) {
        maxDiff = std::max(maxDiff, suffixMax[i] - arr[i]);
    }
    return maxDiff;
}

/*
 上述的算法中的后缀最大值数组可以降维到一个数，
 一边遍历一边求解右边最大值，因为在求解maxDiff时，
 我们并不需要其它地方对应的后缀最大值
*/
int MaxDiff1(const std::vector<int>& arr)
{
    int n = arr.size();
    int maxUntilNow = arr[n-1];
    int maxDiff = INT_MIN;
    for (int i = n-2; i >= 0; i--) {
        if (arr[i] < maxUntilNow) {
            maxDiff = std::max(maxDiff, maxUntilNow - arr[i]);
        } else {
            maxUntilNow = arr[i];
        }
    }
    return maxDiff;
}

int main()
{
    {
        std::vector<int> arr = { 14, 12, 70, 15, 95, 65, 22, 30 };
        std::cout << MaxDiff(arr) << "\n";
        std::cout << MaxDiff1(arr) << "\n";
    }
}
