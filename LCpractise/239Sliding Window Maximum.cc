class Solution {
public:
// use a queue to store the nondescent subsequence of the current window, when front move out the window, pop it, and when the coming number higher than some numbers incide the queue, update queue
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> r;
        if (nums.empty()) return r;
        deque<int> que;
        
        // initialize
        que.push_back(0);
        for (unsigned ii = 1; ii < k; ++ii) {
            while (!que.empty() && nums[ii] > nums[que.back()])  que.pop_back();
            if (que.empty() || nums[ii] <= nums[que.back()]) que.push_back(ii);
        }
        r.push_back(nums[que.front()]);
        
        // update
        for (unsigned ii = k; ii < nums.size(); ++ii) {
            if (ii - que.front() >=k ) que.pop_front(); //pop out if outside the window
            while (!que.empty() && nums[ii] > nums[que.back()])  que.pop_back(); // keep non ascending
            if (que.empty() || nums[ii] <= nums[que.back()]) que.push_back(ii);
            r.push_back(nums[que.front()]);
        }
        
        return r;
    }
};