class Solution {
public:
// swap to end
    int removeDuplicates(int A[], int n) {
        if (n == 0 || n == 1) return n;
        if (A[0] == A[n-1]) return 1;
        
        int ii = 0;
        while (ii < n) {
            int val = A[ii];
            while (ii < n-1 && A[ii+1] == val) {
                A[ii+1] = INT_MAX;
                ++ii;
            }
            ++ii;
        }
        
        int len = 0;
        ii = 0; //mark next val = INT_MAX
        int jj = 0; // mark next val != INT_MAX
        while (ii < n && jj < n) {
            while (ii < n && A[ii] != INT_MAX) {// find coming INT_MAX
                ++ii;
                ++len;
            }
            jj = max(ii + 1, jj);
            while (jj < n && A[jj] == INT_MAX) ++jj; // find next distinct val not INT_MAX
            if (jj < n) swap(A[ii], A[jj]);
        }
        return len;
    }
};