#include "utils.h"

/*
      1  2  3
 x       4 5
  -----------------
         1  5
      1 0
      5
      1 2
      8
   4
========
    5 5 3  5
*/
std::string Multiply(const std::string& str1, const std::string& str2)
{
    int m = str1.size();
    int n = str2.size();
    std::vector<int> res(m + n);
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int p1 = i + j, p2 = i + j + 1;
            int mul = (str1[i] - '0') * (str2[j] - '0');
            int sum = mul + res[p2];
            res[p1] += sum / 10;
            res[p2] = sum % 10;
        }
    }
    // remove leading '0'
    int i = 0;
    while (i < res.size() && res[i] == 0) {
        i++;
    }
    std::string resStr;
    while (i < res.size()) {
        resStr.push_back(res[i++] + '0');
    }
    return resStr;
}

int main()
{
    {
        std::string str1 = "123";
        std::string str2 = "45";
        std::cout << Multiply(str1, str2) << "\n";  // 5535
    }
    {
        std::string str1 = "999";
        std::string str2 = "999";
        std::cout << Multiply(str1, str2) << "\n";  // 998001
    }
}
