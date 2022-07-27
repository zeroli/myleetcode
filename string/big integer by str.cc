#include "utils.h"

#include <cassert>

struct BigInteger
{
public:
    BigInteger() = default;
    BigInteger(const std::string& numStr)
        : d_numStr(numStr[0] == '-' ? numStr.substr(1) : numStr)
        , d_sign(numStr[0] == '-' ? '-' : '+')
    {
    }

    BigInteger(const BigInteger& other) = default;
    BigInteger& operator =(const BigInteger& other) = default;
    BigInteger(BigInteger&& other) = default;
    BigInteger& operator =(BigInteger&& other) = default;

    // define addition of 2 BigIntegers
    friend BigInteger operator + (const BigInteger& integer1, const BigInteger& integer2)
    {
        if (integer1.IsZero()) {
            return integer2;
        }
        if (integer2.IsZero()) {
            return integer1;
        }

        if (integer1.IsPositive() && integer2.IsNegative()) {
            return Subtract2Positives(integer1, (-integer2));
        }
        else if (integer1.IsNegative() && integer2.IsPositive()) {
            return Subtract2Positives(integer2, (-integer1));
        }
        else if (integer1.IsNegative() && integer2.IsNegative()) {
            return -(Add2Positives((-integer1), (-integer2)));
        } else {
            return Add2Positives(integer1, integer2);
        }
    }

    // define substraction of 2 BigIntegers
    friend BigInteger operator -(const BigInteger& integer1, const BigInteger& integer2)
    {
        if (integer1.IsZero()) {
            return -integer2;
        }
        if (integer2.IsZero()) {
            return integer1;
        }

        if (integer1.IsPositive() && integer2.IsPositive()) {
            return Subtract2Positives(integer1, integer2);
        }
        else if (integer1.IsPositive() && integer2.IsNegative()) {
            return Add2Positives(integer1, (-integer2));
        }
        else if (integer1.IsNegative() && integer2.IsPositive()) {
            return -Add2Positives((-integer1), integer2);
        }
        else { // (integer1.IsNegative() && integer2.IsNegative())
            return Subtract2Positives((-integer2), (-integer1));
        }
    }

    // define - minus operator
    BigInteger operator -() const
    {
        BigInteger ret(*this);
        ret.d_sign = (d_sign == '+' ? '-' : '+');
        return ret;
    }

    bool IsNegative() const {
        return d_sign == '-';
    }
    bool IsZero() const {
        return d_numStr.empty() ||
            (d_numStr[0] == '0' && d_numStr.size() == 1);
    }
    bool IsPositive() const {
        return d_sign == '+';
    }

    static BigInteger Add2Positives(const BigInteger& integer1, const BigInteger& integer2)
    {
        assert(integer1.IsPositive() && integer2.IsPositive());

        int n1 = integer1.d_numStr.size();
        int n2 = integer2.d_numStr.size();
        BigInteger sum;

        auto& sumStr = sum.d_numStr;
        sumStr.reserve(std::max(n1, n2) + 1);
        auto& str1 = integer1.d_numStr;
        auto& str2 = integer2.d_numStr;

        int carrier = 0;
        int i =  n1 - 1;
        int j =  n2 - 1;
        while (i >= 0 || j >= 0) {
            int tmp = carrier;
            if (i >= 0) {
                tmp += (str1[i] - '0');
                i--;
            }
            if (j >= 0) {
                tmp += (str2[j] - '0');
                j--;
            }
            carrier = tmp / 10;
            tmp = tmp % 10;
            sumStr.push_back(tmp + '0');
        }
        if (carrier > 0) {
            sumStr.push_back(carrier + '0');
        }
        std::reverse(sumStr.begin(), sumStr.end());
        return sum;
    }

    static BigInteger Subtract2Positives(const BigInteger& integer1, const BigInteger& integer2)
    {
        assert(integer1.IsPositive() && integer2.IsPositive());

        BigInteger diff;
        auto& diffStr = diff.d_numStr;

        int carrier = 0;
        int n1 = integer1.d_numStr.size();
        int n2 = integer2.d_numStr.size();
        diffStr.reserve(std::max(n1, n2));

        const auto& str1 = integer1.d_numStr;
        const auto& str2 = integer2.d_numStr;

        int i = n1 - 1, j = n2 - 1;
        while (i >= 0 || j >= 0) {
            int tmp = 0;
            tmp += carrier;
            if (i >= 0) {
                tmp += (str1[i] - '0');
                i--;
            }
            if (j >= 0) {
                tmp -= (str2[j] - '0');
                j--;
            }
            if (tmp < 0) {
                tmp += 10;
                carrier = -1;
            } else {
                carrier = 0;
            }
            diffStr.push_back(tmp + '0');
        }
        if (carrier < 0) {
            return -Subtract2Positives(integer2, integer1); // note, need minus it
        }

        std::reverse(diffStr.begin(), diffStr.end());  // note, need reverse
        // remove leading '0', but leave a '0'
        while (diffStr.size() > 1 && diffStr.front() == '0') {
            diffStr.erase(diffStr.begin());
        }
        return diff;
    }


    friend std::ostream& operator <<(std::ostream& outstr, const BigInteger& integer)
    {
        integer.Print(outstr);
        return outstr;
    }

    std::string d_numStr;  // 123 digits only
    char d_sign = '+';  // '+' or '-'

private:
    void Print(std::ostream& outstr) const {
        outstr << ((d_sign == '-') ? "-" : "");
        outstr << d_numStr;
    }
};

int main()
{
    {
        BigInteger sum = BigInteger("123") + BigInteger("345");
        std::cout << "sum(123+345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("1123") + BigInteger("345");
        std::cout << "sum(1123+345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("823") + BigInteger("345");
        std::cout << "sum(823+345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("825") + BigInteger("345");
        std::cout << "sum(825+345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("855") + BigInteger("345");
        std::cout << "sum(855+345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("-123") + BigInteger("-345");
        std::cout << "sum(-123+-345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("-855") + BigInteger("-345");
        std::cout << "sum(-855+-345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("-1123") + BigInteger("-345");
        std::cout << "sum(-1123+-345) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("1200") + BigInteger("0");
        std::cout << "sum(1200+0) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("0") + BigInteger("1000");
        std::cout << "sum(0+1000) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("-1123") + BigInteger("1123");
        std::cout << "sum(-1123+1123) = " << sum << "\n";
    }
    {
        BigInteger sum = BigInteger("1123") + BigInteger("-1123");
        std::cout << "sum(1123+-1123) = " << sum << "\n";
    }
    {
        BigInteger diff = BigInteger("100") - BigInteger("0");
        std::cout << "diff(100-0) = " << diff << "\n"; // 100
    }
    {
        BigInteger diff = BigInteger("0") - BigInteger("100");
        std::cout << "diff(0-100) = " << diff << "\n";  // -100
    }
    {
        BigInteger diff = BigInteger("200") - BigInteger("180");
        std::cout << "diff(200-180) = " << diff << "\n";  // 20
    }
    {
        BigInteger diff = BigInteger("200") - BigInteger("10");
        std::cout << "diff(200-10) = " << diff << "\n";  // 190
    }
    {
        BigInteger diff = BigInteger("180") - BigInteger("200");
        std::cout << "diff(180-200) = " << diff << "\n";  // -20
    }
    {
        BigInteger diff = BigInteger("10") - BigInteger("200");
        std::cout << "diff(10-200) = " << diff << "\n";  // -190
    }
    {
        BigInteger diff = BigInteger("-100") - BigInteger("10");
        std::cout << "diff(-100-10) = " << diff << "\n";  // -110
    }
    {
        BigInteger diff = BigInteger("10") - BigInteger("-100");
        std::cout << "diff(10- -100) = " << diff << "\n";  // 110
    }
    {
        BigInteger diff = BigInteger("-10") - BigInteger("-100");
        std::cout << "diff(-10- -100) = " << diff << "\n";  // 90
    }
    {
        BigInteger diff = BigInteger("-100") - BigInteger("-10");
        std::cout << "diff(-100- -10) = " << diff << "\n";  // -90
    }
    {
        BigInteger diff = BigInteger("-100") - BigInteger("-100");
        std::cout << "diff(-100- -100) = " << diff << "\n";  // 0
    }
}
