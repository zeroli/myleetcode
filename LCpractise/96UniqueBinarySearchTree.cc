class Solution {
public:
// the relation beteen the result for n and for n-1:
// a[n]: 2 * a[n-1] (n as root, and 1 as root) + j+1 as root: a[j] * a[n-j-1]
    int numTrees(int n) {
        if (n <= 1) return 1;
        vector<int> A(n+1, 0);
        A[1] = 1;
        
        for (int ii = 2; ii < n+1; ++ii) {
            A[ii] = 2*A[ii-1];
            for (int jj = 1; jj < ii-1; ++jj) {
                A[ii] += A[jj] * A[ii-jj-1];
            }
        }
        return A[n];
    }
};