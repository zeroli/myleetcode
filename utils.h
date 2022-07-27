#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <numeric>

using StrArray_t = std::vector<std::string>;
using StrPath_t = std::vector<std::string>;
template <typename T>
using Array2D_t = std::vector<std::vector<T>>;

template <typename T1, typename T2>
std::ostream& operator <<(std::ostream& ostr, const std::pair<T1, T2>& t)
{
    ostr << "(" << t.first << "," << t.second << ")";
    return ostr;
}

template <typename T>
std::ostream& operator <<(std::ostream& ostr, const std::vector<T>& t)
{
    ostr << "[";
    if (!t.empty()) {
        for (int i = 0; i < (int)t.size() - 1; i++) {
            ostr << t[i] << ", ";
        }
        ostr << t.back();
    }
    ostr << "]";
    return ostr;
}

template <typename T>
std::ostream& operator <<(std::ostream& ostr, const std::set<T>& t)
{
    ostr << "{ ";
    for (auto&& p : t) {
        ostr << p << ", ";
    }
    ostr << " }";
    return ostr;
}

template <typename T>
std::ostream& operator <<(std::ostream& ostr, const std::unordered_set<T>& t)
{
    ostr << "{ ";
    for (auto&& p : t) {
        ostr << p << ", ";
    }
    ostr << " }";
    return ostr;
}

template <typename T1, typename T2>
std::ostream& operator <<(std::ostream& ostr, const std::map<T1, T2>& t)
{
    ostr << "{ ";
    for (auto&& p : t) {
        ostr << p << ", ";
    }
    ostr << " }";
    return ostr;
}

template <typename T1, typename T2>
std::ostream& operator <<(std::ostream& ostr, const std::unordered_map<T1, T2>& t)
{
    ostr << "{ ";
    for (auto&& p : t) {
        ostr << p << ", ";
    }
    ostr << " }";
    return ostr;
}

template <typename T>
std::ostream& operator <<(std::ostream& ostr, const Array2D_t<T>& m)
{
    ostr << "[\n";
    for (auto&& arr : m) {
        ostr << "  " << arr << "\n";
    }
    ostr << "]";
    return ostr;
}

#endif  // UTILS_H_
