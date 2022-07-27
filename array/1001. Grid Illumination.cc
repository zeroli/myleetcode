#include "utils.h"

/*
On a N x N grid of cells, each cell (x, y) with 0 <= x < N and 0 <= y < N has a lamp.

Initially, some number of lamps are on.  lamps[i] tells us the location of the i-th lamp that is on.
 Each lamp that is on illuminates every square on its x-axis, y-axis, and both diagonals (similar to a Queen in chess).

For the i-th query queries[i] = (x, y), the answer to the query is 1 if the cell (x, y) is illuminated, else 0.

After each query (x, y) [in the order given by queries], we turn off any lamps that are at cell (x, y) or
 are adjacent 8-directionally (ie., share a corner or edge with cell (x, y).)

Return an array of answers.  Each value answer[i] should be equal to the answer of the i-th query queries[i].
*/

using namespace std;

class Solution {
public:
  vector<int> gridIllumination(int N, vector<vector<int>>& lamps, vector<vector<int>>& queries) {
    unordered_set<long> s;
    unordered_map<int, int> lx, ly, lp, lq;
    for (const auto& lamp : lamps) {
      const int x = lamp[0];
      const int y = lamp[1];
      s.insert((static_cast<long>(x) << 32) | y);
      ++lx[x];
      ++ly[y];
      // diagonal direction:
      // abs(x1-x2) = abs(y1-y2)
      // => x1 - x2 = y1 - y2 => x1 - y1 = x2 - y2
      // => x2 - x1 = y1 - y2 => x1 + y1 = x2 + y2
      ++lp[x + y];
      ++lq[x - y];
    }
    vector<int> ans;
    for (const auto& query : queries) {
      const int x = query[0];
      const int y = query[1];
      if (lx.count(x) || ly.count(y) || lp.count(x + y) || lq.count(x - y)) {
        ans.push_back(1);
        for (int tx = x - 1; tx <= x + 1; ++tx)
          for (int ty = y - 1; ty <= y + 1; ++ty) {
            if (tx < 0 || tx >= N || ty < 0 || ty >= N) continue;
            const long key = (static_cast<long>(tx) << 32) | ty;
            if (!s.count(key)) continue;
            s.erase(key);
            if (--lx[tx] == 0) lx.erase(tx);
            if (--ly[ty] == 0) ly.erase(ty);
            if (--lp[tx + ty] == 0) lp.erase(tx + ty);
            if (--lq[tx - ty] == 0) lq.erase(tx - ty);
          }
      } else {
        ans.push_back(0);
      }
    }
    return ans;
  }
};

int main()
{
    {
        int N = 5;
        std::vector<std::vector<int>> lamps = { { 0, 0}, {4, 4} };
        std::vector<std::vector<int>> queries = { { 1, 1 }, { 1, 0 }};
        std::cout << Solution().gridIllumination(N, lamps, queries) << "\n";
    }
}
