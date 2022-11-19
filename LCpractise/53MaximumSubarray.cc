class Solution {
public:
// similar to the stock buy/sell: keep a record of sum end with current, and a record of max sum so far
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        
        int cursum = nums[0];
        int maxsum = nums[0];
        for (int ii = 1; ii < nums.size(); ++ii) {
            cursum = max(cursum + nums[ii], nums[ii]);
            maxsum = max(maxsum, cursum);
        }
        return maxsum;
    }
};