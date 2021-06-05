

#include "filesystem/path.h"
#include "time/timestamp.h"

#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Touch path is required!" << std::endl;
        return -1;
    }

    CppCommon::Path::SetModified(argv[1], CppCommon::UtcTimestamp());
    return 0;
}
