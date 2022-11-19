class Solution {
public:
// use XOR to annihilate the elements show twice
// extension how to mark some elements show three times, 
    int singleNumber(vector<int>& nums) {
        int A = nums[0];
        for (unsigned ii = 1; ii < nums.size(); ++ii) A ^= nums[ii];
        return A;
    }
};