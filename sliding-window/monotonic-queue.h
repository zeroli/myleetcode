#ifndef MONOTONIC_QUEUE_H_
#define MONOTONIC_QUEUE_H_

#include <vector>

// monotonic queue
// by default, it is a monotonic max queue
// use std::greater<T> for monotonic min queue
template <typename T, typename Cmp = std::less<T>>
struct MonotonicQueue {
    std::vector<int> data;

    void push(int d)
    {
        Cmp cmp;
        while (!data.empty() && cmp(data.back(), d))
        {  // bigger data comes in, remove smaller ones
            data.pop_back();
        }
        data.push_back(d);
    }

    // pop what??
    void pop(int d)
    {
        if (!data.empty() && data.front() == d) {
            data.erase(data.begin());
        }
    }

    // return max one, otherwise, throw exception
    int front() const
    {
        if (!data.empty()) {
            return data.front();
        }
        throw std::out_of_range("out-of-range");
    }
};

#endif  // MONOTONIC_QUEUE_H_
