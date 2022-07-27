#include "utils.h"

void SetMatrixZero1(Array2D_t<int>& m)
{
    std::set<int> rows_clear, cols_clear;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (m[i][j] == 0) {
                rows_clear.insert(i);
                cols_clear.insert(j);
            }
        }
    }
    for (auto&& row : rows_clear) {
        for (int i = 0; i < m[0].size(); i++) {
            m[row][i] = 0;
        }
    }
    for (auto&& col : cols_clear) {
        for (int i = 0; i < m.size(); i++) {
            m[i][col] = 0;
        }
    }
}

void SetMatrixZero(Array2D_t<int>& m)
{
    bool firstRowHasZero = false;
    bool firstColHasZero = false;
    int M = m.size(), N = m[0].size();
    for (int i = 0; i < N; i++) {
        if (m[0][i] == 0)
            firstRowHasZero = true;
    }
    for (int i = 0; i < M; i++) {
        if (m[i][0] == 0)
            firstColHasZero = true;
    }

    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {
            if (m[i][j] == 0) {  // store this flag to its first row/col headers
                m[0][j] = 0;
                m[i][0] = 0;
            }
        }
    }

    // modify every single element based on those 2 flags in its row/col header
    for (int i = 1; i < M; i++) {
        for (int j = 1; j < N; j++) {
            if (m[0][j] == 0 || m[i][0] == 0) {
                m[i][j] = 0;
            }
        }
    }
    if (firstRowHasZero) {
        for (int i = 0; i < N; i++) {
            m[0][i] = 0;
        }
    }
    if (firstColHasZero) {
        for (int i = 0; i < M; i++) {
            m[i][0] = 0;
        }
    }
}

int main()
{
    {
        Array2D_t<int> arr2d = {
            { 0, 1 },
            { 1, 1 }
        };
        std::cout << arr2d << "\n";
        SetMatrixZero(arr2d);
        std::cout << arr2d << "\n";
    }
    {
        Array2D_t<int> arr2d = {
            { 1, 1, 1 },
            { 1, 0, 1 },
            { 1, 1, 1 }
        };
        std::cout << arr2d << "\n";
        SetMatrixZero(arr2d);
        std::cout << arr2d << "\n";
    }
}
