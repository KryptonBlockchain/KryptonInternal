

#include "common/uint256.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppCommon::uint256_t a(0xFEDBCA9876543210ull);
    CppCommon::uint256_t b(0ull, 0ull, 0xFEDBCA9876543210ull, 0xFEDBCA9876543210ull);

    std::cout << a << " * " << b << " = " << (a * b) << std::endl;
    std::cout << b << " / " << a << " = " << (b / a) << std::endl;
    return 0;
}
