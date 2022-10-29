/*
所有的排列组合
1, 2, 3 =>
[1, 2, 3]
[1, 3, 2]
[2, 1, 3]
[2, 3, 1]
[3, 1, 2]
[3, 2, 1]
原始数组里面不存在重复元素
*/

#include "utils.h"

using Result_t = std::vector<int>;
void dfs(const std::vector<int>& arr, std::vector<bool>& selected,
    Result_t& result, std::vector<Result_t>& results)
{
    // 退出判断
    // 一旦遍历到result大小等于元素个数的是，就是叶子节点
    if (result.size() == arr.size()) {
        results.push_back(result);
        return;
    }
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        if (selected[i]) {
            continue;
        }
        // 做选择
        selected[i] = true;
        result.push_back(arr[i]);
        dfs(arr, selected, result, results);
        // 撤销选择
        selected[i] = false;
        result.pop_back();
    }
}

std::vector<Result_t> Permutations(const std::vector<int>& arr)
{
    std::vector<Result_t> results;
    std::vector<bool> selected(arr.size(), false);
    Result_t result;
    dfs(arr, selected, result, results);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3 };
        std::cout << Permutations(arr) << "\n";
    }
}
