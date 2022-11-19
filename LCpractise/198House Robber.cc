class Solution {
public:
// the value for nums[0..i] must be maximum (value for nums[0..i-1], value for nums[0..i-2]+nums[i]) with the knowledge that if nums[i-1] not chosen, then nums[i] must be chosen
    int rob(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        if (nums.size() == 2) return max(nums[0], nums[1]);
        
        vector<int> allr(nums.size(), 0);
        allr[0] = nums[0];
        allr[1] = max(nums[0], nums[1]);
        
        for (int ii = 2; ii < nums.size(); ++ii) {
            allr[ii] = max(allr[ii-1], allr[ii-2]+nums[ii]);
        }
        return allr.back();
    }
};