#include "graph-util.h"

using Grid_t = std::vector<std::vector<std::string>>;

using Mark_t = std::set<std::pair<int, int>>;

int dfs(Grid_t& grid, int r, int c, Mark_t& visited)
{
    if (r < 0 || r >= grid.size()) return 0;
    if (c < 0 || c >= grid[0].size()) return 0;

    if (visited.find({r, c}) != visited.end()) {
        return 0;
    }
    visited.insert({r, c});
    if (grid[r][c] != "L") {
        return 0;
    }

    int size = 1;
    size += dfs(grid, r - 1, c, visited);  // up
    size += dfs(grid, r + 1, c, visited);  // bottom
    size += dfs(grid, r, c - 1, visited);  // left
    size += dfs(grid, r, c + 1, visited);  // right

    return size;
};

int MinimumIsland(Grid_t& grid)
{
    Mark_t visited;
    int cnt = INT_MAX;

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[0].size(); c++) {
            int k =  dfs(grid, r, c, visited);
            if (k > 0) {
                cnt = std::min(cnt, k);
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

    int cnt = MinimumIsland(grid);
    std::cout << "minimum island size: " << cnt << "\n";
}
