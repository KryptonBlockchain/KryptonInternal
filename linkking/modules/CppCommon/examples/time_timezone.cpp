
#include "time/timezone.h"

#include <iostream>

void show(const CppCommon::Timezone& time_zone)
{
    std::cout << "Time.name() = " << time_zone.name() << std::endl;
    std::cout << "Time.offset() = " << time_zone.offset().seconds() << std::endl;
    std::cout << "Time.daylight() = " << time_zone.daylight().seconds() << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::cout << "UTC timezone:" << std::endl;
    show(CppCommon::Timezone::utc());

    std::cout << "Local timezone:" << std::endl;
    show(CppCommon::Timezone::local());

    return 0;
}
