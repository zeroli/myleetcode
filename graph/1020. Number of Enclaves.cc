/*
You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally)
land cell or walking off the boundary of the grid.

Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

Input: grid = {{0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.

Input: grid = {{0,1,1,0},{0,0,1,0},{0,0,1,0},{0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.
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

int NumOfEnclaves(Grid_t& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    // flood fill those non-closed islands from edges
    for (int r = 0; r < m; r++) {
        FloodFill(grid, r, 0);
        FloodFill(grid, r, n - 1);
    }

    for (int c = 0; c < n; c++) {
        FloodFill(grid, 0, c);
        FloodFill(grid, m - 1, c);
    }

    int cnt = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == ISLAND) {
                cnt += 1;  // count the cells# of island
            }
        }
    }
    return cnt;
}

int main()
{
    {
        Grid_t grid = {
            {0,0,0,0},{1,0,1,0},{0,1,1,0},{0,0,0,0}
        };
        std::cout << NumOfEnclaves(grid) << "\n";  // 2
    }
}
