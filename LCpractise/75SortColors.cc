class Solution {
public:
// two pass: count first and then sort
// one pass: set two indices to track the left first not 0 and right first not 2, whenever meet 0 swap to left, meet 2 swap to right
    void sortColors(vector<int>& nums) {
        
        int redidx = 0;
        int blueidx = nums.size()-1;// the next idx where blue will be set if necessary
        int ii = 0;
        while(ii < blueidx+1) {
            if (nums[ii] == 0) {
                swap(nums[ii++], nums[redidx++]);
                continue;
            } else if (nums[ii] == 2) {
                swap(nums[ii], nums[blueidx--]);
                continue;
            }
            ii++;
        }
    }

};