/*
Given a matrix of m×n elements (m rows, n columns),
 return all elements of the matrix in spiral order.
For example, Given the following matrix:
[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5
*/

#include "utils.h"

std::vector<int> EnumerateSpiralMatrix(const Array2D_t<int>& arr2d)
{
    int m = arr2d.size(), n = arr2d[0].size();
    int begRow = 0;
    int endRow = m - 1;
    int begCol = 0;
    int endCol = n - 1;
    std::vector<int> res;
    while (1) {
        // 从左到右 for begRow
        for (int i = begCol; i <= endCol; i++) {
            res.push_back(arr2d[begRow][i]);
        }
        // 这一行遍历完，到下一行。
        // 如果下一行越过endRow，说明之前begRow=endRow，没有更多行了
        if (++begRow > endRow) break;
        // 从上到下 for endCol
        for (int j = begRow; j <= endRow; j++) {
            res.push_back(arr2d[j][endCol]);
        }
        if (--endCol < begCol) break;
        // 从右到左 for endRow
        for (int i = endCol; i >= begCol; i--) {
            res.push_back(arr2d[endRow][i]);
        }
        if (--endRow < begRow) break;
        // 从下到上 for begCol
        for (int j = endRow; j >= begRow; j--) {
            res.push_back(arr2d[j][begCol]);
        }
        if (++begCol > endCol) break;
    }
    return res;
}

int main()
{
    {
        Array2D_t<int> m = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 },
        };
        std::cout << EnumerateSpiralMatrix(m) << "\n";
    }
    {
        Array2D_t<int> m = {
            { 1, 2, 3 },
            { 4, 5, 6 },
        };
        std::cout << EnumerateSpiralMatrix(m) << "\n";
    }
    {
        Array2D_t<int> m = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 },
        };
        std::cout << EnumerateSpiralMatrix(m) << "\n";
    }
    {
        Array2D_t<int> m = {
            { 1, 2, 3, 4 },
            { 5, 6, 7, 8 },
            { 9, 10, 11, 12 },
            { 13, 14, 15, 16 },
        };
        std::cout << EnumerateSpiralMatrix(m) << "\n";
    }
}
