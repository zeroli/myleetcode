class Solution {
public:
// observation: if there is a chain that start from begin end with end, then works, so we can backward search the chain, the first one can reach the end, and find the second one can reach the first one. one observation for that is if end can be reached, then any one before that can be reached
    bool canJump(vector<int>& nums) {
        if (nums.size() <= 1) return true;
        int next = nums.size()-1;
        for (int ii = nums.size()-2; ii>=0; --ii) {
            if (nums[ii] >= next-ii) {// can reach next from ii
                next = ii;
            }
        }
        return next==0;
    }

};