#include "utils.h"

using Memo_t = std::map<int, std::vector<int>>;
using Path_t = std::vector<int>;

bool bestSum_(int target, const std::vector<int>& nums, Memo_t& memo, Path_t& path)
{
    if (memo.find(target) != memo.end()) {
        auto& tmp = memo[target];
        path.insert(path.end(), tmp.begin(), tmp.end());
        return !tmp.empty();
    }
    // base case
    if (target == 0) {
        return true;
    }
    // pruning
    if (target < 0) {
        return false;
    }

    Path_t shortestPath;
    // any number in array could be selected any times
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > target) {
            continue;
        }
        Path_t tmp; tmp.push_back(nums[i]);
        if (bestSum_(target - nums[i], nums, memo, tmp)) {
            // best path memo for child node for target
            if (shortestPath.empty() || shortestPath.size() > tmp.size()) {
                shortestPath = tmp;
            }
        }
    }
    memo[target] = shortestPath;
    // extend the path along with best path for target
    path.insert(path.end(), shortestPath.begin(), shortestPath.end());
    return !shortestPath.empty();
}

Path_t bestSum(int target, const std::vector<int>& nums)
{
    Memo_t memo;
    std::vector<int> path;
    bestSum_(target, nums, memo, path);
    return path;
}

int main()
{
    {
        std::vector<int> nums = {
            5, 3, 4, 7
        };
        std::cout << bestSum(7, nums) << "\n";
    }
    {
        std::vector<int> nums = {
            2, 3, 5,
        };
        std::cout << bestSum(8, nums) << "\n";
    }
    {
        std::vector<int> nums = {
            7, 14
        };
        std::cout << bestSum(300, nums) << "\n";
    }
}
