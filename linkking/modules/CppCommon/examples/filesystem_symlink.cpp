

#include "filesystem/symlink.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppCommon::Symlink symlink("example.lnk");

    // Create a new symbolic link from the executable path
    CppCommon::Symlink::CreateSymlink(CppCommon::Path::executable(), symlink);

    // Read symbolic link target
    std::cout << "Symbolic link target: " << symlink.target() << std::endl;

    // Remove symbolic link
    CppCommon::Symlink::Remove(symlink);

    return 0;
}
