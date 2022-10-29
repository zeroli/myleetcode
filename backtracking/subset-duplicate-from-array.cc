/*
1,2,2 =>
[1]
[2]
[1,2]
[1,2,2]
[2,2]
[]

所有子集合，每个子集合输出得有序，原数组包含重复元素
*/

#include "utils.h"

using Result_t = std::vector<int>;
void Helper(const std::vector<int>& arr, int startIdx,
    Result_t result, std::vector<Result_t>& results, std::vector<bool>& used)
{
    int n = arr.size();
    for (int i = startIdx; i < n; i++) {
        if (i > startIdx && arr[i] == arr[i-1] && !used[i-1]) {
            // 同一层，相同的元素不能继续用了，同一树路径上相同元素可以选择
            continue;
        }
        // 做选择
        used[i] = true;  // 同一树路径，标记选择这个元素
        result.push_back(arr[i]);
        // 一做选择，就加入了最终结果集中
        results.push_back(result);
        Helper(arr, i + 1, result, results, used);
        // 撤销选择
        result.pop_back();
        used[i] = false;
    }
}

std::vector<Result_t> AllSubsets(const std::vector<int>& arr0)
{
    std::vector<int> arr(arr0);
    std::sort(arr.begin(), arr.end());

    std::vector<bool> used(arr.size(), false);
    std::vector<Result_t> results;
    Result_t result;
    results.push_back(result);
    Helper(arr, 0, result, results, used);
    return results;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 2 };
        std::cout << AllSubsets(arr) << "\n";
    }
}
