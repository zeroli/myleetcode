class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int ii = 0;
        while (ii < nums.size()-1 && nums[ii+1] > nums[ii]) ++ii;
        return ii;
    }
};