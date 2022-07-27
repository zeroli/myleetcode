#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <iostream>

using VecList_t = std::vector<std::string>;

struct Solution {
    std::vector<VecList_t> d_result;
    VecList_t d_ipStr;

    std::vector<VecList_t> SplitIntoIP(const std::string& ipNum)
    {
        backtracking(ipNum, 0, 0);
        return d_result;
    }

    void backtracking(const std::string& ipNum, int startIdx, int done)
    {
        if (done == 3) {  // base case
            auto str = ipNum.substr(startIdx);
            if (IsValid(str)) {
                d_ipStr.push_back(str);
                d_result.push_back(d_ipStr);
                d_ipStr.pop_back();
            }
            return;
        }
        for (int i = startIdx; i < ipNum.size(); i++) {
            auto str = ipNum.substr(startIdx, i - startIdx + 1);
            if (!IsValid(str)) {
                break;
            }
            done++;
            d_ipStr.push_back(str);
            backtracking(ipNum, i + 1, done);
            done--;
            d_ipStr.pop_back();
        }
    }
private:
    bool IsValid(const std::string& str) const
    {
        if (str[0] == '0' && str.size() > 1) {
            return false;
        }
        for (int i = 0; i < str.size(); i++) {
            if (str[i] < '0' || str[i] > '9') {
                return false;
            }
        }
        return atoi(str.c_str()) <= 255;
    }
};

int main()
{
    std::string ipNum = "0250255255";
    std::cout << "input: " << ipNum << "\n";
    auto result = Solution().SplitIntoIP(ipNum);
    for (auto&& r : result) {
        std::copy(r.begin(), r.end(), std::ostream_iterator<std::string>(std::cout, "."));
        std::cout << "\n";
    }
    return 0;
}
