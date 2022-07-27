#include "utils.h"

using Board_t = std::vector<std::vector<char>>;
using Visited_t = std::vector<std::vector<bool>>;

bool searchWord_(const std::string& word, const Board_t& board, Visited_t& visited, int index, int row, int col)
{
    // base case
    if (index == word.size()) {
        return true;
    }
    // out of board check
    if (row < 0 || row >= board.size()) {
        return false;
    }
    if (col < 0 || col >= board[0].size()) {
        return false;
    }

    if (visited[row][col]) {
        return false;
    }

    if (word[index] != board[row][col]) {
        return false;
    }
    visited[row][col] = true;
    // dfs recursive call for 4 direction(up/down/left/right), for next character
    bool ret =
        searchWord_(word, board, visited, index + 1, row - 1, col) ||
        searchWord_(word, board, visited, index + 1, row + 1, col) ||
        searchWord_(word, board, visited, index + 1, row, col - 1) ||
        searchWord_(word, board, visited, index + 1, row, col + 1);

    visited[row][col] = false;
    return ret;
}

bool searchWord(const std::string& word, const Board_t& board)
{
    Visited_t visited(board.size(), std::vector<bool>(board[0].size(), false));
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            // always start searching word from its beginning
            if (searchWord_(word, board, visited, 0, i, j)) {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    Board_t board = {
        { 'A', 'B', 'C', 'E' },
        { 'S', 'F', 'C', 'S' },
        { 'A', 'D', 'E', 'E' }
    };
    {
        std::string word = "ABCCED";
        std::cout << "search word " << word << ": " << std::boolalpha
            << searchWord(word, board) << "\n";
    }
    {
        std::string word = "SEE";
        std::cout << "search word " << word << ": " << std::boolalpha
            << searchWord(word, board) << "\n";
    }
    {
        std::string word = "ABCB";
        std::cout << "search word " << word << ": " << std::boolalpha
            << searchWord(word, board) << "\n";
    }
}
