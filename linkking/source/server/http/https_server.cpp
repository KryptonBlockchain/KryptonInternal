
#include "server/http/https_server.h"

#include "string/format.h"

namespace LinkKing {
namespace HTTP {

void HTTPSServer::AddStaticContent(const CppCommon::Path& path, const std::string& prefix, const CppCommon::Timespan& timeout)
{
    auto hanlder = [](CppCommon::FileCache & cache, const std::string& key, const std::string& value, const CppCommon::Timespan& timespan)
    {
        auto header = HTTPResponse();
        header.SetBegin(200);
        header.SetContentType(CppCommon::Path(key).extension().string());
        header.SetHeader("Cache-Control", "max-age={}"_format(timespan.seconds()));
        header.SetBody(value);
        return cache.insert(key, header.cache(), timespan);
    };

    cache().insert_path(path, prefix, timeout, hanlder);
}

} // namespace HTTP
} // namespace LinkKing
