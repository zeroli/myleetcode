class Solution {
public:
// DP question, with the size of square ended at (i,j) depends on (i-1,j), (i, j-1), and (i-1, j-1)
// NOTE, actually we do not need the full matrix size, we only need two rows, one for pre, and one for cur
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty()) return 0;
        
        int row = matrix.size();
        int col = matrix[0].size();
        vector<vector<int>> squaresize(row, vector<int>(col, 0));

        int maxss = 0;
        for (int ii = 0; ii < col; ++ii){
            squaresize[0][ii] = matrix[0][ii] == '0' ? 0:1;
            maxss = max(maxss, squaresize[0][ii]);
        }
        for (int ii = 0; ii < row; ++ii){
            squaresize[ii][0] = matrix[ii][0] == '0' ? 0:1;
            maxss = max(maxss, squaresize[ii][0]);
        }
        
        for (int irow = 1; irow < row; ++irow)
        for (int icol = 1; icol < col; ++icol){
            if (matrix[irow][icol] != '0') {
                squaresize[irow][icol] = 1 + min( {squaresize[irow-1][icol-1]
                                                , squaresize[irow][icol-1]
                                                , squaresize[irow-1][icol]} );
                maxss = max(maxss, squaresize[irow][icol]);
            }
        }
        return maxss*maxss;
    }
};