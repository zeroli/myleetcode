class Solution {
public:
// going from two sides, and compare the volume with max, when move inside, the lower one move first
    int maxArea(vector<int>& height) {
        if (height.empty() || height.size() == 1) return 0;
        int istart = 0;
        int iend = height.size()-1;
        int maxv = 0;
        
        while (iend - istart >= 1) {
            int newv = min(height[istart], height[iend]) * (iend - istart);
            maxv = max(maxv, newv);
            if (height[istart] < height[iend]) ++istart;
            else --iend;
        }
        return maxv;
    }
};