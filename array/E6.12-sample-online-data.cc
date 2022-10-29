/*
从不断采用得到的数据中，获取随机的k个数，
所有数据都需要同等概率被选择出来，数据量不确定
*/

/*
当n个数中随机选择k个数之后，那么紧接着过来的第n+1个数
要么会被选择，概率是k/(n+1)，要么不会被选择进k个数字中
当被选中时，那么k个数中需要有一个被踢出来，这个第n+1个数进去。
如何选择这个被踢出来的数呢？
从当前n+1个数中选择一个index，如果index落在k以内，那么就踢出那个数
否则就没有数被踢出，换句话说这个第n+1个数就不被选中
*/

#include "utils.h"
#include <random>

std::vector<int> SelectKOnline(int n, int k)
{
    std::vector<int> selects;
    for (int i = 0; i < k; i++) {
        selects.push_back(i);
    }

    std::random_device r;
    std::default_random_engine seed(r());

    for (int i = k; i < n; i++) {
        int remove = std::uniform_int_distribution<int>(0, i)(seed);
        if (remove < k) {
            selects[remove] = i;
        }
    }
    return selects;
}

int main()
{
    {
        std::cout << SelectKOnline(1000, 10) << "\n";
    }
}
