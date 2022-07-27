#include "utils.h"

/*
Given a row-wise sorted matrix arr of size m × n, write a program to find the median of the matrix given.

Problem Note

    It is assumed that m × n is always odd.
    No extra memory is allowed.
*/

struct Elem {
    int row, col;
    int val;
};

struct ElemCmp {
    bool operator ()(const Elem& e1, const Elem& e2) const
    {
        return e1.val > e2.val;  // build min heap
    }
};

int FindMedian(const Array2D_t<int>& arr2d)
{
    std::priority_queue<Elem, std::vector<Elem>, ElemCmp> pq;
    int m = arr2d.size();
    int n = arr2d[0].size();
    for (int i = 0; i < m; i++) {
        pq.push({i, 0, arr2d[i][0]});
    }

    int k = m * n / 2 + 1;
    while (!pq.empty()) {
        auto elem = pq.top();
        pq.pop();

        if (--k == 0) {
            return elem.val;
        }

        // next element to be pushed is right close element
        int nr = elem.row, nc = elem.col+1;
        if (nc >= n) {
            continue;
        }
        Elem next({ nr, nc, arr2d[nr][nc]});
        pq.push(next);
    }
    return -1;
}

int main()
{
    {
        Array2D_t<int> arr2d = {
            {1, 4, 5},
            {2, 6, 9},
            {3, 6, 10}
        };
        std::cout << FindMedian(arr2d) << "\n";
    }
}
