/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.)
 You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.

Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.

Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0
*/

#include "utils.h"

using Grid_t = std::vector<std::vector<int>>;
static constexpr int ISLAND = 1;
static constexpr int WATER = 0;

int FloodFill(Grid_t& grid, int r, int c)
{
    int m = grid.size();
    int n = grid[0].size();
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return 0;
    }

    if (grid[r][c] == WATER) {
        return 0;
    }
    grid[r][c] = WATER;

    int area = 1;
    area += FloodFill(grid, r - 1, c);  // up
    area += FloodFill(grid, r + 1, c);  // down
    area += FloodFill(grid, r, c - 1);  // left
    area += FloodFill(grid, r, c + 1);  // right
    return area;
}

int MaxAreaOfIsland(Grid_t& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    int maxArea = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == ISLAND) {
                maxArea = std::max(maxArea, FloodFill(grid, r, c));
            }
        }
    }
    return maxArea;
}

int main()
{
    {
        Grid_t grid = {
            {0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}
        };
        std::cout << MaxAreaOfIsland(grid) << "\n";  // 6
    }
}
