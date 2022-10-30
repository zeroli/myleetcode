/*
       1
    1    1
  1   2   1
1   3   3   1
杨辉三角形
输入n，产生前面n行数据的数组
*/

#include "utils.h"

std::vector<std::vector<int>> GenPascalTriangle(int n)
{
    std::vector<std::vector<int>> result;
    result.push_back({1});
    for (int i = 1; i < n; i++) {
        result.push_back({1});
        auto& prevRow = result[i-1];
        for (int j = 0; j < prevRow.size(); j++) {
            auto data = prevRow[j] + ((j+1 == prevRow.size()) ? 0 : prevRow[j+1]);
            result.back().push_back(data);
        }
    }
    return result;
}

int main()
{
    std::cout << GenPascalTriangle(5) << "\n";
}
