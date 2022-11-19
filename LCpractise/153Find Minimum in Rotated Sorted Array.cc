class Solution {
public:
// if no duplication, then the minimal is either the first element or the element smaller than previous one
// if duplicaiton allowed, there may be no clue left or right will be searched next, so both needs to be done, complexicity becomes O(n), or use extral O(n) space to remove the duplication and then do the search
    int findMin(vector<int>& nums) {
        if (nums.size() == 1 || nums[0] < nums.back()) return nums[0];
        
        return findMin(&nums[0], 0, nums.size());
    }
    
private:
    int findMin(int nums[], unsigned begin, unsigned end) {
        if (begin == end-1) return nums[begin];
        if (nums[begin] < nums[end-1]) return nums[begin];

        unsigned mid = begin + (end-begin)/2; // if end-begin: odd, mid is the mid, if end-begin even, mid is the one on the right side
        if (nums[mid] < nums[mid-1]) return nums[mid];
        if (nums[mid] > nums[mid-1])  {
            if (nums[mid] > nums[begin]) return findMin(&nums[0], mid, end);
            if (nums[mid] < nums[begin]) return findMin(&nums[0], begin, mid);
        }
    }
    
    // method 2    
    int findMin(const vector<int>& nums, size_t begin, size_t end){ // [begin, end] is the close region
        if (nums[begin] < nums[end] || begin == end) return nums[begin];
        if (end-begin == 1) return min(nums[begin], nums[end]); // avoid inifinity recursive when there are two elements
        size_t mid = begin + (end+1-begin)/2; // point to the midd for odd or after mid space for even
        if (nums[mid] > nums[begin]) {
            return findMin(nums, mid+1, end);
        }
        return findMin(nums, begin, mid);
    }

};