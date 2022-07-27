#include "utils.h"

/*
Given two integers n and k,
 Write a program to return all possible combinations of k numbers out of 1 2 3 ... n.

Problem Note

    Elements in a combination must be in a non-descending order.
    The combinations themselves must be sorted in ascending order, i.e., the combination with the smallest first element should be printed first.
    The combination [1,2] is valid but [2,1] is invalid as 2>1.
*/

using Path_t = std::vector<int>;

void BackTracking(int n, int k, int startIndex,
    Path_t& path, std::vector<Path_t>& results)
{
    if (path.size() == k) {
        results.push_back(path);
        return;
    }

    for (int i = startIndex; i <= n; i++) {
        path.push_back(i);
        BackTracking(n, k, i+1, path, results);
        path.pop_back();
    }
}

std::vector<Path_t> Combinations(int n, int k)
{
    Path_t path;
    std::vector<Path_t> results;
    BackTracking(n, k, 1, path, results);
    return results;
}

int main()
{
    {
        int n = 3;
        int k = 2;
        std::cout << Combinations(n, k) << "\n";
    }
    {
        int n = 5;
        int k = 3;
        std::cout << Combinations(n, k) << "\n";
    }
}
