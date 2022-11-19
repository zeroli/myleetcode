class Solution {
public:
// one way to avoid duplciation is to use map or Hash to check whether it has been visited in addition to the normal one without duplication
// method 2: (1) Swap the 1st element with all the elements, including itself.
       //   (2) Then the 1st element is fixed, go to the next element.
       //   (3) Until the last element is fixed. Output.
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        if (nums.empty()) return vector<vector<int> >();
        vector<vector<int> > r;
        if (nums.size() == 1) {
            r.push_back(nums);
            return r;
        }
        
        permute(&nums[0], nums.size(), nums.size(), r);
        return r;
    }

    void permute(int* nums, int n, int tn, vector<vector<int>>& r) {
        if (n == 1) {
            vector<int> element(nums, nums+tn);
            r.push_back(element);
        }
        // create a map to keep record whether it is a duplication
        map<int, int> visited;
        for (int ii = 0; ii < n; ++ii) {
            if (visited[nums[ii]] > 0) continue; // skip
            visited[nums[ii]] = 1; // set it to be visited
            swap(nums[ii], nums[n-1]);
            permute(&nums[0], n-1, tn, r);
            swap(nums[ii], nums[n-1]);// swap back to kee the same order
        }
    }
};