class Solution {
public:
// the minimal path to (i,j) must be one of minimal path to (i-1, j) and (i, j-1)
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        if (grid.size() == 1) return accumulate(grid[0].begin(), grid[0].end(), 0);
        
        vector<vector<int>> r (grid.size(), vector<int>(grid[0].size(), 0));
        r[0][0] = grid[0][0];
        for (unsigned ii = 1; ii < grid.size(); ++ii) {
            r[ii][0] = r[ii-1][0] + grid[ii][0];
        }
        for (unsigned ii = 1; ii < grid[0].size(); ++ii) {
            r[0][ii] = r[0][ii-1] + grid[0][ii];
        }
        for (unsigned ii = 1; ii < grid.size(); ++ii) 
        for (unsigned jj = 1; jj < grid[ii].size(); ++jj) {
            r[ii][jj] = min(r[ii-1][jj], r[ii][jj-1]) + grid[ii][jj];
        }
        return r.back().back();
    }
};