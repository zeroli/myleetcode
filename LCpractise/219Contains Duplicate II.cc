class Solution {
public:
    // hash the locs for each val into a set and find the distance
    // better use a k-size window, and hash the locs/count only inside the shift k size window
    
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, vector<unsigned> > locs;
        for (unsigned ii = 0; ii < nums.size(); ++ii) {
            locs[nums[ii]].push_back(ii);
        }
        
        for (map<int, vector<unsigned>>::const_iterator it = locs.begin(); it != locs.end(); ++it) {
            if (it->second.size() < 2) continue;
            const vector<unsigned>& vloc = it->second;
            for (unsigned ii = 0; ii < vloc.size()-1; ++ii) {
                if (vloc[ii+1] - vloc[ii] <= k) return true;
            }
        }
        return false;
    }
};