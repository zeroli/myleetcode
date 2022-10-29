/*
实现一个queue，带有Max API接口
*/

#include "utils.h"

/*
1 6 2 4
加入元素以从左到右的顺序push到队列中
push 1:  max = 1
push 6:  max = 6 (6 > 1)
push 2:  max = 6 (2 < 6)
push 4:  max = 6 (4 < 6)
pop 1 :  max = 6 (1 < 6)
pop 6 :  max = 4 (4是剩下元素中第2大的数)
pop 2 :  max = 4 (2 < 4)
pop 4 :  没有最大元素了

我们需要用一个单调递减的队列来记录max值
后push进来的值会弹出单调递减队列中比它小的max，
否则直接push到这个单调递减队列中
*/

struct QueueWithMax
{
public:
    void Push(int x)
    {
        std::cout << "Push " << x << ", ";
        queue.push(x);
        // 弹出所有单调递减队列中比x小的数，从后往前遍历
        while (!maxq.empty() && maxq.back() < x) {
            maxq.pop_back();
        }
        maxq.push_back(x);
        std::cout << " Max: " << Max() << "\n";
    }

    int Pop()
    {
        auto x = queue.front();
        queue.pop();
        std::cout << "Pop " << x << ", ";

        if (x == maxq.front()) {
            maxq.pop_front();
        }
        std::cout << " Max: " << Max() << "\n";
    }

    int Max() const
    {
        assert(!maxq.empty());
        return maxq.front();
    }

private:
    std::queue<int> queue;
    std::deque<int> maxq;
};

int main()
{
    {
        QueueWithMax qm;
        qm.Push(1); assert(1 == qm.Max());
        qm.Push(2); assert(2 == qm.Max());
        qm.Push(3); assert(3 == qm.Max());
        qm.Push(1); assert(3 == qm.Max());
        qm.Pop(); assert(3 == qm.Max());
        qm.Pop(); assert(3 == qm.Max());
        qm.Pop(); assert(1 == qm.Max());
        qm.Push(2); assert(2 == qm.Max());
        qm.Pop(); assert(2 == qm.Max());
    }
    {
        QueueWithMax qm;
        qm.Push(1); assert(1 == qm.Max());
        qm.Push(6); assert(6 == qm.Max());
        qm.Push(2); assert(6 == qm.Max());
        qm.Push(4); assert(6 == qm.Max());
        qm.Pop(); assert(6 == qm.Max());
        qm.Pop(); assert(4 == qm.Max());
        qm.Pop(); assert(4 == qm.Max());
    }
}
