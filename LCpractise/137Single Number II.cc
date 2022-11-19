class Solution {
public:
// get the bit result for show up odd times, and also the one for show up >=2 times, remove the common part
    int singleNumber(vector<int>& nums) {
        int ones = 0; // bit shows up odd times
        int twos = 0; // bit shows up even, even + 1 times
        for (unsigned ii = 0; ii < nums.size(); ++ii) {
            twos |= ones & nums[ii]; // show even times and even + times ??
            ones ^= nums[ii]; // show odd times
            int threes = ones & twos; // get show 3 times
            ones &= ~threes; // remove show 3 times
            twos &= ~threes; // remove show 3 times
        }
        return ones;
    }
};