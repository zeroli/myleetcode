class Solution {
public:
// if the last one not selected, then the result is the same as circle break by removing the last one
// if the last one forced to be selected, then the first one not selected, ie.e circle break by remove the first one, 
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return max(rob(&nums[0], n-1), rob(&nums[1], n-1));
    }
    
//
private:
    int rob(int nums[], int n) {
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        if (n == 2) return max(nums[0], nums[1]);
        
        vector<int> allr(n, 0);
        allr[0] = nums[0];
        allr[1] = max(nums[0], nums[1]);
        
        for (int ii = 2; ii < n; ++ii) {
            allr[ii] = max(allr[ii-1], allr[ii-2]+nums[ii]);
        }
        return allr.back();
    }
};