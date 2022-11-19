class Solution {
public:
// solution 1: like reverse words in a string: Here one can treat the two parts as two different words, and do revert string first, and then revert word: 1234567 =? 7654321 => 5671234
// solution 2: cut the arrays into multiple blocks with each block the size of k, and swap block by block, call rotate on the residual block
// solution 3: rotate one by one, O(n*k)
    void rotate(int nums[], int n, int k) {
        k = k % n; // k could be negative
        if (k < 0) k += n; 
        if (k == 0) return;
        if (k == 1) {
            for (unsigned int ii = n - 1; ii > 0; --ii){
                swap(nums[ii], nums[ii - k]);
            }
            return;
        }
        if (k > n/2) k -= n; // make |n| >=2k, to enable the cut into blocks
        
        int blocks = n/abs(k); // swap between block
        for (unsigned int ii = 0; ii < (blocks - 1) * abs(k); ++ii){
            int idx = k > 0 ? n - 1 - ii : ii;
            swap(nums[idx], nums[idx - k]);
        }
        if (k > 0) rotate(nums, k + n % k, k); // deal with residual block
        if (k < 0) rotate(nums + (blocks -1) * abs(k), abs(k) + n % abs(k), k);
    }
    
    //method 1: revert the whole, and revert part
    void rotate1(vector<int>& nums, int k) {
       size_t n = nums.size();
       k %= n;
       if (k<0) k += n;
       for (int ii = 0; ii < n/2; ++ii) {
           swap(nums[ii], nums[n-1-ii]);
       }
       for (int ii = 0; ii < k/2; ++ii) {
           swap(nums[ii], nums[k-1-ii]);
       }
       for (int ii = 0; ii < (n-k)/2; ++ii) {
           swap(nums[ii+k], nums[n-1-ii]);
       }
    }

};