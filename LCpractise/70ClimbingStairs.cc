class Solution {
public:
    int climbStairs(int n) {
        vector<int> A(n+1, 1);
        for (int ii = 2; ii < n+1; ++ii) {
            A[ii] = A[ii-1] + A[ii-2];
        }
        return A[n];
    }
};