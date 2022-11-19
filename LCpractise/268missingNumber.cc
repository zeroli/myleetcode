class Solution {
public:
// if n not too big, use math, otherwise use sort
    int missingNumber(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return nums.size() * (nums.size()+1)/2 - sum;
    }
};