/*
实现一个栈，提供接口max，返回当前栈中最大值
*/

#include "utils.h"

/*
思路就是把元素和最大值结合作为stack中的元素，
每push一个元素，将当前元素与当前最大值进行比较，求取最大值
每pop一个元素时，直接弹出，因为下一个top包含自己对应的最大值
时间复杂度都是O(1)，但是空间复杂度会多出一倍，用来记录最大值
*/
/*
我们可以减少空间复杂度，对于连续push进去的元素，它们可能有相同的最大值
我们只要存储最大值和统计个数
每push一个元素，如果比当前最大值小，那么那个最大值个数加1
否则新开一个最大值记录，并设置个数为1
每pop时，将当前最大值个数减1，如果减到0了，
则去除这个最大值记录。
*/

struct StackWithMax {
public:
    void Push(int ele)
    {
        std::cout << "Push(" << ele << ") ";
        stk.push(ele);

        if (maxstk.empty()) {
            maxstk.push({ele, 1});
        } else {
            if (ele > maxstk.top().max) {
                maxstk.push({ele, 1});
            } else if (ele == maxstk.top().max) {
                maxstk.top().cnt++;
            }
        }
        std::cout << " => Max " << Max() << "\n";
    }
    int Pop()
    {
        assert(!stk.empty());
        auto ele = stk.top();
        stk.pop();
        std::cout << "Pop " << ele << " ";
        if (ele == maxstk.top().max) {
            if (--maxstk.top().cnt == 0) {
                maxstk.pop();
            }
        }
        std::cout << " => Max " << Max() << "\n";
    }

    int Max() const
    {
        assert(!maxstk.empty());
        return maxstk.top().max;
    }
private:
    std::stack<int> stk;
    struct MaxCnt {
        int max;
        int cnt;
    };
    std::stack<MaxCnt> maxstk;
};

int main()
{
    {
        StackWithMax stkm;
        stkm.Push(2); assert(2 == stkm.Max());
        stkm.Push(2); assert(2 == stkm.Max());
        stkm.Push(1); assert(2 == stkm.Max());
        stkm.Push(4); assert(4 == stkm.Max());
        stkm.Push(5); assert(5 == stkm.Max());
        stkm.Push(5); assert(5 == stkm.Max());
        stkm.Push(3); assert(5 == stkm.Max());
        stkm.Pop(); assert(5 == stkm.Max());
        stkm.Pop(); assert(5 == stkm.Max());
        stkm.Pop(); assert(4 == stkm.Max());
        stkm.Pop(); assert(2 == stkm.Max());
        stkm.Push(0); assert(2 == stkm.Max());
        stkm.Push(3); assert(3 == stkm.Max());
    }
}
