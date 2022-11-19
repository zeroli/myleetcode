class Solution {
public:
// start from the diagonal direction top right, and move down/left 
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) return false;
        int Nrow = matrix.size();
        int Ncol = matrix[0].size();
        
        int irow = 0;
        int jcol = Ncol-1;
        while(irow < Nrow && jcol >= 0) {
            if (matrix[irow][jcol] == target) return true;
            if (matrix[irow][jcol] < target) {
                ++irow;
            } else {
                --jcol;
            }
        }
        return false;
    }
};