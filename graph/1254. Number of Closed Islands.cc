/*
Given a 2D grid consists of 0s (land) and 1s (water).
  An island is a maximal 4-directionally connected group of 0s and a closed island
   is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

Input: grid = {{1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0}}
Output: 2
Explanation:
Islands in gray are closed because they are completely surrounded by water (group of 1s).

Input: grid = {{0,0,1,0,0},{0,1,0,1,0},{0,1,1,1,0}}
Output: 1

Input: grid = {{1,1,1,1,1,1,1},
               {1,0,0,0,0,0,1},
               {1,0,1,1,1,0,1},
               {1,0,1,0,1,0,1},
               {1,0,1,1,1,0,1},
               {1,0,0,0,0,0,1},
               {1,1,1,1,1,1,1}}
Output: 2
*/

#include "utils.h"

using Grid_t = std::vector<std::vector<int>>;
static constexpr int ISLAND = 0;
static constexpr int WATER = 1;

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

int NumOfClosedIsland(Grid_t& grid)
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
                cnt += 1;
                FloodFill(grid, r, c);
            }
        }
    }
    return cnt;
}

int main()
{
    {
        Grid_t grid = {
            { 1,1,1,1,1,1,1,0 },
            { 1,0,0,0,0,1,1,0 },
            { 1,0,1,0,1,1,1,0 },
            { 1,0,0,0,0,1,0,1},
            { 1,1,1,1,1,1,1,0 }
        };
        std::cout << NumOfClosedIsland(grid) << "\n";  // 2
    }
    {
        Grid_t grid = {
            { 0,0,1,0,0 },
            { 0,1,0,1,0 },
            { 0,1,1,1,0 }
        };
        std::cout << NumOfClosedIsland(grid) << "\n";  // 1
    }
    {
        Grid_t grid = {
            { 1,1,1,1,1,1,1 },
            {1,0,0,0,0,0,1},
            {1,0,1,1,1,0,1},
            {1,0,1,0,1,0,1},
            {1,0,1,1,1,0,1},
            {1,0,0,0,0,0,1},
            {1,1,1,1,1,1,1}
        };
        std::cout << NumOfClosedIsland(grid) << "\n";  // 2
    }
}
