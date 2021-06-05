
#include "filesystem/directory.h"

#include <iostream>

int main(int argc, char** argv)
{
    // Get the current directory
    CppCommon::Directory current(".");

    // Iterate through all directory entries
    for (const auto& entry : current)
        std::cout << entry.filename() << std::endl;

    return 0;
}
