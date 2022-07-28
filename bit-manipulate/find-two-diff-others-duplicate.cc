#include "utils.h"

// keep right most bit 1, others to 0
int RightMostBit1(int num)
{
    if (num == 0) {
        return -1;
    }
    return num & (~num + 1);
}

std::pair<int, int> FindTwoDiff(const std::vector<int>& arr)
{
    // xor all numbers, so that result will be a ^ b
    // suppose a and b are those unique ones
    int res = 0;
    for (auto num : arr) {
        res ^= num;
    }
    // find the right-most bit 1
    int bit1 = RightMostBit1(res);
    // group nums where that bit is 1, and group numbers where that big is 0
    int bit1_num = 0, bit0_num = 0;
    for (auto num : arr) {
        if (bit1 & num) {  // bit 1 number found
            bit1_num ^= num;
        } else {
            bit0_num ^= num;
        }
    }
    return { bit1_num, bit0_num };
}

int main()
{
    std::vector<int> arr = { 1, 2, 3, 4, 3, 2, 1, 6 };
    std::cout << FindTwoDiff(arr) << "\n";
}
