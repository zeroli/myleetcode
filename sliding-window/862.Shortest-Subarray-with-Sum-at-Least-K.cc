/*
Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.

A subarray is a contiguous part of an array.



Example 1:

Input: nums = [1], k = 1
Output: 1

Example 2:

Input: nums = [1,2], k = 4
Output: -1

Example 3:

Input: nums = [2,-1,2], k = 3
Output: 3



Constraints:

    1 <= nums.length <= 105
    -105 <= nums[i] <= 105
    1 <= k <= 109

*/

#include "utils.h"

// array may contain negative number ***

int ShortestSubstrLen(const std::vector<int>& arr, int k)
{
    int n = arr.size();
    std::vector<int> prefixSum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixSum[i+1] = prefixSum[i] + arr[i];
    }
    std::cout << "prefixSum: " << prefixSum << "\n";
    int minLen = n + 1;
    // maintain the ascending of prefixsum that might be start index
    // store the index
    // monotonic ascending queue support front/back removal
    std::deque<int> deque;
    for (int i = 0; i <= n; i++) {
        while (!deque.empty() && (prefixSum[i] - prefixSum[deque.front()] >= k))
        {
            // do update
            minLen = std::min(minLen, i - deque.front());
            deque.pop_front();
        }
        // reestablish the deque
        // remove those bigger ones than current prefixSum[i]
        // since this i is bigger than those removal ones (bigger)
        // and later smaller prefixSum will contribute bigger diff
        // no need keep those bigger ones(their index smaller, and definitely longer)
        while (!deque.empty() && prefixSum[i] < prefixSum[deque.back()])
        {
            deque.pop_back();
        }
        deque.push_back(i);
    }
    return minLen <= n ? minLen : -1;
}

int main()
{
    {
        std::vector<int> arr = {2, -1, 2};
        int k = 3;
        std::cout << ShortestSubstrLen(arr, k) << "\n";  // 3
    }
}

/*
What makes this problem hard is that we have negative values. If you haven't already done the problem with positive integers only, I highly recommend solving it first, as I will use its Sliding Window solution to reach the Deque solution here. You can find the problem here , and a Sliding window solution here.

Recall of the Sliding window solution in a positive array

The Sliding window solution finds the subarray we are looking for in a linear time complexity. The idea behind it is to maintain two pointers: start and end, moving them in a smart way to avoid examining all possible values 0<=end<=n-1 and 0<=start<=end (to avoid brute force).
What it does is:

    Incremeting the end pointer while the sum of current subarray (defined by current values of start and end) is smaller than the target.
    Once we satisfy our condition (the sum of current subarray >= target) we keep incrementing the start pointer until we violate it (until sum(array[start:end+1]) < target).
    Once we violate the condition we keep incrementing the end pointer until the condition is satisfied again and so on.

The reason why we stop incrementing start when we violate the condition is that we are sure we will not satisfy it again if we keep incrementing start. In other words, if the sum of the current subarray start -> end is smaller than the target then the sum of start+1 -> end is neccessarily smaller than the target. (positive values)
The problem with this solution is that it doesn't work if we have negative values, this is because of the sentence above Once we "violate" the condition we stop incrementing start.

Problem of the Sliding window with negative values

Now, let's take an example with negative values nums = [3, -2, 5] and target=4. Initially start=0, we keep moving the end pointer until we satisfy the condition, here we will have start=0 and end=2. Now we are going to move the start pointer start=1. The sum of the current subarray is -2+5=3 < 4 so we violate the condition. However if we just move the start pointer another time start=2 we will find 5 >= 4 and we are satisfying the condition. And this is not what the Sliding window assumes.

Deque solution

The Deque solution is just a modification of the Sliding window solution above. We will modify the way we are updating start.
Let's explain the Deque solution based on the code of @Lee215 by answering some questions :

    def shortestSubarray(self, A, K):
        N = len(A)
        B = [0] * (N + 1)
        for i in range(N): B[i + 1] = B[i] + A[i]
        d = collections.deque()
        res = N + 1
        for i in xrange(N + 1):
            while d and B[i] - B[d[0]] >= K: res = min(res, i - d.popleft())
            while d and B[i] <= B[d[-1]]: d.pop()
            d.append(i)
        return res if res <= N else -1

What does the Deque store :
The deque stores the possible values of the start pointer. Unlike the sliding window, values of the start variable will not necessarily be contiguous.

Why is it increasing :
So that when we move the start pointer and we violate the condition, we are sure we will violate it if we keep taking the other values from the Deque. In other words, if the sum of the subarray from start=first value in the deque to end is smaller than target, then the sum of the subarray from start=second value in the deque to end is necessarily smaller than target.
So because the Deque is increasing (B[d[0]] <= B[d[1]]), we have B[i] - B[d[0]] >= B[i] - B[d[1]], which means the sum of the subarray starting from d[0] is greater than the sum of the sub array starting from d[1].

Why do we have a prefix array and not just the initial array like in sliding window :
Because in the sliding window when we move start (typically when we increment it) we can just substract nums[start-1] from the current sum and we get the sum of the new subarray. Here the value of the start is jumping and one way to compute the sum of the current subarray in a constant time is to have the prefix array.

Why using Deque and not simply an array :
We can use an array, however we will find ourselves doing only three operations:
1- remove_front : when we satisfy our condition and we want to move the start pointer
2- append_back : for any index that may be a future start pointer
3- remove_back : When we are no longer satisfying the increasing order of the array
Deque enables doing these 3 operations in a constant time.
*/
