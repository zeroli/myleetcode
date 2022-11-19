class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int, int> count;
        for (unsigned ii = 0; ii < nums.size(); ++ii) {
            count[nums[ii]] += 1;
            if (count[nums[ii]] > 1) return true;
        }
        return false;
    }
};