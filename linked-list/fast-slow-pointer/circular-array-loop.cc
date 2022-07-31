#include "utils.h"
#include "linked-list/internal-util.h"

int GetNextIndex(const std::vector<int>& arr, bool isForward, int curIndex)
{
    bool dir = arr[curIndex] > 0;
    if (dir != isForward) { // different direction
        return -1;
    }

    int nextIndex = (curIndex + arr[curIndex]) % arr.size();
    if (nextIndex < 0) {  // wrap up
        nextIndex += arr.size();
    }
    if (nextIndex == curIndex) {  // only one element loop
        return -1;
    }
    return nextIndex;
}

bool ContainsLoop(const std::vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++) {
        bool isForward = arr[i] > 0;
        int slow = i, fast = i;
        do {
            slow = GetNextIndex(arr, isForward, slow);  // take a step
            fast = GetNextIndex(arr, isForward, fast);  // take a step
            if (fast != -1) {
                fast = GetNextIndex(arr, isForward, fast);  // take another step
            }
        } while (slow != -1 && fast != -1 && slow != fast);

        if (slow != -1 && slow == fast) {  // found the cycle
            return true;
        }
    }
    return false;
}

int main()
{
    {
        std::vector<int> arr = { 1, 2, -1, 2, 2 };
        std::cout << std::boolalpha << ContainsLoop(arr) << "\n";  // true
    }
    {
        std::vector<int> arr = { 2, 2, -1, 2 };
        std::cout << std::boolalpha << ContainsLoop(arr) << "\n";  // true
    }
    {
        std::vector<int> arr = { 2, 1, -1, -2 };
        std::cout << std::boolalpha << ContainsLoop(arr) << "\n";  // false
    }

}
