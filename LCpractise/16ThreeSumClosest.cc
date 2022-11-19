class Solution {
public:
// for each one element, call find twoSumClosest, which run binary search
    int threeSumClosest(vector<int>& nums, int target) {
        if (nums.size() < 3) return INT_MAX;
        sort(nums.begin(), nums.end());
        
        int distance = INT_MAX;
        for (unsigned ii = 0; ii < nums.size()-2; ++ii) {
            int newtarget = target - nums[ii];
            int closestTwoSum = twoSumCloset(&nums[ii+1], nums.size()-ii-1, newtarget);
            if (abs(closestTwoSum) < abs(distance)) distance = closestTwoSum;
        }
        
        return distance + target;
    }
    
private:
    int twoSumCloset(int nums[], unsigned n, int target) {// return distance
        int left = 0; 
        int right = n-1;
        int dis = INT_MAX;
        
        while (right - left >= 1) {
            int cur_dis = nums[left] + nums[right] - target;
            if (cur_dis == 0) return 0;
            else if ( cur_dis < 0) ++left;
            else --right;
            if (abs(cur_dis) < abs(dis)) dis = cur_dis;
        }
        return dis;
    }
};