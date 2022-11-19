class Solution {
public:
// method 2: (1) Swap the 1st element with all the elements, including itself.
       //   (2) Then the 1st element is fixed, go to the next element.
       //   (3) Until the last element is fixed. Output.
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return vector<vector<int> >();
        vector<vector<int> > r;
        if (nums.size() == 1) {
            r.push_back(nums);
            return r;
        }
        
        //return permute(&nums[0], nums.size());
        permute(&nums[0], nums.size(), nums.size(), r);
        return r;
    }
    
    // below there are too many copy operations which leads to runtime problem, better to pass result through
    vector<vector<int>> permute(int* nums, int n) {
        vector<vector<int>> r;
        for (int ii = 0; ii < n; ++ii) {
            swap(nums[ii], nums[n-1]);
            vector<vector<int> > subr = permute(&nums[0], n-1); // too many copies
            for (int jj = 0; jj < subr.size(); ++jj) {
                subr[jj].push_back(nums[n-1]);
            }
            r.insert(r.end(), subr.begin(), subr.end());
            swap(nums[ii], nums[n-1]);// swap back to kee the same order
        }
    }
    // improved version
    void permute(int* nums, int n, int tn, vector<vector<int>>& r) {
        if (n == 1) {
            vector<int> element(nums, nums+tn);
            r.push_back(element);
        }
        for (int ii = 0; ii < n; ++ii) {
            swap(nums[ii], nums[n-1]);
            permute(&nums[0], n-1, tn, r);
            swap(nums[ii], nums[n-1]);// swap back to kee the same order
        }
    }
    
// method 1: r(n) = insert n into the n intervals of each result of r(n-1)
/* runtime error, why?
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return vector<vector<int> >();
        vector<vector<int> > r;
        if (nums.size() == 1) {
            r.push_back(nums);
            return r;
        }
        
        permute(&nums[0], nums.size(), r);
        return r;
    }
    
    void permute(int nums[], int n, vector<vector<int>>& r) {
        if (n == 1) {
            r.push_back(vector<int>(1, nums[0]));
            return;
        }
        
        permute(nums, n-1, r);
        for (int ii = 0; ii < r.size(); ++ii) {//expand each vector in r to be n vectors by insert nums[n-1]
            vector<int>& v = r[ii];
            for (auto it = v.begin(); it != v.end(); ++it) {
                vector<int> e(v);
                e.insert(it, nums[n-1]);
                r.push_back(e);
            }
            v.push_back(nums[n-1]);
        }
    }
*/
/*       
    vector<vector<int>> permute(vector<int>& nums) {
        if (nums.empty()) return vector<vector<int> >();
        vector<vector<int> > r;
        if (nums.size() == 1) {
            r.push_back(nums);
            return r;
        }
        
        return permute(&nums[0], nums.size());
    }
    
    vector<vector<int>> permute(int nums[], int n) {
        vector<vector<int> > r;
        if (n == 1) {
            r.push_back(vector<int>(1, nums[0]));
            return r;
        }
        
        vector<vector<int> > r1 = permute(nums, n-1);
        for (int ii = 0; ii < r1.size(); ++ii) {//expand each vector in r1 to be n vectors by insert nums[n-1]
            vector<int>& v = r1[ii];
            for (auto it = v.begin(); it != v.end(); ++it) {
                vector<int> e(v);
                e.insert(it, nums[n-1]);
                r.push_back(e);
            }
            v.push_back(nums[n-1]);
            r.push_back(v);
        }
        
        return r;
    }
*/
};