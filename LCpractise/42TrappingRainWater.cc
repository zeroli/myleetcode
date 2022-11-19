class Solution {
public:

    int trap(vector<int>& height) {
        return trap1(height);
    }

private:
//test cases: ascending, descending, ascending + descending + ...
// method 2: remember the left maximums so far, and if at i-th it drops, keep moving, once it increases, the water level increase, check the addition volume of water increases: O(1) space, 1 loop
// the left maximums needed to record: all maximums in the descending order on the right
// addition volume: check between the left maximum which is higher than cur and cur: (not so trivial??)
    int trap2(const vector<int>& height) {
    }

// method 1: for each location, get the maximums on the left and right, and the water depth is the min of the two maximums: O(n) space and 2 loop
    int trap1(const vector<int>& height) { // works
        if (height.empty()) return 0;
        int n = height.size();
        vector<int> leftMax(n, INT_MIN);
        vector<int> rightMax(n, INT_MIN);
        for (int ii = 1; ii < n; ++ii){
            leftMax[ii] = max(leftMax[ii-1], height[ii-1]);
            rightMax[n-1-ii] = max(rightMax[n-ii], height[n-ii]);
        }

        int r = 0;
        for (int ii = 1; ii < n-1; ++ii) {
            r += max(0, min(leftMax[ii], rightMax[ii]) - height[ii]);
        }
        return r;
    }
};