#include "utils.h"
#include "min-heap.h"

#include <cassert>

int main()
{
    {
        MinHeap<int> mh;
        mh.Push(1);
        mh.Push(3);
        mh.Push(2);
        std::cout << mh << "\n";
        assert(mh.Size() == 3);
        assert(mh.Top() == 1);
        mh.Pop();
        std::cout << mh << "\n";
        assert(mh.Top() == 2);
        mh.Pop();
        std::cout << mh << "\n";
        assert(mh.Top() == 3);

        mh.Push(-1);
        mh.Push(3);
        mh.Push(1);
        std::cout << mh << "\n";
        assert(mh.Top() == -1);

        while (!mh.IsEmpty()) {
            mh.Pop();
        }
    }
    {
        std::vector<int> arr = {1, 2, 3, -1, 0, 7, 9, 20, 10, 4 };
        MinHeap<int> mh(arr);
        std::sort(arr.begin(), arr.end());

        std::cout << mh << "\n";
        std::vector<int> arr2;
        while (!mh.IsEmpty()) {
            arr2.push_back(mh.Top());
            mh.Pop();
            std::cout << "after pop " << arr2.back() << ": " << mh << "\n";
        }
        std::cout << "arr : " << arr << "\n";
        std::cout << "arr2: " << arr2 << "\n";
        assert(arr == arr2);
    }
}
