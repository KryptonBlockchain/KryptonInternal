
#include "errors/system_error.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Last system error: " << CppCommon::SystemError::GetLast() << std::endl;
    std::cout << "Last system description: " << CppCommon::SystemError::Description() << std::endl;
    return 0;
}
