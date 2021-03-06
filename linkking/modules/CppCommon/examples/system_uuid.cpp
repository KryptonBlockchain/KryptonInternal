
#include "system/uuid.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "UUID::Nil(): " << CppCommon::UUID::Nil() << std::endl;
    std::cout << "UUID::Sequential(): " << CppCommon::UUID::Sequential() << std::endl;
    std::cout << "UUID::Random(): " << CppCommon::UUID::Random() << std::endl;
    std::cout << "UUID::Secure(): " << CppCommon::UUID::Secure() << std::endl;
    return 0;
}
