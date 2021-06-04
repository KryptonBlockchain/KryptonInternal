
#include "server/asio/udp_resolver.h"

namespace LinkKing {
namespace Asio {

UDPResolver::UDPResolver(const std::shared_ptr<Service>& service)
    : _service(service),
      _io_service(_service->GetAsioService()),
      _strand(*_io_service),
      _strand_required(_service->IsStrandRequired()),
      _resolver(*_io_service)
{
    assert((service != nullptr) && "Asio service is invalid!");
    if (service == nullptr)
        throw CppCommon::ArgumentException("Asio service is invalid!");
}

} // namespace Asio
} // namespace LinkKing
