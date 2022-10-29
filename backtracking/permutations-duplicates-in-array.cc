/*
所有的排列组合
1, 1, 2 =>
[1, 1, 2]
[1, 2, 1]
[2, 1, 1]
原始数组里面存在重复元素
*/

#include "utils.h"

using Result_t = std::vector<int>;
void dfs(const std::vector<int>& arr, std::vector<bool>& used,
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
        // 如果在同一树路径上，这个元素已经被用了，则跳过
        if (used[i]) {
            continue;
        }
        // 如果没被用，但是跟前一个元素相同，
        // 且前一个元素没在当前路径上，也跳过
        // 因为不允许重复选择之前选过的数字
        // 这个前面相同元素应该在当前for循环的已经处理过了
        // 由它产生了一个树分支
        if (i > 0 && arr[i] == arr[i-1] && !used[i-1]) {
            continue;
        }
        // 做选择
        used[i] = true;
        result.push_back(arr[i]);
        dfs(arr, used, result, results);
        // 撤销选择
        //selected[i] = false;
        used[i] = false;
        result.pop_back();
    }
}

std::vector<Result_t> Permutations(const std::vector<int>& arr0)
{
    // 包含重复元素，我们需要去重，得要排序原数组
    std::vector<int> arr(arr0);
    std::vector<Result_t> results;
    std::vector<bool> used(arr.size(), false);
    Result_t result;
    dfs(arr, used, result, results);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 1, 1, 2 };
        std::cout << Permutations(arr) << "\n";
    }
    {
        std::vector<int> arr = { 1, 1, 1, 2, 2, 3 };
        std::cout << Permutations(arr) << "\n";
    }
}
