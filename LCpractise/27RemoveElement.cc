class Solution {
public:
// swap to the end
    int removeElement(int A[], int n, int elem) {
        if (n == 0) return 0;
        if (n == 1) return A[0] == elem? 0 : 1;
        
        int first_diff = n - 1;
        while (first_diff >= 0 && A[first_diff] == elem) --first_diff;
        int len = first_diff + 1;
        if (first_diff > 0) {
            for (int ii = first_diff - 1; ii >=0; --ii) {
                if (A[ii] == elem) {
                    swap(A[ii], A[first_diff--]);
                    --len;
                }
            }
            
        }
        return len;
    }
};