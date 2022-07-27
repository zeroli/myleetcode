#include "utils.h"

/*
Given a string with repeated characters, the task is to rearrange characters in a string
 so that no two adjacent characters are same.
Note : It may be assumed that the string has only lowercase English alphabets.
*/

struct Item {
    char c;
    int cnt;
    friend bool operator >(const Item& t1, const Item& t2)
    {
        return t1.cnt > t2.cnt;
    }
};

std::string Rearrange(const std::string& str)
{
    std::vector<Item> sorted;
    std::map<char, int> charFreqs;
    for (auto c : str) {
        charFreqs[c]++;
    }
    for (auto& cf : charFreqs) {
        sorted.push_back({cf.first, cf.second});
    }
    std::sort(sorted.begin(), sorted.end(), std::greater<Item>());

    int maxlen = sorted[0].cnt;
    std::vector<std::string> parts(maxlen);
    int pos = 0;
    for (auto& p : sorted) {
        for (int i = 0; i < p.cnt; i++) {
            pos = pos % maxlen;
            parts[pos].push_back(p.c);
            pos++;
        }
    }
    std::string finalStr;
    finalStr.reserve(str.size());
    for (auto&& part : parts) {
        std::move(part.begin(), part.end(), std::back_inserter(finalStr));
        //finalStr.insert(finalStr.end(), part.begin(), part.end());
    }
    return finalStr;
}

int main()
{
    {
        std::string str = "aaabc";
        std::cout << Rearrange(str) << "\n";  // abaca
    }
    {
        std::string str = "aaabb";
        std::cout << Rearrange(str) << "\n";  // ababa
    }
    {
        std::string str = "aa";
        std::cout << Rearrange(str) << "\n";  // aa (FAIL)
    }
    {
        std::string str = "aaaabc";
        std::cout << Rearrange(str) << "\n";  // abacaa (FAIL)
    }
}
