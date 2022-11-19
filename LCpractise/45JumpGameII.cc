class Solution {
public:
// ...http://n00tc0d3r.blogspot.com/2013/03/jump-game.html
    int jump(vector<int>& nums) {
        return jump3(nums);
    }
// method3: 
// The basic idea is each time when we jump, we jump to the farthest slot.
//Start from slot i,
//next is the next position where we will jump from, so it starts from 0.
//maxr is the farthest position we can reach so far, so every time when we jump, we set next to current maxr. 
// why it works for like: 2 100 0 1

    int jump3(const vector<int>& A) {
        int steps = 0;  
        int maxr = 0;
        int next = 0;
       for (int i=0; i<A.size()-1 && next<A.size()-1; ++i) {  
         maxr = max(maxr, i+A[i]); // max postion can be reached from i
         if (i == next) {  // ready to jump  from next
           if (maxr == next) return -1; // unreachable  
           next = maxr;  // set new next as maxr
           ++steps;  
         }  
       }  
       return steps; 
    }

// method2: find the leftest one that can jump once to the end, and set it as new end, but runtime O(n^2) since to find the leftest one is O(n)
// method1: if A[i] is the minum number of jumps from begin to i, and A[i+1] is the min of all A[j]+1 if nums[j] >= i-j
// this is O(n^2)
    int jump1(const vector<int>& nums) {
        if (nums.size() == 1) return 0;
        vector<int> A(nums.size(), INT_MAX);
        for (int ii = 1; ii < A.size(); ++ii) {
            for (int jj = 0; jj < ii; ++jj) {
                if (A[jj] >= ii-jj) A[ii] = min(A[ii], A[jj]+1); //can reach ii from jj 
            }
        }
        return A.back();
    }
};