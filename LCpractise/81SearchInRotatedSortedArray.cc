class Solution {
public:
// recusively called when found duplication, if no duplciation, normal binary recursively call
    bool search(vector<int>& nums, int target) {
        int idx = search(nums, 0, nums.size()-1, target);
        if (idx >=0 ) return true;
        return false;
    }
    
private:
    int search(const vector<int>& nums, size_t begin, size_t end, int target) {
        if (nums.empty()) return -1;
        if (nums.size() == 1) return nums[0] == target? 0:-1;
        if (end == begin) return nums[begin] == target? begin:-1;
        if (end - begin == 1) { // try to avoid to put mid overlap with end that make the logic below complicate
            if (nums[begin] == target) return begin;
            if (nums[end] == target) return end;
            return -1;
        }
        
        size_t mid = begin + (end+1-begin)/2;
        if (nums[mid] == target) return mid;
        
        if (nums[begin] == nums[mid] && nums[mid] == nums[end]) {
            return max(search(nums, begin, mid-1, target), search(nums, mid+1, end, target));
        } else if (nums[begin] == nums[mid] && nums[mid] > nums[end]) { // second condition is by product
            return search(nums, mid+1, end, target);
        } else if (nums[mid] == nums[end] && nums[begin] > nums[mid]) {
            return search(nums, begin, mid-1, target);
        } else {// no duplication at the three check points or non-descending with possible duplication
            if (nums[mid] >= nums[begin] && nums[mid] <= nums[end]) {// ascending complete
                if (nums[mid] > target) return search(nums, begin, mid-1, target);
                return search(nums, mid+1, end, target);
            } else if (nums[mid] > nums[begin] && nums[mid] > nums[end]) {//left ascending, right rotate
                if (target >= nums[begin] && target < nums[mid]) return search(nums, begin, mid-1, target);
                return search(nums, mid+1, end, target);
            } else if (nums[mid] < nums[begin] && nums[mid] < nums[end]) {//left rotate, right ascending
                if (target > nums[mid] && target <= nums[end]) return search(nums, mid+1, end, target);
                return search(nums, begin, mid-1, target);
            }
        }
        return -1;
    }
};
