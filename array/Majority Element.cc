#include "utils.h"

/*
 Given an array of size n, find the majority element.
  The majority element is the element that appears more than ⌊ n/2 ⌋ times.
You may assume that the array is non-empty and the majority element always exist in the array.
*/

int MajorityElement(const std::vector<int>& arr)
{
    int n = arr.size();
    int k = n / 2;
    // we could sort, and then the mid element should be majority element
    // O(nlgn)

    // using Moore's voting algorithm
    int candidate = 0;
    int cnt = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == arr[candidate]) {
            cnt++;
        } else {
            cnt--;
        }
        if (cnt == 0) {
            candidate = i;
            cnt = 1;
        }
    }
    // if problem says it might be no major element,
    // then we need use final candidate to check if its occurence is over n/2
    return arr[candidate];
}

int main()
{
    {
        std::vector<int> arr = { 2, 1, 1, 3, 1 };
        std::cout << MajorityElement(arr) << "\n";
    }
}
