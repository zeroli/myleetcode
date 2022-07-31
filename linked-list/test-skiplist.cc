#include "utils.h"
#include "skip-list.h"

int main()
{
    {
        ds::SkipList sl;
        sl.Insert(1);
        sl.Insert(2);
        sl.Insert(10);
        sl.Insert(8);
        sl.Insert(15);
        assert(sl.Contains(2));
        std::cout << sl << "\n";
        assert(sl.First() == 1);
        assert(sl.Last() == 15);
        sl.Delete(10);
        std::cout << sl << "\n";
    }
}
