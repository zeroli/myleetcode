/*
 spread gossip
*/
#include "utils.h"
#include <queue>

using Cell_t = std::pair<int, int>;
bool InGrid(int r, int c, int m, int n)
{
    return r >= 0 && r < m && c >= 0 && c < n;
}

int SpreadGossip(Array2D_t<int>& arr)
{
    int m = arr.size();
    int n = arr[0].size();

    std::queue<Cell_t> queue;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) {
                queue.push({i, j});
            }
        }
    }

    const int dirs[][2] = {
        { -1, 0 },
        { +1, 0},
        { 0, -1 },
        { 0, +1}
    };

    int nsteps = -1;
    while (!queue.empty()) {
        int sz = queue.size();
        for (int i = 0; i < sz; i++) {
            auto cell = queue.front();
            queue.pop();

            for (int id = 0; id < 4; id++) {
                Cell_t ncell = { cell.first + dirs[id][0], cell.second + dirs[id][1] };
                if (!InGrid(ncell.first, ncell.second, m, n)) {
                    continue;
                }
                if (arr[ncell.first][ncell.second] != 0) {
                    continue;
                }
                arr[ncell.first][ncell.second] = 1;
                queue.push(ncell);
            }
        }
        nsteps++;
    }
    return nsteps;
}

int main()
{
    {
        Array2D_t<int> arr = {
            { 1, 0, 1 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        std::cout << SpreadGossip(arr) << "\n";  // 3
    }
    {
        Array2D_t<int> arr = {
            { 1, 1, 1 },
            { 1, 1, 1 },
            { 1, 1, 1 }
        };
        std::cout << SpreadGossip(arr) << "\n";  // 0
    }
    {
        Array2D_t<int> arr = {
            { 0, 0, 0 },
            { 0, 0, 0 },
            { 0, 0, 0 }
        };
        std::cout << SpreadGossip(arr) << "\n";  // -1
    }
}
