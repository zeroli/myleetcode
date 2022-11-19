class Solution {
public:
// only need to keep one row, and do the calculuation of new val from back to begin

// below is the version use two rows
    vector<int> getRow(int rowIndex) {
        vector<int> R0; R0.assign(1, 1);
        if (rowIndex == 0) return R0;
        
        vector<int>& preR = R0;
        vector<int> R;
        for(unsigned int irow = 1; irow <= rowIndex; ++irow){
            R.clear();
            R.assign(irow+1, 0);
            R[0] = R[irow] = 1;
            for (unsigned int jcol = 1; jcol < irow; ++jcol){
                R[jcol] = preR[jcol-1] + preR[jcol];
            }
            swap(preR, R);
        }
        return preR;
    }
};