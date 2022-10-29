/*
两个排序数组，求解它们的交集
[1, 2, 3],[2, 3, 4] => [2, 3]

*/

#include "utils.h"

std::vector<int> Insertion2SortedArrays(const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    std::vector<int> intersects;
    int i = 0, j = 0;
    int n1 = arr1.size(), n2 = arr2.size();
    while (i < n1 && j < n2) {
        if (arr1[i] == arr2[j]) {
            // 相同的元素，不再认为是交集了
            if (intersects.empty() || arr1[i] != intersects.back()) {
                intersects.push_back(arr1[i]);
            }
            i++;
            j++;
        } else if (arr1[i] < arr2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return intersects;
}

int main()
{
    {
        std::vector<int> arr1 = { 1, 2, 3};
        std::vector<int> arr2 = { 2, 3, 4};
        std::cout << Insertion2SortedArrays(arr1, arr2) << "\n";
    }
    {
        std::vector<int> arr1 = { 1, 2, 2, 3};
        std::vector<int> arr2 = { 2, 3, 4};
        std::cout << Insertion2SortedArrays(arr1, arr2) << "\n";
    }
}
