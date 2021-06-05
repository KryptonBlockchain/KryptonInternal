

#include "system/source_location.h"

#include <iostream>

int main(int argc, char** argv)
{
    std::cout << "Source location: " << __LOCATION__ << std::endl;
    return 0;
}
