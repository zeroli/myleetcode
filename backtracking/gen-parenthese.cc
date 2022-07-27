#include "utils.h"

using Result_t = std::vector<std::string>;
Result_t results;

/*
这个问题本质上是一个暴力穷举，在2n个位置上放置( 和 )，
每个位置可以放"("也可以放")"，共有多少种组合及其它们的组合列表。
但是所有这些组合中，有些组合是不合法的，
因此我们在回溯算法中需要进行剪枝。
1）左括号剩余数大于右括号剩余数，是不合法的。
base case就是左右括号剩余数同时为0时。
*/
// l: 左括号剩余数，r: 右括号剩余数
void GenerateParentheses1_(int l, int r, std::string& path)
{
    if (l == 0 && r == 0) {
        results.push_back(path);
        return;
    }
    if (l > r) return;  // invalid, pruning
    if (l < 0 || r < 0) return;

    if (l > 0) {
        path.push_back('(');
        GenerateParentheses1_(l - 1, r, path);
        path.pop_back();
    }
    if (r > 0) {
        path.push_back(')');
        GenerateParentheses1_(l, r - 1, path);
        path.pop_back();
    }
}

void GenerateParentheses_(int n, int l, int r, std::string& path)
{
    if (path.size() == 2 * n) {
        results.push_back(path);
        return;
    }
    if (l < n) {
        path.push_back('(');
        GenerateParentheses_(n, l+1, r, path);
        path.pop_back();
    }
    if (r < l) {  // if left parentheses has more, need right parentheses
        path.push_back(')');
        GenerateParentheses_(n, l, r+1, path);
        path.pop_back();
    }
}

Result_t GenerateParentheses(int n)
{
    results.clear();
    std::string path;
    GenerateParentheses_(n, 0, 0, path);
    return results;
}

Result_t GenerateParentheses1(int n)
{
    results.clear();
    std::string path;
    GenerateParentheses1_(n, n, path);
    return results;
}

int main()
{
    {
        auto results = GenerateParentheses(3);
        std::cout << results << "\n";
    }
    {
        auto results = GenerateParentheses1(3);
        std::cout << results << "\n";
    }
}
