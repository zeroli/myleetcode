#include "utils.h"

int CoundSubarrEqualSum(const std::vector<int>& arr, int K)
{
    // calculate prefix sum and store them in hash table for quick access
    std::unordered_map<int, int> counts;  // prefix sum => counts
    int sum = 0;  // sum until now
    int cnt = 0;
    for (auto num : arr) {
        sum += num;
        if (sum == K) {
            cnt++;
        }
        if (counts.find(sum - K) != counts.end()) {
            cnt += counts[sum - K];  // remove some prefix, we can get same sum K
        }
        counts[sum]++;
    }
    return cnt;
}

int main()
{
    {
        std::vector<int> arr = { 10, 2, -2, -20, 10 };
        int sum = -10;
        std::cout << CoundSubarrEqualSum(arr, sum) << "\n";  // 3
    }
}
