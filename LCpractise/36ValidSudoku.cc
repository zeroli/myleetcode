class Solution {
public:
// brutal force check each block
    bool isValidSudoku(vector<vector<char>>& board) {
        assert(board.size() == 9);
        
        // scan for each row
        map<char, int> count;
        for (unsigned ii = 0; ii < 9; ++ii) {
            vector<char>& row = board[ii];
            count.clear();
            for (unsigned jj = 0; jj < 9; ++jj) {
                if (row[jj] != '.') {
                    if (++count[row[jj]] > 1) return false;
                }
            }
        }
        
        // scan for each column
        for (unsigned jj = 0; jj < 9; ++jj) {
            count.clear();
            for (unsigned ii = 0; ii < 9; ++ii) {
                if (board[ii][jj] != '.') {
                    if (++count[board[ii][jj]] > 1) return false;
                }
            }
        }
        
        // scan for each subblock
        for (unsigned ii = 0; ii < 9; ii += 3)
        for (unsigned jj = 0; jj < 9; jj += 3) {
            count.clear();
            for (unsigned iiin = 0; iiin < 3; ++iiin)
            for (unsigned jjin = 0; jjin < 3; ++jjin) {
                unsigned x = ii + iiin;
                unsigned y = jj + jjin;
                if (board[x][y] != '.') {
                    if (++count[board[x][y]] > 1) return false;
                }   
            }
        }
        return true;
    }
};