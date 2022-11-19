class Solution {
public:
// observation: only the first highest common bits will contribute the final bit AND, since other bit site will always be flipped within the range
    int rangeBitwiseAnd(int m, int n) {
        if (n == m) return m;
        int comm = 0;
        int k = 31;
        while ((n&1<<k) == (m&1<<k)) {
            comm += n&1<<k;
            --k;
        }
        return comm;
    }
};