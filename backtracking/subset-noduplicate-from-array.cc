/*
输入的数组元素，没有重复
1, 2, 3 =>
[1]
[2]
[3]
[1,2]
[1,3]
[2,3]
[1,2,3]
结果集中不能有重复的子集
输出的每一个子集要是非降序排列的
*/
#include "utils.h"

// 这题与backtracking\Print all subset.cc，题目一样
using Result_t = std::vector<int>;
void ChooseHelper(const std::vector<int>& arr, int startIdx, Result_t result, std::vector<Result_t>& results)
{
    // 结束条件，cover在了下面的for loop中
    int n = arr.size();
    for (int i = startIdx; i < n; i++) {
        // 做选择
        result.push_back(arr[i]);
        // 每做一个选择，加入到结果集中，树节点都要放入结果集中
        results.push_back(result);
        ChooseHelper(arr, i + 1, result, results);
        // 撤销选择
        result.pop_back();
    }
}

std::vector<std::vector<int>> AllSubsets(const std::vector<int>& arr0)
{
    std::vector<int> arr(arr0);
    std::sort(arr.begin(), arr.end());

    std::vector<Result_t> results;
    Result_t result;
    results.push_back(result);  // 空的子集合也要考虑在内
    ChooseHelper(arr, 0, result, results);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3 };
        std::cout << AllSubsets(arr) << "\n";
    }
    {
        std::vector<int> arr = { 5, 2, 3, 1, 0 };
        std::cout << AllSubsets(arr) << "\n";
    }
}
