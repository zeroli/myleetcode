/*
给定一个数组，长度为n，从中选出k个元素(k<n)，替代元素返回
k个元素要uniformly被选择出来
*/

#include "utils.h"

#include <random>

/*
每个元素要同等概率被选出来，那么可以想到的方案就是
循环k次，每次触发随机生成器，返回0到n-1之间的数作为index，
然后index对应的数就是被选出来的数，最后返回k个这样的数
*/

std::vector<int> SelectK(const std::vector<int>& arr, int k)
{
    std::random_device r;
    std::default_random_engine seed(r());
    int n = arr.size();
    std::uniform_int_distribution<int> gen(0, n-1);
    std::vector<int> res;
    while (k--) {
        res.push_back(arr[gen(seed)]);
    }
    return res;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, 3, 4, 5, 7, 10 };
        std::cout << SelectK(arr, 3) << "\n";
    }
}
