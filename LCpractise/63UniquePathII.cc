class Solution {
public:
// the blocked site will have paths =0 to impact the the paths to (bottom, right)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        unsigned m = obstacleGrid.size();
        unsigned n = obstacleGrid[0].size();
        vector<vector<int> > intermediate(m, vector<int>(n, 0));
        for (unsigned ii = 0; ii < m; ++ii) {
            if (!obstacleGrid[ii][0]) {
                intermediate[ii][0] = 1;
            } else {
                break;
            }
        }
        for (unsigned jj = 0; jj < n; ++jj) {
            if (!obstacleGrid[0][jj]) {
                intermediate[0][jj] = 1;
            } else {
                break;
            }
        }
        
        for (unsigned ii = 1; ii < m; ++ii)
        for (unsigned jj = 1; jj < n; ++jj) {
            if (!obstacleGrid[ii][jj]) 
                intermediate[ii][jj] = intermediate[ii-1][jj] + intermediate[ii][jj-1];
        }
        
        return intermediate[m-1][n-1];
    }
};