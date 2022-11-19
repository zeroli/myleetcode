class Solution {
public:
//recursively call subsetsSorted, by first generate the sets for the first n-1 elements, and then expand these sets with the last element, and merge all these sets
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int> > r;
        if (nums.empty()) {
            r.push_back(vector<int>());
            return r;
        }
        
        sort(nums.begin(), nums.end());
        return subsetsSorted(&nums[0], nums.size());
    }
    
private:
    vector<vector<int>> subsetsSorted(int nums[], unsigned n) {
        vector<vector<int>> r;
        if (n == 0)  {
            r.push_back(vector<int>());
            return r;
        }
        
        vector<vector<int>> sr= subsetsSorted(&nums[0], n-1);
        for (vector<vector<int>>::iterator it = sr.begin(); it != sr.end(); ++it) {
            r.push_back(*it);
            it->push_back(nums[n-1]);
            r.push_back(*it);
        }
        
        return r;
    }
};