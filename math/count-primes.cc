/*
给定一个正整数n，统计2-n之间有多少个prime number？
*/

/*
首先我们知道判断一个数是否是prime number，
我们不需要从2一直遍历到n(不包括n)，只需要遍历到sqrt(n)就可以了
12 = 2x6
12 = 3x4
12 = sqrt(12)xsqrt(12)
12 = 4x3
12 = 6x2
for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
        // n is not prime
    }
}

但是我们这里不利用这个算法来遍历计算2-n之间的数字是否prime，
因为计算复杂度很高
如果我们知道一个数是prime，那么2*prime， 3*prime，4*prime，5*prime，...,都不可能是prime
因为它们有那些2，3，4, 5...的整除因子
那么我们可以从2开始依次判断，判断完一个之后，便把它后面所有的非prime数标记下，
然后到那些数的时候，就不需要判断了
用空间换时间，标记所有数是否为prime，初始化为true
*/

#include "utils.h"

// 包括n
int CountPrimes(int n)
{
    std::vector<bool> isPrime(n, true);
    isPrime[0] = false;  // 1 is not prime
    for (int i = 2; i <= n; i++) {
        if (isPrime[i-1]) {
            for (int j = i * 2; j <= n; j += i) {
                isPrime[j-1] = false;
            }
        }
    }
    return std::count_if(isPrime.begin(), isPrime.end(), [](int x) { return x == true; });
}

/*
上面的`for (int j = i * 2; j <= n; j += i) {`仍然存在计算冗余
对于每一个prime，都从i*2开始标记后面的非prime数，
其实很多数已经被前面判断的prime数同样的比较过程标记过了。
2i, 3i, 4i, 5i, 6i, 7i, 8i, 9i, 10i, 11i, ...., (i-1)*i, i*i
当前的prime number是i, 之前任意一个小的prime number是k (k < i)
那么对于k * i，之前肯定已经标记false了，为啥？
因为k也是从2k, 3k, 4k, 5k, ....ik, (i+1)k, ....进行标记的。
唯独i*i没办法标记，因为对于(i-1)*i，如果i-1也是一个prime，
那么它会标记(i-1)*i，(i-1)*(i+1), ...
故而对于i*i之前的所有k*i (k < i)，如果k是prime，k*i会被标记，
如果k不是prime，k*i肯定也已经被那些基本的prime已经标记过了。
所有这条语句可以改写为:
for (int j = i * i; j <= n; j += i)
*/

int main()
{
    std::cout << CountPrimes(11) << "\n";  // 5 (2, 3, 5, 7, 11)
}
