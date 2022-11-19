class Solution {
public:
// label 2x as non-prime, then label 3x as non-prime, then 5x as nonprime (x>1), until reach n
    int countPrimes(int n) {
        if (!n) return 0;
        vector<int> isprime(n, 1);
        isprime[0] = 0;
        isprime[1] = 0;
        
        for (unsigned ii = 2; ii*ii < n; ++ii) { // sqrt(n) will be the maximum of minimal of a pair doe multiply for a number, ii is the factor (larger one)
            if (!isprime[ii]) continue; // only do the following for prime ii
            for(unsigned idx = ii+ii; idx < n; idx+=ii) isprime[idx] = 0; // the ones devided by ii
        }
        return accumulate(isprime.begin(), isprime.end(), 0);
    }
};