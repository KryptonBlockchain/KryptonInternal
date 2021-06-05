
#include "system/dll.h"

#include <memory>

class IRandom
{
public:
    virtual ~IRandom() = default;
    virtual int random() = 0;
};

API bool PluginRandomCreate(IRandom** ppRandom);
API bool PluginRandomRelease(IRandom* pRandom);
