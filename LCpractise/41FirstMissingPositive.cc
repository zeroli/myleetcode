class Solution {
public:
// swap on local, A[i] to i, if A[i]>n set it to be negative, if duplicate, set the duplication to be -1, 
// if >n or <=0, set it to be negative
// if duplication, set it to be negative
// first transverse: do the swap, 
// second transverse: check the missing
// NOTE to avoid the step forward directly when do the swap
    int firstMissingPositive(vector<int>& nums) {
         if (nums.empty()) return 1;
         vector<int>& A = nums;
         int ii = 0;
         while (ii < A.size()) {
             if (A[ii] > A.size()) { A[ii] = -1;}
             else if (A[ii] > 0) { // do the swap
                if (ii != A[ii]-1) { // not the same loc
                    if (A[ii] != A[A[ii]-1]) {// swap only if not duplicate
                        swap(A[ii], A[A[ii]-1]); 
                        continue; // no ++ii, still work on the same location
                    }
                    else { A[ii] = -1;}
                } 
             } else if (A[ii] <=0) { A[ii] = -1;}
             ++ii;
         }
         
         for (int ii = 0; ii < A.size(); ++ii) {
             if (A[ii] == -1) return ii+1;
         }
         return A.size()+1;
    }
};