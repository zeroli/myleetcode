#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using Memo_t = std::map<int, bool>;

bool canSum_(int target, const std::vector<int>& nums, Memo_t& memo)
{
    if (memo.find(target) != memo.end()) {
        return memo[target];
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
        if (canSum_(target - nums[i], nums, memo)) {
            memo[target] = true;
            return true;
        }
    }
    memo[target] = false;
    return false;
}

bool canSum(int target, const std::vector<int>& nums)
{
    Memo_t memo;
    return canSum_(target, nums, memo);
}

int main()
{
    {
        std::vector<int> nums = {
            5, 3, 4, 7
        };
        std::cout << std::boolalpha << canSum(7, nums) << "\n";
    }
    {
        std::vector<int> nums = {
            7, 14
        };
        std::cout << std::boolalpha << canSum(300, nums) << "\n";
    }
}
