class Solution {
public:
// use the returned vector space to store first the left product, and then multiple by the right product
    vector<int> productExceptSelf(vector<int>& nums) {
        if (nums.empty()) return vector<int>();
        vector<int> r(nums.size(), 1);
        
        int temp = 1;
        for (int ii = 1; ii < nums.size(); ++ii) {
            temp *= nums[ii-1];
            r[ii] = temp;
        }
        
        temp = 1;
        for (int ii = nums.size()-2; ii >= 0; --ii) {
            temp *= nums[ii+1];
            r[ii] *= temp;
        }
        
        return r;
    }
};