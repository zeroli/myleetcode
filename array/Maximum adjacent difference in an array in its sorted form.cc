#include "utils.h"

/*
Given an array, find the maximum difference
 between its two consecutive elements in its sorted form.
Examples:

Input: arr[] = {1, 10, 5}
Output: 5
Sorted array would be {1, 5, 10} and
maximum adjacent difference would be
10 - 5 = 5

Input: arr[] = {2, 4, 8, 11}
Output: 4
*/

void FindMinMax(const std::vector<int>& arr, int& min, int& max)
{
    min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
    }
}

struct Bucket {
    int min = INT_MAX, max = INT_MIN;

    bool isEmpty() const {
        return min > max;
    }
};

int MaxGap(const std::vector<int>& arr)
{
    int n = arr.size();
    int min, max;
    FindMinMax(arr, min, max);
    int interval = (max - min) / (n - 1);
    if (interval == 0) {
        interval = 1;
    }
    int nbuckets = (max - min) / interval + 1;

    int maxGap = 0;
    std::vector<Bucket> buckets(nbuckets);
    for (auto& num : arr) {
        int iBucket = (num - min) / interval;
        auto& bucket = buckets[iBucket];
        bucket.min = std::min(bucket.min, num);
        bucket.max = std::max(bucket.max, num);
    }
    const Bucket* prevBucket = nullptr;
    for (int i = 0; i < buckets.size(); i++) {
        const auto& bucket = buckets[i];
        if (bucket.isEmpty()) {
            continue;
        }
        // max gap must between previous.max and current.min,
        // since in one bucket, the min/max max diff will be < internal
        // the diff between previous.max and current.min might be > internal
        if (prevBucket && !prevBucket->isEmpty()) {
            maxGap = std::max(maxGap, (bucket.min - prevBucket->max));
        }
        prevBucket = &bucket;
    }
    return maxGap;
}

int main()
{
    {
        std::vector<int> arr = { 1, 7, 3, 4 };
        std::cout << MaxGap(arr) << "\n";  // 3 (4 => 7)
    }
}
