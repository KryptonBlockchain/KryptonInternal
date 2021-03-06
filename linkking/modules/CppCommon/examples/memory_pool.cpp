
#include "memory/allocator_pool.h"

#include <iostream>

int main(int argc, char** argv)
{
    CppCommon::DefaultMemoryManager auxiliary;
    CppCommon::PoolMemoryManager<CppCommon::DefaultMemoryManager> manger(auxiliary);
    CppCommon::PoolAllocator<int, CppCommon::DefaultMemoryManager> alloc(manger);

    int* v = alloc.Create(123);
    std::cout << "v = " << *v << std::endl;
    alloc.Release(v);

    int* a = alloc.CreateArray(3, 123);
    std::cout << "a[0] = " << a[0] << std::endl;
    std::cout << "a[1] = " << a[1] << std::endl;
    std::cout << "a[2] = " << a[2] << std::endl;
    alloc.ReleaseArray(a);

    return 0;
}
