#include "utils.h"

/*
给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，
返回此范围内所有数字的按位与（包含 m, n 两端点）。

示例 1:

输入: [5,7]
输出: 4
示例 2:

输入: [0,1]
输出: 0
*/

// 注意是按位与
/*
   二进制数长这样子：
   m:      xyzxxxxxx....1 xyzezzczzeafa
   m+k:    xyzxxxxxx....1 adfadfadsfa
   n:      xyzxxxxxx....1 adfadsfasdfa
   可以看到m到n，前面一部分二进制长的都相同，其最后一位为1
   剩下的bit位，都是0/1的组合，0 + 1 => 1 变成下一个数，1 + 1 => 0变成下一个数
   可以肯定的是，竖着看，后面的位置，所有区间数按位与肯定为0，
   因为肯定至少有一个数，对应位是0，这样最后按位与得到都是0。
   否则如果某位对应都是1，它左边的部分不全为1（有0），这种情况不存在，因为数都是连续的。
   前面相同bit的数，就是区间所有数按位与所保留下来的bit，后面的位都是0
   因为算法就是不断的右移m和n，直到只剩下左边相同的部分，那时候m/n就是相等的。
*/
int BitwiseAndRange(int m, int n)
{
    // base case
    if (m == n) {
        return m;
    }

    // << 1, 是把右边的0挪回来
    return (BitwiseAndRange(m >> 1, n >> 1) << 1);
}

int main()
{
    std::cout << BitwiseAndRange(5, 7) << "\n";  // 4
    std::cout << BitwiseAndRange(0, 1) << "\n";  // 0
}
