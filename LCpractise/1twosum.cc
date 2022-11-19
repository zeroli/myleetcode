class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> snums = nums;
        sort(snums.begin(), snums.end());
        int left = 0;
        int right = snums.size()-1;
        
        while (right - left >= 1) {
            int sum = snums[left] + snums[right] - target;
            if (sum == 0) break;
            if (sum > 0) --right;
            else ++left;
        }
        
        int idx1 = -1;
        for (unsigned ii = 0; ii < nums.size(); ++ii) {
            if (nums[ii] == snums[left] || nums[ii] == snums[right]) {idx1 = ii; break;}
        }
        int idx2 = -1;
        for (unsigned ii = idx1+1; ii < nums.size(); ++ii) {
            if (nums[ii] == snums[left] || nums[ii] == snums[right]) {idx2 = ii; break;}
        }
        
        vector<int> A(1,++idx1);
        A.push_back(++idx2);
        return A;
    }
};