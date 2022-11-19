class Solution {
public:
// top to bottome generate
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> r;
        if (!numRows) return r;
        r.resize(numRows, vector<int>());
        
        r[0] = vector<int>(1,1);
        if (numRows == 1) return r;
        r[1] = vector<int>(2,1);
        if (numRows == 2) return r;
        
        for (int ii = 2; ii < numRows; ++ii){
            r[ii] = vector<int>(ii+1,1);
            for (int idx = 1; idx < ii; ++idx) {
                r[ii][idx] = r[ii-1][idx-1] + r[ii-1][idx];
            }
        }
        return r;
    }
};