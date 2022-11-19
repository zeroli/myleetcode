class Solution {
public:
// if mid = target, ok
// if target in between one zone, search it, else search other zone, target could be in array but not in the zone
// the key here is to find the zone according to the boundary and mid condition
 
    int search(vector<int>& nums, int target) {
        if (nums.empty()) return -1;
        if (nums.size() == 1) return nums[0] == target ? 0:-1;
        
        return search(&nums[0], target, 0, nums.size());
    }
    
private:
    // method 1
    int search(int nums[], int target, int begin, int end) {
        if (end <= begin) return -1;
        if (end - begin == 1 && nums[begin] != target) return -1;
        
        int mid = begin + (end-begin)/2; // if size odd: point to center, even: point to right one
        if (nums[mid] == target) return mid;
        if (nums[begin] < nums[mid]) {
            if (nums[begin] <= target && target < nums[mid]) {
                return search(&nums[0], target, begin, mid);
            } else {
                return search(&nums[0], target, mid, end);
            }
        } else {
            if (nums[mid] < target && target <= nums[end-1]) {
                return search(&nums[0], target, mid, end);
            } else {
                return search(&nums[0], target, begin, mid);
            }
        }
    }
    
    // method 2
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
        if (nums[mid] > nums[begin] && nums[mid] <= nums[end]) {// ascending complete
            if (nums[mid] > target) return search(nums, begin, mid-1, target);
            return search(nums, mid+1, end, target);
        } else if (nums[mid] > nums[begin] && nums[mid] > nums[end]) {//left ascending, right rotate
            if (target >= nums[begin] && target < nums[mid]) return search(nums, begin, mid-1, target);
            return search(nums, mid+1, end, target);
        } else if (nums[mid] < nums[begin] && nums[mid] < nums[end]) {//left rotate, right ascending
            if (target > nums[mid] && target <= nums[end]) return search(nums, mid+1, end, target);
            return search(nums, begin, mid-1, target);
        }
        return -1;
    }


};