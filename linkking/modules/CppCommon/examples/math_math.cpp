
#include "math/math.h"

#include <iostream>

int main(int argc, char** argv)
{
    uint64_t a = 4984198405165151231;
    uint64_t b = 6132198419878046132;
    uint64_t c = 9156498145135109843;
    std::cout << "Math::MulDiv64(" << a << " * " << b << " / " << c << ") = " << CppCommon::Math::MulDiv64(a, b, c) << std::endl;
    return 0;
}
