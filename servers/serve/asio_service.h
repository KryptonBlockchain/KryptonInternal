#include "server/asio/service.h"

class AsioService : public LinkKing::Asio::Service
{
public:
    using LinkKing::Asio::Service::Service;

protected:
    void onError(int error, const std::string& category, const std::string& message) override
    {
        std::cout << "Asio service caught an error with code " << error << " and category '" << category << "': " << message << std::endl;
    }
};