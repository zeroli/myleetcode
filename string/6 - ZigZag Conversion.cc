#include "utils.h"

/*
The string “PAYPALISHIRING” is written in a zigzag pattern on a given number of rows like this:
 (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: “PAHNAPLSIIGYIR”

Write the code that will take a string and make this conversion given a number of rows:
 string convert(string s, int numRows);
*/

// could use recursive call, each call will return string array with length row
// and then insert more into head to form final one
std::string ZigzagConvert(const std::string& str, int nRows)
{
    std::string ret;
    int maxstep = 2 * (nRows - 1);
    int step = maxstep;
    for (int i = 0; i < nRows; i++)
    {
        if (step == 0) {
            step = maxstep;  // restart, reach to nrow-1
        }
        // get one row with "step" steps
        int j = i;
        ret += str[j];
        while (true) {
            j += step;
            if (j >= str.size()) break;
            ret += str[j];
            // no inverse step to take, continue previous one
            if (maxstep == step) continue;
            j += (maxstep - step);
            if (j >= str.size()) break;
            ret += str[j];
        }
        std::cout << i << ": " << ret << "\n";
        step -= 2;
    }

    return ret;
}

int main()
{
    {
        std::string str = "PAYPALISHIRING";
        int nRows = 3;
        std::cout << ZigzagConvert(str, nRows) << "\n";  // PAHNAPLSIIGYIR
    }
}
