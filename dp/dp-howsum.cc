#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include "utils.h"

using Memo_t = std::map<int, std::vector<int>>;
using Path_t = std::vector<int>;

bool howSum_(int target, const std::vector<int>& nums, Memo_t& memo, Path_t& path)
{
    if (memo.find(target) != memo.end()) {
        path = memo[target];
        return !path.empty();
    }
    // base case
    if (target == 0) {
        return true;
    }
    // pruning
    if (target < 0) {
        return false;
    }

    // any number in array could be selected any times
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > target) {
            continue;
        }
        if (howSum_(target - nums[i], nums, memo, path)) {
            path.insert(path.begin(), nums[i]);
            memo[target] = path;
            return true;
        }
    }
    memo[target] = {};
    return false;
}

Path_t howSum(int target, const std::vector<int>& nums)
{
    Memo_t memo;
    std::vector<int> path;
    howSum_(target, nums, memo, path);
    return path;
}

int main()
{
    {
        std::vector<int> nums = {
            5, 3, 4, 7
        };
        std::cout << howSum(7, nums) << "\n";
    }
    {
        std::vector<int> nums = {
            7, 14
        };
        std::cout << howSum(300, nums) << "\n";
    }
}
