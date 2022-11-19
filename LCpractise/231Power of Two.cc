class Solution {
public:
// watch for n=0
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        //if (n == INT_MIN) return true;
        //if (n < 0) return isPowerOfTwo(-n);
        return !(n&(n-1));
    }
};