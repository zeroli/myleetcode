class Solution {
public:
// if use one binary search to find one location with target value, and then move backward and forward, thew worst situation will be O(n)
// better to use two binary searches to find the left and right edge 
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> r;
        
        // find the lower bound
        int start = 0;
        int end = nums.size()-1;
        while (start < end) {
            int mid = start + (end - start)/2;
            if (nums[mid] < target) start = mid + 1;
            else {end = mid;}
        }
        int low_bound = -1;
        if (nums[start] == target) low_bound = start;
        if (low_bound == -1) {
            r.assign(2, -1);
            return r;
        }
        r.push_back(start);
        
        end = nums.size()-1;
        while (start < end) {
            int mid = start + (end - start)/2;
            if (nums[mid] <= target) start = mid + 1;
            else {end = mid;}
        }
        // if the last element == target and the second last element == target, end = last locaiton
        int high_bound = end;
        if (nums.back() != target) {
           high_bound = end-1;
        }
        r.push_back(high_bound);
        
        return r;
    }
};