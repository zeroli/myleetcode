/*
You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land).
 An island is a group of 1's connected 4-directionally (horizontal or vertical).
 Any cells outside of the grid are considered water cells.

An island in grid2 is considered a sub-island if there is an island in grid1
 that contains all the cells that make up this island in grid2.

Return the number of islands in grid2 that are considered sub-islands.


Example 1:

Input: grid1 = {{1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}},
 grid2 = {{1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}}
Output: 3
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island.
 There are three sub-islands.

 Input: grid1 = {{1,0,1,0,1},{1,1,1,1,1},{0,0,0,0,0},{1,1,1,1,1},{1,0,1,0,1}},
  grid2 = {{0,0,0,0,0},{1,1,1,1,1},{0,1,0,1,0},{0,1,0,1,0},{1,0,0,0,1}}
Output: 2
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island.
 There are two sub-islands.
*/

#include "utils.h"

using Grid_t = std::vector<std::vector<int>>;
static constexpr int ISLAND = 1;
static constexpr int WATER = 0;

void FloodFill(Grid_t& grid, int r, int c)
{
    int m = grid.size();
    int n = grid[0].size();
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return;
    }

    if (grid[r][c] == WATER) {
        return;
    }
    grid[r][c] = WATER;

    FloodFill(grid, r - 1, c);  // up
    FloodFill(grid, r + 1, c);  // down
    FloodFill(grid, r, c - 1);  // left
    FloodFill(grid, r, c + 1);  // right
}

int NumOfEnclaves(Grid_t& grid1, Grid_t& grid2)
{
    int m = grid1.size();
    int n = grid1[0].size();
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            // remove those islands in grid2 not island in grid1, IMPORTANT
            if (grid1[r][c] == WATER && grid2[r][c] == ISLAND) {
                FloodFill(grid2, r, c);
            }
        }
    }
    int cnt = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (grid2[r][c] == ISLAND) {
                cnt += 1;  // count remaining sub-island#
                FloodFill(grid2, r, c);
            }
        }
    }
    return cnt;
}

int main()
{
    {
        Grid_t grid1 = {
            {1,1,1,0,0},{0,1,1,1,1},{0,0,0,0,0},{1,0,0,0,0},{1,1,0,1,1}
        };
        Grid_t grid2 = {
            {1,1,1,0,0},{0,0,1,1,1},{0,1,0,0,0},{1,0,1,1,0},{0,1,0,1,0}
        };
        std::cout << NumOfEnclaves(grid1, grid2) << "\n";  // 3
    }
}
