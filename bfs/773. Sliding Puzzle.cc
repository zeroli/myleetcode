#include "utils.h"

/*
On an 2 x 3 board, there are five tiles labeled from 1 to 5,
 and an empty square represented by 0.
  A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given the puzzle board board, return the least number of moves required so that the state of the board is solved.
 If it is impossible for the state of the board to be solved, return -1.

 Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.

Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.

Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]

*/

/*
其实这样的题目，包括拼图和魔方都是暴力穷举，
采用bfs算法来从一种状态，经过很多种变换后，到底最终的状态
BFS算法是最快可以到达目标状态的算法。
状态代表的是图中的节点，可以采用序列化成字符串的方式来表示
如何编程从一种状态变到另一种状态，是问题的关键。
如果是求变换的次数，那么就是求解bfs的最短路径；
*/

static constexpr int UP = 1;
static constexpr int DOWN = 2;
static constexpr int LEFT = 3;
static constexpr int RIGHT = 4;

// return -1 for invalid move
int NextMoveIndex(const Array2D_t<int>& board, int cur, int dir)
{
    int m = board.size();
    int n = board[0].size();
    int r = cur / n, c = cur % n;
    switch (dir) {
        case UP: // up
            r -= 1;
            break;
        case DOWN:  // down
            r += 1;
            break;
        case LEFT:  // left
            c -= 1;
            break;
        case RIGHT:  // right
            c += 1;
            break;
        default:
            break;
    }
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return -1;
    }
    return r * n + c;
}

int BFS(const Array2D_t<int>& board,
    const std::vector<int>& start, const std::vector<int>& end)
{
    std::queue<std::vector<int>> queue;
    queue.push(start);
    std::set<std::vector<int>> visisted;

    int nstep = 0;
    while (!queue.empty()) {
        int sz = queue.size();
        for (int i = 0; i < sz; i++) {
            auto state = queue.front();
            queue.pop();

            if (state == end) {  // find the end state
                return nstep;
            }

            // find position of '0'
            int cur = -1;
            for (int j = 0; j < state.size(); j++) {
                if (state[j] == 0) {
                    cur = j;
                    break;
                }
            }
            // move to neighbor?
            for (int k = UP; k <= RIGHT; k++) {
                int next = NextMoveIndex(board, cur, k);
                if (next >= 0) {
                    std::swap(state[cur], state[next]);
                    if (!visisted.count(state)) {  // seen before, skip
                        queue.push(state);
                        visisted.insert(state);
                    }
                    std::swap(state[cur], state[next]);
                }
            }
        }
        // 注意，step累加应该放在所有的子节点判断完成之后
        // 因为它代表转换的步数
        nstep++;
    }
    return -1;
}

int MoveNum(Array2D_t<int>& board)
{
    int m = board.size();
    int n = board[0].size();
    std::vector<int> startBoard;  // start point
    startBoard.reserve(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            startBoard.push_back(board[i][j]);
        }
    }
    std::vector<int> endBoard = {
        1, 2, 3, 4, 5, 0
    };
    if (startBoard == endBoard) {
        return 0;
    }
    return BFS(board, startBoard, endBoard);
}

int main()
{
    {
        Array2D_t<int> board = {
            { 1,2,3 },
            { 4,0,5 }
        };
        std::cout << MoveNum(board) << "\n";
    }
}
