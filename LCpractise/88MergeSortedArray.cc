class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        if (n == 0) return;
        if (m == 0) {
            for (int ii = 0; ii < n; ++ii) {
                A[ii] = B[ii];
            }
            return;
        }
        
        int idxA = m - 1;
        int idxB = n - 1;
        int idxT = m + n - 1;
        while (idxB >= 0) {
            while (idxB >=0 && (idxA < 0 || A[idxA] < B[idxB])) {
                A[idxT--] = B[idxB--];
            }
            while (idxA >=0 && A[idxA] >= B[idxB]) {
                A[idxT--] = A[idxA--];
            }
        }
    }
};