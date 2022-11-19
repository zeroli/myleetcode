class Solution {
public:
// if no duplication, then the minimal is either the first element or the element smaller than previous one
// if duplicaiton allowed, there may be no clue left or right will be searched next, so both needs to be done, complexicity becomes O(n)
    int findMin(vector<int>& nums) {
        if (nums.size() == 1 || nums[0] < nums.back()) return nums[0];
        
        return findMin(&nums[0], 0, nums.size());
    }
    
private:
// method 1: 
    int findMin(int nums[], unsigned begin, unsigned end) {
        if (end - begin == 1) return nums[begin];
        if (end - begin == 2) return min(nums[begin], nums[end-1]);
        if (nums[begin] < nums[end-1]) return nums[begin];
        
        {
            unsigned mid = begin + (end-begin)/2; // if end-begin: odd, mid is the mid, if end-begin even, mid is the one on the right side
            if (nums[mid] < nums[mid-1]) return nums[mid];
            if (nums[mid] == nums[mid-1]) {
                int cur = mid-1;
                while (cur >= begin && nums[cur] == nums[mid]) --cur;
                if (cur >= begin && nums[cur] > nums[mid]) return nums[mid];
                // all left not larger: go below
                return findMin(&nums[0], mid, end);
            }
            if (mid+1 < end && nums[mid] == nums[mid+1]) {
                int cur = mid+1;
                while (cur < end && nums[cur] == nums[mid]) ++cur;
                if (cur < end && nums[cur] < nums[mid]) return nums[cur];
                // all right not lesser: go below
                return findMin(&nums[0], begin, mid);
            }
            if (nums[mid] > nums[mid-1])  {
                if (nums[mid] > nums[begin]) return findMin(&nums[0], mid, end);
                if (nums[mid] < nums[begin]) return findMin(&nums[0], begin, mid);
            }
        }
    }
// method2:
// key observation: begin will never less than end except complete ascending
// recursive if found duplciaiton at check points
    int findMin(const vector<int>& nums, size_t begin, size_t end){ // [begin, end] is the close region
        if (nums[begin] < nums[end] || begin == end) return nums[begin];
        if (end-begin == 1) return min(nums[begin], nums[end]); // avoid inifinity recursive when there are two elements
        size_t mid = begin + (end+1-begin)/2; // point to the midd for odd or after mid space for even
        
        if (nums[mid] == nums[begin] && nums[mid] == nums[end]) {
            return min(findMin(nums, begin, mid-1), findMin(nums, mid, end));
        } else if (nums[mid] == nums[begin]) {// must on the right (not include mid)
            return findMin(nums, mid+1, end);
        } else if (nums[mid] == nums[end]) {//nmust on the left or mid
            return findMin(nums, begin, mid);
        } else if (nums[mid] > nums[begin]) {
            return findMin(nums, mid+1, end);
        } else {
            return findMin(nums, begin, mid);
        }
    }

};