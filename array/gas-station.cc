/*
There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next
station (i+1). You begin the journey with an empty tank at one of the gas stations.
Return the starting gas station’s index if you can travel around the circuit once, otherwise return -1.
Note: The solution is guaranteed to be unique

Example 1:

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3
Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.
Example 2:

Input: gas = [2,3,4], cost = [3,4,3]
Output: -1
Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
*/
#include "utils.h"

// brute-force solution
// 时间复杂度为O(n ^ 2)
// 尝试从每一个gas station开始travel，中间一旦碰到sum < 0
// 代表无法走到下一站，fail
int TravelStartFrom(const std::vector<int>& gas, const std::vector<int>& cost)
{
    int n = gas.size();
    for (int k = 0; k < n; k++) {
        int sum = 0;
        int i = k;
        for (; i < (k + n); i++) {
            int j = i % n;
            sum += gas[j] - cost[j];
            if (sum < 0) {
                break;
            }
        }
        if (i == k + n) {
            return k;
        }
    }
    return -1;
}

int TravelStartFrom1(const std::vector<int>& gas, const std::vector<int>& cost)
{
    int n = gas.size();
    int j = 0; // 代表从0开始travel，加和为0
    int sum = 0;
    int total = 0;
    for (int i = 0; i < n; i++) {
        sum += gas[i] - cost[i];
        total += gas[i] - cost[i];
        // 第一次碰到加和变成负数，前面的加和为非负数
        // sum([j, i]) < 0
        // 接下来，该移动j到[j, i]的哪个位置才能使得sum[new_j, i] > 0呢?
        // 假设k=new_j，如果sum([j, k]) < 0，这种情况不太可能，
        // 因为前面我们推断出[j, i)遍历过程中，没有加和为负数的情况；
        // 如果sum([j, k)) >= 0，那么后部分sum([k, i])肯定<0，因为它们总和为负数
        // 因此不管移动j到哪个位置，都不能让sum([k, i])>=0.
        // 故而移动j到i+1位置，跳过前面所有的[j, i]，sum重置为0.
        if (sum < 0) {
            j = i + 1;
            sum = 0;
        }
    }
    // 如果最后sum < 0, j=n了，说明total < 0，那是肯定的。
    // 因为在遍历过程中，前面很多片段sum < 0，然后就被丢弃了
    // sum(part1) < 0, sum(part2) < 0, ...., sum(partn) < 0
    return total >= 0 ? j : -1;
}

int main()
{
    {
        std::vector<int> gas = { 1,2,3,4,5 };
        std::vector<int> cost = { 3,4,5,1,2 };
        std::cout << TravelStartFrom(gas, cost) << "\n";  // 3
        std::cout << TravelStartFrom1(gas, cost) << "\n";  // 3
    }
    {
        std::vector<int> gas = { 2,3,4 };
        std::vector<int> cost = { 3,4,3 };
        std::cout << TravelStartFrom(gas, cost) << "\n";  // -1
        std::cout << TravelStartFrom1(gas, cost) << "\n";  // -1
    }
}
