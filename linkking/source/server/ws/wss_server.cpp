

#include "server/ws/wss_server.h"

namespace LinkKing {
namespace WS {

bool WSSServer::CloseAll(int status)
{
    std::scoped_lock locker(_ws_send_lock);

    PrepareSendFrame(WS_FIN | WS_CLOSE, false, nullptr, 0, status);
    if (!Multicast(_ws_send_buffer.data(), _ws_send_buffer.size()))
        return false;

    return HTTPSServer::DisconnectAll();
}

bool WSSServer::Multicast(const void* buffer, size_t size)
{
    if (!IsStarted())
        return false;

    if (size == 0)
        return true;

    assert((buffer != nullptr) && "Pointer to the buffer should not be null!");
    if (buffer == nullptr)
        return false;

    std::shared_lock<std::shared_mutex> locker(_sessions_lock);

    // Multicast all WebSocket sessions
    for (auto& session : _sessions)
    {
        auto wss_session = std::dynamic_pointer_cast<WSSSession>(session.second);
        if (wss_session)
        {
            std::scoped_lock ws_locker(wss_session->_ws_send_lock);

            if (wss_session->_ws_handshaked)
                wss_session->SendAsync(buffer, size);
        }
    }

    return true;
}

} // namespace WS
} // namespace LinkKing