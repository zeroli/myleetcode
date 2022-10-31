/*
1438. Longest Continuous Subarray With Absolute Diff Less Than
     or Equal to Limit

Input: arr[] = {2, 4, 5, 5, 5, 3, 1}, K = 0
Output: 3
Explanation:
The possible subarray with difference in elements as 0 is {5, 5, 5} whose length is 3.
 Hence the output is 3.

Input: arr[] = {1, 2, 3, 6, 7}, K = 2
Output: 3
Explanation:
The possible subarray with difference in elements at most 2 is {1, 2, 3} whose length is 3.
 Hence the output is 3.

*/

#include "utils.h"

#include "monotonic-queue.h"

int LongestSubarrayAbsDiffSmallerThan(const std::vector<int>& arr, int k)
{
    // use sliding window + monotonic max/min queue
    // max/min queue maintain max/min value for previous subarray which abs diff <= k
    // so that sliding to right, new value will check if violate the subarray
    int beg = 0;
    int maxLen = 0;

    // 只要满足窗口内最大和最小值差值<=k
    // 那么求滑动窗口内的最大值和最小值，可以直接利用单调队列数据结构
    MonotonicQueue<int, std::less<int>> maxqueue;
    MonotonicQueue<int, std::greater<int>> minqueue;
    for (int end = 0; end < arr.size(); end++) {
        int cur = arr[end];
        maxqueue.push(cur);
        minqueue.push(cur);

        // violate? shrink window left side
        while (maxqueue.front() - minqueue.front() > k) {
            maxqueue.pop(arr[beg]);
            minqueue.pop(arr[beg]);
            beg++;
        }
        maxLen = std::max(maxLen, end - beg + 1);
    }
    return maxLen;
}

int main()
{
    {
        std::vector<int> arr = { 2, 4, 5, 5, 5, 3, 1 };
        int k = 0;
        std::cout << LongestSubarrayAbsDiffSmallerThan(arr, k) << "\n";  // 3 (5,5,5)
    }
    {
        std::vector<int> arr = { 1, 2, 3, 6, 7 };
        int k = 2;
        std::cout << LongestSubarrayAbsDiffSmallerThan(arr, k) << "\n";  // 3 (1,2,3)
    }
}

/*
Key Notes:

    "Absolute difference between any two elements is less than or equal to limit" is basically
        => "Absolute difference between min and max elements of subarray"

    Now the question becomes => find the longest subarray in which the absolute difference between min and max is less than or equal to limit.
     What we can do is to have two pointers: left and right,
     and then find the longest subarray for every right pointer (iterate it) by shrinking left pointer. And return the longest one among them.

    Let's work on sliding window max first. How to efficiently find 239. sliding window maximum?
    By using max Deque. We maintain list of max element candidates in monotonically decreasing order.
     Everytime the right pointer reaches a new position, we need to dequeue the "tail" element who is smaller than the nums[right].
     Since, those "old small tail" elements will never be the range maximum from now on. After "clean up" the "old small tail" elements,
     add nums[right] into the deque, and then, the head of deque is the current maximum.

    Same for the min Deque. Move right poniter by 1, and clean up "old big tail" elements, add nums[right], the head of deque is the current minimum.

    What we should do next is to shrink left pointer because of limit. If current.max - current.min > limit.
     We should move the left pointer. Accordingdly, we need to update our min max deques. If head of max deque is equal to the nums[left],
     that means, it is the one, we need to dequeue it, since we are gonna move the left pointer by 1. (Note: nums[left] will be never larger than head of max deque, and if nums[left] is smaller than the head, we good, keep moving left pointer until satisfying the limit).

Deque<Integer> maxDeque = new LinkedList<>();
Deque<Integer> minDeque = new LinkedList<>();

int res = 1;

int l = 0;

// find the longest subarray for every right pointer by shrinking left pointer
for (int r = 0; r < nums.length; ++r) {

	// update maxDeque with new right pointer
	while (!maxDeque.isEmpty() && maxDeque.peekLast() < nums[r]) {
		maxDeque.removeLast();
	}
	maxDeque.addLast(nums[r]);

	// update minDeque with new right pointer
	while (!minDeque.isEmpty() && minDeque.peekLast() > nums[r]) {
		minDeque.removeLast();
	}
	minDeque.addLast(nums[r]);

	// shrink left pointer if exceed limit
	while (maxDeque.peekFirst() - minDeque.peekFirst() > limit) {
		if (maxDeque.peekFirst() == nums[l]) maxDeque.pollFirst();
		if (minDeque.peekFirst() == nums[l]) minDeque.pollFirst();
		++l;  // shrink it!
	}

	// update res
	res = Math.max(res, r - l + 1);
}

return res;
*/
