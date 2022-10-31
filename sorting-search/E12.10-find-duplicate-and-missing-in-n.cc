/*
给定n个正数的数组，数值从0到n-1，包含，有一个元素出现了2次，
那么另外一个元素肯定缺失了。
找出这个重复一次的元素和缺失的元素
*/

#include "utils.h"

/*
我们知道如果一个0到n-1组成的数组，如果丢失一个元素，
要找出这个元素，肯定用数学的方法，加和，然后减去数组的加和
或者将0到n-1的数与数组的所有元素进行异或操作，
那么结果就是丢失的元素，因为那些相同的元素会互相抵消掉，
留下那个丢失的元素。
我们又知道如果一个0到n-1组成的数组n+1元素，如果多出一个元素，
那么这个元素就是重复的元素，要找到这个元素，也可以用数学的方法，
加和，然后数组的加和减去那个加和，就是重复的元素。
或者将0到n-1的数与数组的所有元素进行异或操作，
那么结果就是重复的元素，因为那些相同的元素会互相抵消掉，
留下那个重复的元素。

那么如果数组元素有n个，数值是从0到n-1，那么有一个元素重复，
有一个元素丢失，如何求出重复和丢失的元素。
思路仍然是将0到n-1的n个数，与n个数组元素，进行异或，
异或结果就是重复元素和丢失元素的抑或结果。
这时我们也只知道它们异或的结果，而不知道它们各自的数值。
a ^ b
要求出a，只要我们知道了b: a ^ b ^ b => a
要求出b，只要我们知道了a: a ^ b ^ a => b

这个题目跟原来见过的一个题目思路类似：
给定一个数组，数组里面元素都重复2次，只有两个元素没有重复，
单独出现一次，求出这两个元素。

我们可以进行分组，将原来的2n个元素的数组，
这里就是0到n-1数组序列和n个元素组成的原数组，共2个元素。
这样理解这个问题，就跟之前的那个题目一模一样了。
但解决的关键思路就是根据什么进行分组呢？
a ^ b结果肯定不为0，有一个最低位为1，那么原2n元素的数组中
肯定有些元素的对应位位1，有些元素的对应位为0，
那么我们就可以进行分组，那些对应位为1的元素分成的组，
肯定有些相同元素，相互抵消了，既然最后结果为1，
那么它们异或的结果对应位肯定位1，然后跟a^b的结果再次异或，
结果要么是重复元素，要么是丢失元素。
然后我们再次遍历原n元素的数组，比较这个结果是不是其中一个元素，
如果是，则肯定是重复元素(因为丢失元素不会存在数组中)。
如果不是，则肯定是丢失元素，有了丢失元素，就可以知道重复元素了。
*/

// 返回(重复元素，丢失元素)
std::pair<int, int> FindDuplicateAndMissing(const std::vector<int>& arr)
{
    int n = arr.size();
    int miss_xor_dup = 0;
    for (int i = 0; i < n; i++) {
        miss_xor_dup ^= i ^ arr[i];
    }
    int lsbbit1 = miss_xor_dup & ~(miss_xor_dup - 1);
    int miss_or_dup = miss_xor_dup;
    for (int i = 0; i < n; i++) {
        if (i & lsbbit1) {
            miss_or_dup ^= i;
        }
        if (arr[i] & lsbbit1) {
            miss_or_dup ^= arr[i];
        }
    }
    for (int i = 0; i < n; i++) {
        if (miss_or_dup == arr[i]) {  // 是一个重复元素？
            return { arr[i], arr[i] ^ miss_xor_dup };
        }
    }
    // 是丢失元素，求出重复元素
    return { miss_xor_dup ^ miss_or_dup, miss_or_dup };
}

// 如果n不太大，可以利用bitmap来解决，每一位对应的数字，因为数字是连续的。
int main()
{
    {
        std::vector<int> arr = { 0, 1, 3, 3, 4 };
        std::cout << FindDuplicateAndMissing(arr) << "\n";  // (3, 2)
    }
}