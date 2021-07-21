
#include "system/dll.h"

#include <cstdlib>

API int PluginRandom()
{
   return std::rand();
}
