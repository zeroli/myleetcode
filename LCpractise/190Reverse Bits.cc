class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t rn = 0;
        int total_bits = 32;
        for (unsigned int ii = 0; ii < total_bits; ++ii){
            rn += (n & 1 << ii)? 1 << total_bits - 1 - ii : 0;
        }
        return rn;
    }
};  