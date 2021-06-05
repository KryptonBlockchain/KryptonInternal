
#include "common/uint128.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppCommon::uint128_t a(0xABCDEFull);
    CppCommon::uint128_t b(0x12345ull, 0xFEDBCA9876543210ull);

    std::cout << a << " * " << b << " = " << (a * b) << std::endl;
    std::cout << b << " / " << a << " = " << (b / a) << std::endl;
    return 0;
}
