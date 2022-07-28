#include "utils.h"

int FindUniqueNum(const std::vector<int>& arr)
{
    int res = 0;
    for (int ib = 0; ib < 32; ib++) {
        // check all number at bit `ib`
        int cnt = 0;
        for (auto num : arr) {
            if ((num >> ib) & 1) {
                cnt++;
            }
        }
        // that unique number has 1 for that bit
        if (cnt % 3) {
            res |= (1 << ib);
        }
    }
    return res;
}

int main()
{
    std::vector<int> arr = { 1, 2, 3, 3, 2, 1, 2, 3, 1, 5 };
    std::cout << FindUniqueNum(arr) << "\n";
}
