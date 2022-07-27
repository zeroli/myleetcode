#include "utils.h"

/*
Write a function to count number of smaller elements on right of each element in an array. Given an unsorted array arr[] of distinct integers, construct another array countSmaller[] such that countSmaller[i] contains count of smaller elements on right side of each element arr[i] in array.

Examples:

Input:   arr[] =  {12, 1, 2, 3, 0, 11, 4}
Output:  countSmaller[]  =  {6, 1, 1, 1, 0, 1, 0}

(Corner Cases)
Input:   arr[] =  {5, 4, 3, 2, 1}
Output:  countSmaller[]  =  {4, 3, 2, 1, 0}

Input:   arr[] =  {1, 2, 3, 4, 5}
Output:  countSmaller[]  =  {0, 0, 0, 0, 0}
*/

void Merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& tmp,
        std::vector<int>& counts, std::map<int, int>& num2Index)
{
    for (int i = left; i <= right; i++){
        tmp[i] = arr[i];
    }

    int i = left, j = mid + 1;
    for (int p = left; p <= right; p++) {
        if (i == mid + 1) {
            arr[p] = tmp[j++];
        } else if (j == right + 1) {
            arr[p] = tmp[i++];
            // please note, this is for arr[p], not arr[i]/arr[j]
            counts[num2Index[arr[p]]] += (j - mid - 1);
        } else if (tmp[i] > tmp[j]) {
            arr[p] = tmp[j++];
        } else {
            arr[p] = tmp[i++];
            // please note, this is for arr[p], not arr[i]/arr[j]
            counts[num2Index[arr[p]]] += (j - mid - 1);
        }
    }
    //std::cout << counts << "\n";
}

void MergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& tmp,
        std::vector<int>& counts, std::map<int, int>& num2Index)
{
    if (left == right) {
        return;
    }

    int mid = left + (right - left) / 2;
    MergeSort(arr, left, mid, tmp, counts, num2Index);
    MergeSort(arr, mid+1, right, tmp, counts, num2Index);
    Merge(arr, left, mid, right, tmp, counts, num2Index);
}

std::vector<int> CountSmaller(std::vector<int>& arr)
{
    std::vector<int> counts(arr.size(), 0);
    std::vector<int> tmp(arr);
    std::map<int, int> num2Index;
    for (int i = 0; i < arr.size(); i++) {
        num2Index[arr[i]] = i;
    }
    MergeSort(arr, 0, arr.size()-1, tmp, counts, num2Index);
    return counts;
}

int main()
{
    {
        std::vector<int> arr = { 12, 1, 2, 3, 0, 11, 4 };
        std::cout << CountSmaller(arr) << "\n";  // 6, 1, 1, 1, 0, 1, 0
    }
    {
        std::vector<int> arr = { 5, 4, 3, 2, 1 };
        std::cout << CountSmaller(arr) << "\n";  // 4, 3, 2, 1, 0
    }
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5 };
        std::cout << CountSmaller(arr) << "\n";  // 0, 0, 0, 0, 0
    }

}
