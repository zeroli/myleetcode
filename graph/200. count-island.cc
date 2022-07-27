#include "graph-util.h"

using Grid_t = std::vector<std::vector<std::string>>;

using Mark_t = std::set<std::pair<int, int>>;

bool dfs(Grid_t& grid, int r, int c, Mark_t& visited)
{
    if (r < 0 || r >= grid.size()) return false;
    if (c < 0 || c >= grid[0].size()) return false;

    if (visited.find({r, c}) != visited.end()) {
        return false;
    }
    visited.insert({r, c});
    if (grid[r][c] != "L") {
        return false;
    }

    dfs(grid, r - 1, c, visited);  // up
    dfs(grid, r + 1, c, visited);  // bottom
    dfs(grid, r, c - 1, visited);  // left
    dfs(grid, r, c + 1, visited);  // right

    return true;
};

int CountIsland(Grid_t& grid)
{
    Mark_t visited;
    int cnt = 0;

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            if (dfs(grid, r, c, visited)) {
                cnt++;
            }
        }
    }
    return cnt;
}

int main()
{
    Grid_t grid = {
        { "W", "L", "W", "W", "W" },
        { "W", "L", "W", "W", "W" },
        { "W", "W", "W", "L", "W" },
        { "W", "W", "L", "L", "W" },
        { "L", "W", "W", "L", "L" },
        { "L", "L", "W", "W", "W" },
    };

    int cnt = CountIsland(grid);
    std::cout << "island total: " << cnt << "\n";
}
