#include "utils.h"

// another solution is using idea of merge sort, inversion pairs
// see sorting-search/
std::vector<int> CountSmallerOnRight(const std::vector<int>& arr)
{
    std::vector<int> res(arr.size(), 0);

    std::stack<int> stk;  // store index
    for (int i = arr.size() - 1; i >= 0; i--) {
        // monotical descending order, when meet bigger one, pop until see bigger one
        while (!stk.empty() && arr[stk.top()] < arr[i])
        {
            res[i] += res[stk.top()] + 1;  // get all smaller from previous visited ones
            stk.pop();
        }
        stk.push(i);
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = {12, 1, 2, 3, 0, 11, 4};
        std::cout << CountSmallerOnRight(arr) << "\n"; // {6, 1, 1, 1, 0, 1, 0}
    }
}
