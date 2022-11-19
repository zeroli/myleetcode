class Solution {
public:
// binary search
    int searchInsert(vector<int>& nums, int target) {
        if (nums.empty() || nums[0] >= target) return 0;
        if (nums.back() < target) return nums.size();
        
        return searchInsert(&nums[0], target, 0, nums.size());
    }
    
private:
    int searchInsert(int nums[], int target, int begin, int end) {
        if (end-begin <=0) return begin;
        if (nums[begin] >= target) return begin;
        if (nums[end-1] < target) return end;
        
        int mid = begin + (end-begin)/2; 
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) return searchInsert(nums, target, mid, end);
        if (nums[mid] > target) return searchInsert(nums, target, begin, mid);
    }
};