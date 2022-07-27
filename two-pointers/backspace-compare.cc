#include "utils.h"

int GetNextValidCharIndex(const std::string& str, int index)
{
    int ndeletes = 0;
    while (index >= 0) {
        if (str[index] == '#') {
            ndeletes++;
        } else if (ndeletes > 0) {
            ndeletes--;
        } else {  // ndeletes == 0
            break;
        }
        index--;
    }
    // if ndeletes>0, while index < 0, then input is invalid
    return index;
}

bool BackspaceCompare(const std::string& str1, const std::string& str2)
{
    int i = str1.size() - 1;
    int j = str2.size() - 1;
    while (i >=0 && j >= 0) {
        int s1 = GetNextValidCharIndex(str1, i);
        int s2 = GetNextValidCharIndex(str2, j);
        if (s1 < 0 && s2 < 0) {  // both reach to end
            return true;
        }
        if (s1 < 0 || s2 < 0) {  // either one reaches to end
            return false;
        }
        if (str1[s1] != str2[s2]) {
            return false;
        }
        i = s1 - 1;
        j = s2 - 1;
    }
    return true;
}

int main()
{
    {
        std::string str1="xy#z", str2="xzz#";
        std::cout << std::boolalpha << BackspaceCompare(str1, str2) << "\n";
    }
    {
        std::string str1="xy#z", str2="xyz#";
        std::cout << std::boolalpha << BackspaceCompare(str1, str2) << "\n";
    }
    {
        std::string str1="xp#", str2="xyz##";
        std::cout << std::boolalpha << BackspaceCompare(str1, str2) << "\n";
    }
    {
        std::string str1="xywrrmp", str2="xywrrmu#p";
        std::cout << std::boolalpha << BackspaceCompare(str1, str2) << "\n";
    }

}
