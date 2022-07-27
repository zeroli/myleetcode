#include "utils.h"

#include "union-find.h"


bool Check(const std::vector<std::string>& strs)
{
    UnionFind uf(26);
    for (const auto& str : strs) {
        if (str[1] == '=') {
            auto c1 = str[0];
            auto c2 = str[3];
            uf.Union(c1 - 'a', c2 - 'a');
        }
    }
    for (const auto& str : strs) {
        if (str[1] == '!') {
            auto c1 = str[0];
            auto c2 = str[3];
            if (uf.Connected(c1 - 'a', c2 - 'a')) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    {
        std::vector<std::string> strs = { "a==b", "b!=a" };
        std::cout << std::boolalpha << Check(strs) << "\n";
    }
    {
        std::vector<std::string> strs = { "b==a","a==b" };
        std::cout << std::boolalpha << Check(strs) << "\n";
    }
    {
        std::vector<std::string> strs = { "b==a","a==c", "b==c" };
        std::cout << std::boolalpha << Check(strs) << "\n";
    }
    {
        std::vector<std::string> strs = { "b==a","a==c", "b!=c" };
        std::cout << std::boolalpha << Check(strs) << "\n";
    }
}
