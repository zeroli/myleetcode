class Solution {
public:
// observation: going from right to left, if the subarray is ascending means this subarray is the maximum it can form, and if is decending means it is the minimum. Therefore try to find such ascending subarray, and swap the one at the left next to this subarray by the next largest number in this subarray (must be there), and revert the subarray to be descending
// special case: the whole array is descending => revert it;  there is no ascending subarray from right, swap the first rightest one with the one non-duplicate next to it (form descending)

// more clear algorithm:
// (a) Find the longest descending tail of the array and reverse them into ascending order.
// (b) If there is any number ahead of the descending tail, it should be replace with the first greater number in the tail.

    void nextPermutation(vector<int>& nums) {
        
        int end = nums.size()-1;
        while (end > 0 && nums[end] <= nums[end-1]) --end; // end points to the leftest of the subarray
        int left = end;
        int right = nums.size()-1;
        while (right > left) {
            swap(nums[left++], nums[right--]);
        }
        
        if (end == 0) return;
        else { // swap end-1 with the first right one larger
            int left = end;
            while (nums[left] <= nums[end-1]) left++;
            swap(nums[end-1], nums[left]);
        }
    }
};