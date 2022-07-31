#include "utils.h"

/*
Given a binary array, find the maximum number of consecutive 1s in this array.

Input:
 [1,1,0,1,1,1]

Output:
 3

Explanation:
 The first two digits or the last three digits are consecutive 1s.
    The maximum number of consecutive 1s is 3.
*/

int Count1s(const std::vector<int>& arr)
{
    int res = 0;
    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 1) {
            cnt++;
            res = std::max(res, cnt);
        } else {
            cnt = 0;
        }
    }
    return res;
}

int main()
{
    std::vector<int> arr = { 1, 1, 0, 1, 1, 1 };
    std::cout << Count1s(arr) << "\n";  // 3
}
