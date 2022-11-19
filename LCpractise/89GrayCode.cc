class Solution {
public:
// observation: the relation between result for n and n-1 is that the result of n-1 extend to by add 0 to leftmost, and revert the original vector, add 1 to the leftmost
    vector<int> grayCode(int n) {
        vector<int> r;
        if (n == 0) { r.push_back(0); return r; };
        r.push_back(0); r.push_back(1);
        
        unsigned shift = 1;
        for (unsigned ii = 1; ii < n; ii++) {
            unsigned cursize = r.size();
            r.resize(cursize*2);
            shift = shift << 1;
            for (unsigned ii = r.size()-1; ii >= cursize; --ii) {
                r[ii] = r[cursize*2-ii-1] | shift;
            }
        }
        return r;
    }
};