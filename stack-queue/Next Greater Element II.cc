#include "utils.h"

/*
Given a circular array
 (the next element of the last element is the first element of the array),
  print the Next Greater Number for every element.
   The Next Greater Number of a number x is the first greater number to its traversing-order next in the array,
    which means you could search circularly to find its next greater number.
    If it doesn't exist, output -1 for this number.

Input:
 [1,2,1]

Output:
 [2,-1,2]

Explanation:
 The first 1's next greater number is 2;
The number 2 can't find next greater number;
The second 1's next greater number needs to search circularly, which is also 2.
*/

/*
这个题目于Next Greater Element I不同点在于这是一个circular array
一种解法就是将另一个相同的数组拼接在后面
*/

std::vector<int> NextGreaters(const std::vector<int>& arr)
{
    std::stack<int> stk;
    int n = arr.size();
    std::vector<int> res(n, -1);
    for (int i = 0; i < 2 * n; i++) {
        while (!stk.empty() && arr[stk.top()] < arr[i % n]) {
            res[stk.top()] = arr[i % n];
            stk.pop();
        }
        stk.push(i % n);
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 1};
        std::cout << NextGreaters(arr) << "\n";  // 2, -1, 2
    }
    {
        std::vector<int> arr = { 3, 2, 1 };
        std::cout << NextGreaters(arr) << "\n";  // -1, 3, 3
    }
}
