
#ifndef LINKKINGSERVER_ASIO_SSL_CONTEXT_H
#define LINKKINGSERVER_ASIO_SSL_CONTEXT_H

#include "service.h"

namespace LinkKing {
namespace Asio {

//! SSL context
/*!
    SSL context is used to handle and validate certificates in SSL clients and servers.

    Thread-safe.
*/
class SSLContext : public asio::ssl::context
{
public:
    using asio::ssl::context::context;

    SSLContext(const SSLContext&) = delete;
    SSLContext(SSLContext&&) = delete;
    ~SSLContext() = default;

    SSLContext& operator=(const SSLContext&) = delete;
    SSLContext& operator=(SSLContext&&) = delete;

    //! Configures the context to use system root certificates
    void set_root_certs();
};

} // namespace Asio
} // namespace LinkKing

#endif // LINKKINGSERVER_ASIO_SSL_CONTEXT_H
