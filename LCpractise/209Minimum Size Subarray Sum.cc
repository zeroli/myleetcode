class Solution {
public:
// keep a two indices for the beginning and ending of the window, and shrink from left or expand to right depends the sum 
    int minSubArrayLen(int s, vector<int>& nums) {
        if (nums.empty()) return 0;
        
        unsigned start = 0;
        unsigned end = 0;
        unsigned min_len = nums.size()+1;
        
        int cur_sum = 0;
        while (end < nums.size()) {
            while (cur_sum < s && end < nums.size()) {
                cur_sum += nums[end];
                ++end;
            }
            
            while (cur_sum >=s && start <= end) {
                min_len = min(min_len, end - start);
                cur_sum -= nums[start];
                ++start;
            }
        }
        return min_len > nums.size()? 0:min_len;
    }
};