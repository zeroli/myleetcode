/*

Find the number of distinct islands in a 2D matrix

Given a boolean 2D matrix.
 The task is to find the number of distinct islands where a group of connected 1s
  (horizontally or vertically) forms an island.
   Two islands are considered to be distinct if and only if
    one island is equal to another (not rotated or reflected).

Input: grid[][] =
{{1, 1, 0, 0, 0},
1, 1, 0, 0, 0},
0, 0, 0, 1, 1},
0, 0, 0, 1, 1}}
Output: 1
Island 1, 1 at the top left corner is same as island 1, 1 at the bottom right corner

Input: grid[][] =
{{1, 1, 0, 1, 1},
1, 0, 0, 0, 0},
0, 0, 0, 0, 1},
1, 1, 0, 1, 1}}
Output: 3
*/

#include "utils.h"

using Grid_t = std::vector<std::vector<int>>;
static constexpr int ISLAND = 1;
static constexpr int WATER = 0;
static constexpr char UP = '1';
static constexpr char DOWN = '2';
static constexpr char LEFT = '3';
static constexpr char RIGHT = '4';
using Dir_t = char;

void FloodFill(Grid_t& grid, int r, int c, Dir_t dir, std::string& path)
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

    // preorder code, enter direction
    path.push_back(dir);
    path.push_back(',');

    FloodFill(grid, r - 1, c, UP, path);  // up
    FloodFill(grid, r + 1, c, DOWN, path);  // down
    FloodFill(grid, r, c - 1, LEFT, path);  // left
    FloodFill(grid, r, c + 1, RIGHT, path);  // right

    // post order code, exit direction
    path.push_back('-');
    path.push_back(dir);
    path.push_back(',');
}

int NumOfDistinctIsland(Grid_t& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    std::set<std::string> pathSet;
    int cnt = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == ISLAND) {
                // different DFS traversing path, then we will have different island shapes
                std::string path;
                FloodFill(grid, r, c, '#', path);  // any dir as start
                pathSet.insert(path);
                std::cout << r << "," << c << ": " << path << "\n";
            }
        }
    }

    return pathSet.size();
}

int main()
{
    {
        Grid_t grid = {
            {1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}
        };
        std::cout << NumOfDistinctIsland(grid) << "\n";  // 1
    }
    {
        Grid_t grid = {
            {1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1}
        };
        std::cout << NumOfDistinctIsland(grid) << "\n";  // 3
    }

}
