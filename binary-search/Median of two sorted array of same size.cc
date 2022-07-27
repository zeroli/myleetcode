#include "utils.h"

/*
There are two sorted arrays arr1[] and arr2[] of size n each,
 write a program to find the median of the two sorted arrays.
*/

int FindMedian_(const std::vector<int>& arr1, int l1, int r1,
        const std::vector<int>& arr2, int l2, int r2, int k)
{
    int n1 = r1 - l1 + 1;
    int n2 = r2 - l2 + 1;
    if (n1 > n2) {
        return FindMedian_(arr2, l2, r2, arr1, l1, r1, k);
    }
    // base cases
    if (n1 == 0) {
        return arr2[l2 + k - 1];
    }
    if (k == 1) {
        return std::min(arr1[l1], arr2[l2]);
    }

    int ia = std::min(k / 2, n1);
    int ib = k - ia;
    int m1 = l1 + ia - 1, m2 = l2 + ib - 1;
    if (arr1[m1] < arr2[m2]) {  // then arr1[l1...m1] all < arr2[m2]
        return FindMedian_(arr1, m1 + 1, r1, arr2, l2, r2, k - ia);
    } else if (arr1[m1] > arr2[m2]) {  // then arr2[l2...m2] all < arr1[m1]
        return FindMedian_(arr1, l1, r1, arr2, m2 + 1, r2, k - ib);
    } else {
        return arr1[m1-1];
    }
}

double FindMedian(const std::vector<int>& arr1, const std::vector<int>& arr2)
{
    int n1 = arr1.size();
    int n2 = arr2.size();
    int k = n1 + (n2 - n1) / 2;
    if ((n1 + n2) & 1) {
        return FindMedian_(arr1, 0, n1-1, arr2, 0, n2-1, k);
    } else {
        return (FindMedian_(arr1, 0, n1-1, arr2, 0, n2-1, k) +
                FindMedian_(arr1, 0, n1-1, arr2, 0, n2-1, (k + 1))) / 2.0;
    }
}

int main()
{
    {
        std::vector<int> arr1 = { 1, 14, 15, 24, 35 };
        std::vector<int> arr2 = { 2, 13, 19, 32, 47 };
        std::cout << FindMedian(arr1, arr2) << "\n";
    }
    {
        std::vector<int> arr1 = { 1, 3, 5, 11, 17 };
        std::vector<int> arr2 = { 9, 10, 11, 13, 14 };
        std::cout << FindMedian(arr1, arr2) << "\n";
    }
    {
        std::vector<int> arr1 = { 1, 3, 5, 11, 17 };
        std::vector<int> arr2 = { 9, 10, 11, 13, 14, 15 };
        std::cout << FindMedian(arr1, arr2) << "\n";
    }

}
