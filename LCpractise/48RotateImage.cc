class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.size() < 2) return;
        flipDiagonal(matrix);
        flipMirrorY(matrix);
    }
    
private:
    void flipDiagonal(vector<vector<int>>& matrix) {
        if (matrix.size() < 2) return;
        for (unsigned ii = 0; ii < matrix.size(); ++ii)
        for (unsigned jj = ii+1; jj < matrix.size(); ++jj) {
            swap(matrix[ii][jj], matrix[jj][ii]);
        }
    }
    
    void flipMirrorY(vector<vector<int>>& matrix) {
        if (matrix.size() < 2) return;
        for (unsigned ii = 0; ii < matrix.size(); ++ii)
        for (unsigned jj = 0; jj < matrix.size()/2; ++jj) {
            swap(matrix[ii][jj], matrix[ii][matrix.size()-1-jj]);
        }
    }
};