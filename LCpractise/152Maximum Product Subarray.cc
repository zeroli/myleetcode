class Solution {
public:
    // could be postion, negative, and 0
    // need to have two arrays one to store min, and the other one to store max, 
    // MIN[ii] = min( min[ii-1]*a[ii] : max[ii-1]*a[ii])
    // Max[ii] = max( min[ii-1]*a[ii] : max[ii-1]*a[ii])
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        if (nums.size() == 1) return nums[0];
        //if (nums.size() == 2) return max(max(nums[0], nums[1]), nums[0]*nums[1]);
        
        vector<int> mins(nums.size(), 0);
        vector<int> maxs(nums.size(), 0);
        mins[0] = nums[0];
        maxs[0] = nums[0];
        for (int ii = 1; ii < nums.size(); ++ii) {
            if (mins[ii-1] != 0) { // min and max must be 0 simulatanously
                mins[ii] = min(nums[ii], min(mins[ii-1]*nums[ii], maxs[ii-1]*nums[ii])); // need to include curr val as a possible new start
                maxs[ii] = max(nums[ii], max(mins[ii-1]*nums[ii], maxs[ii-1]*nums[ii]));
            } else {
                mins[ii] = nums[ii];
                maxs[ii] = nums[ii];
            }
        }
        return *max_element(maxs.begin(), maxs.end());
    }
};