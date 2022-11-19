class Solution {
public:
// as a math, there is the permutation of (m-1 1s and n-1 0s) C_m+n-2^m-1 = (m+n-2)!/[(m-1)!(n-1)!] = (m+n-2)*...m / n! but could be overflow 
    int uniquePaths(int m, int n) {
        vector<vector<int> > intermediate(m, vector<int>(n, 0));
        for (int ii = 0; ii < m; ++ii) {
            intermediate[ii][0] = 1;
        }
        for (int jj = 0; jj < n; ++jj) {
            intermediate[0][jj] = 1;
        }
        
        for (int ii = 1; ii < m; ++ii)
        for (int jj = 1; jj < n; ++jj) {
            intermediate[ii][jj] = intermediate[ii-1][jj] + intermediate[ii][jj-1];
        }
        
        return intermediate[m-1][n-1];
    }
};