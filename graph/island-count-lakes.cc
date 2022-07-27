#include "utils.h"

#include <iostream>
#include <cassert>
#include <queue>

using Grid_t = std::vector<std::string>;
#define B 'B'  // water
#define G 'G'  // island
#define X 'X'  // lake water
#define O 'O'  // water modified

using Pt_t = std::pair<int, int>;
using PtSet_t = std::set<Pt_t>;

bool checkPt(const Grid_t& grid, const Pt_t& pt)
{
    if (pt.first < 0 || pt.first >= grid.size()) return false;
    if (pt.second < 0 | pt.second >= grid[0].size()) return false;
    return true;
}

void MarkWater(Grid_t& grid, int row, int col)
{
    if (grid[row][col] != B) return;

    std::queue<Pt_t> queue;
    queue.push({row, col});

    grid[row][col] = O;

    while (!queue.empty()) {
        auto pt = queue.front();
        queue.pop();

        // 4 grids surrounding (up/bottom/left/right)
        const Pt_t candidates[4] = {
            { pt.first - 1, pt.second },
            { pt.first + 1, pt.second },
            { pt.first, pt.second - 1 },
            { pt.first, pt.second + 1 }
        };
        for (int i = 0; i < 4; i++) {
            if (!checkPt(grid, candidates[i])) continue;
            auto& ptc = grid[candidates[i].first][candidates[i].second];
            if (ptc == B) {
                ptc = O;
                queue.push(candidates[i]);
            }
        }
    }
}

void MarkOceanWater(Grid_t& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    for (int col = 0; col < n; col++) {
        MarkWater(grid, 0, col);  // upper bound
        MarkWater(grid, m - 1, col);  // lower bound
    }
    for (int row = 0; row < m; row++) {
        MarkWater(grid, row, 0);  // left bound
        MarkWater(grid, row, n - 1);  // right bound
    }
}

using Visited_t = std::map<Pt_t, bool>;

void TraverseIsland_(const Grid_t& grid, const Pt_t& pt, Visited_t& visited, PtSet_t& ptset)
{
    if (visited.find(pt) != visited.end()) {
        return;
    }
    visited[pt] = true;
    // 8 directions to traverse (including diagonal)
    const Pt_t pts[8] = {
        { pt.first, pt.second + 1 },  // 0, +1
        { pt.first - 1, pt.second + 1 },  // -1, +1
        { pt.first - 1, pt.second },  // -1, 0
        { pt.first - 1, pt.second - 1 },  // -1, -1
        { pt.first, pt.second - 1 },  // 0, -1
        { pt.first + 1, pt.second - 1 },  // +1, -1
        { pt.first + 1, pt.second }, // +1, 0
        { pt.first + 1, pt.second + 1 }  // +1, +1
    };
    for (int i = 0; i < 8; i++) {
        auto&& newpt = pts[i];
        if (!checkPt(grid, newpt)) continue;

        auto type = grid[newpt.first][newpt.second];
        if (type == O) continue;  // ocean water

        // lake water
        if (type == X) {
            ptset.insert(newpt);
        }
        // then it is island, then continue traversal
        TraverseIsland_(grid, newpt, visited, ptset);
    }
}

PtSet_t TraverseIsland(const Grid_t& grid, const Pt_t& pt)
{
    PtSet_t ptset;
    Visited_t visited;
    TraverseIsland_(grid, pt, visited, ptset);
    return ptset;
}

bool CountLakes_(const Grid_t& grid, const Pt_t& pt, Visited_t& visited)
{
    if (visited.find(pt) != visited.end()) {
        return false;
    }
    visited[pt] = true;

    if (grid[pt.first][pt.second] != X) return false;

    // 4 grids surrounding (up/bottom/left/right)
    const Pt_t dirs[4] = {
        { pt.first - 1, pt.second },
        { pt.first + 1, pt.second },
        { pt.first, pt.second - 1 },
        { pt.first, pt.second + 1 }
    };
    for (int i = 0; i < 4; i++) {
        auto&& dirpt = dirs[i];
        if (!checkPt(grid, dirpt)) continue;

        CountLakes_(grid, dirpt, visited);
    }
    return true;
}

int CountLakes_(const Grid_t& grid, const PtSet_t& pts)
{
    Visited_t visited;
    int cnt = 0;
    // count how many connected components (lakes)
    for (auto&& pt : pts) {
        if (CountLakes_(grid, pt, visited)) {
            cnt++;
        }
    }
    return cnt;
}

int CountLakes(Grid_t& grid, const Pt_t& pt)
{
    if (!checkPt(grid, pt)) return 0;

    if (grid[pt.first][pt.second] != G) return 0;

    MarkOceanWater(grid);

    std::cout << "grid board after marking ocean water:\n" << grid << "\n";
    auto ptset = TraverseIsland(grid, pt);
    std::cout << "lake water points:\n" << ptset << "\n";
    // traverse lake points to see how many connected components
    return CountLakes_(grid, ptset);
}

int main()
{
    Grid_t grid = {
        { "BBBBBBBBBB" },  // 0
        { "BGGGGGGGGB" },  // 1
        { "BGXXXGXXGB" },  // 2
        { "BGXXXGGGGB" },  // 3
        { "BGGGGGGGGB" },  // 4
        { "BBBBBBBBBB" },  // 5
        { "BBBBGBBBBB" },  // 6
        { "BBBGXGBBBB" },  // 7
        { "BBGBGBBBBB" },  // 8
        { "BBBBBBBBBB" }  // 9
    };
    std::cout << "total lakes#: " << CountLakes(grid, {1, 1}) << "\n";
    std::cout << "total lakes#: " << CountLakes(grid, {7, 3}) << "\n";
}
