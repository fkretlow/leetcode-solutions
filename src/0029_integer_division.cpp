#include <iostream>

class Solution {
public:
    int divide(int dividend, int divisor) const
    {
        int rem = std::abs(dividend);
        int q = 0;
        while (rem >= std::abs(divisor)) {
            rem -= std::abs(divisor);
            ++q;
        }
        if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0)) return -q;
        return q;
    }
};

void test(const int a, const int b)
{
    static const Solution instance;
    std::cout << a << '/' << b << " = " << instance.divide(a,b) << std::endl;
}

int main()
{
    std::cout << "abs(-2147483648)=" << std::abs(-2147483648) << std::endl;
    test(10,3);
    test(10,-3);
    test(0,1);
    test(1,1);
    test(7,2);
    test(-2147483648,-1);
    return 0;
}
