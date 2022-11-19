class Solution {
public:
    int hammingWeight(uint32_t n) {
        int total_bits = 32;
        int count = 0;
        for (unsigned int ii = 0; ii < total_bits; ++ii){
            if(n & 1 << ii) count++;
        }
        return count;
    }
};