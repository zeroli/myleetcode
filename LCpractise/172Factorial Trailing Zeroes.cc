class Solution {
public:
// observation: the number of 2 is more than the number of 5, therefore the number of 5 is same as the number of 10. recursively divide the number by 5 to shrink the zone 
    int trailingZeroes(int n) {
        int r = 0;
        while (n >= 5) {
            r += n/5;
            n /= 5;
        }
        return r;
    }
};