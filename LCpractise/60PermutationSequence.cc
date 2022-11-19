class Solution {
public:
// observation: the first digit starting with m is ranged from [(m-1)*(n-1)!, m(n-1)!), and the second one starting with k is ranged [(k-1)*(n-2)!, k(n-2)!], et al., therefore we can decomposite k into a serial of such index to find the final value; k starts from 1, need to convert it to 0-based
// Note that once a number is used, it should be removed from the candidate list
    string getPermutation(int n, int k) {
        if (n == 1 && k == 1) return "1";
        vector<int> candidates(n, 0);
        vector<int> setn(n, 1);
        for (int ii = 0; ii < n; ++ii) candidates[ii] = ii+1;
        for (int ii = 1; ii < n; ++ii) setn[ii] = setn[ii-1]*ii;
        int residual = k-1; // starting from 0
        string r;
        for (int idx = n-1; idx >=0; --idx) {
            int numidx = residual/setn[idx];
            r += '0' + candidates[numidx];
            candidates.erase(candidates.begin() + numidx); // remove this number, and shift numbers behind forward
            residual %= setn[idx];
        }
        return r;
    }
};