#include "asio_service.h"

#include "server/asio/tcp_server.h"

#include <iostream>

#include "nlohmann_json/single_include/nlohmann/json.hpp"

#include <sstream>

nlohmann::json info;

class ChatSession : public LinkKing::Asio::TCPSession
{
public:
    using LinkKing::Asio::TCPSession::TCPSession;

protected:
    nlohmann::json client;
    void onConnected() override
    {
        std::cout << "Chat TCP session with Id " << id() << " connected!" << std::endl;

        // Convert the IP address to std::string
        std::stringstream ss;
        ss << GetIPAddr();

        client["ip"] = ss.str();

        // Clear the stringstream
        ss.str("");
        ss.clear();

        // Convert the ID to string
        ss << id();
        client["id"] = ss.str();
        info["clients"].push_back(client);

        // Clear the stringstream
        ss.str("");
        ss.clear();

        // Send invite message
        std::string message("Hello from TCP chat! Please send a message or '!' to disconnect the client!");
        SendAsync(message);

        // TEMPORARY Send client json
        ss << info;
        std::string infoMessage(ss.str());
        SendAsync(infoMessage);
        ss.str("");
        ss.clear();
    }

    void onDisconnected() override
    {
        // Remove the client from the json on disconnect
        for (int i = 0; i < static_cast<int>(info["clients"].size()); i++)
        {
            if (info["clients"][i] == client)
            {
                info["clients"].erase(info["clients"].begin() + i);
            }
        }
        std::cout << "Chat TCP session with Id " << id() << " disconnected!" << std::endl;
    }

    void onReceived(const void* buffer, size_t size) override
    {
        std::string message((const char*)buffer, size);
        std::cout << "Incoming: " << message << std::endl;

        // Multicast message to all connected sessions
        server()->Multicast(message);

        // If the buffer starts with '!' the disconnect the current session
        if (message == "!")
            Disconnect();
    }

    void onError(int error, const std::string& category, const std::string& message) override
    {
        std::cout << "Chat TCP session caught an error with code " << error << " and category '" << category << "': " << message << std::endl;
    }
};

class ChatServer : public LinkKing::Asio::TCPServer
{
public:
    using LinkKing::Asio::TCPServer::TCPServer;

protected:
    std::shared_ptr<LinkKing::Asio::TCPSession> CreateSession(const std::shared_ptr<LinkKing::Asio::TCPServer>& server) override
    {
        return std::make_shared<ChatSession>(server);
    }

protected:
    void onError(int error, const std::string& category, const std::string& message) override
    {
        std::cout << "Chat TCP server caught an error with code " << error << " and category '" << category << "': " << message << std::endl;
    }
};

int main(int argc, char** argv)
{
//    info = {
//            {"clients", {1}}
//    };
    info["clients"] = nlohmann::json::array();
    // TCP server port
    int port = 1111;
    if (argc > 1)
        port = std::atoi(argv[1]);

    std::cout << "TCP server port: " << port << std::endl;

    std::cout << std::endl;

    // Create a new Asio service
    auto service = std::make_shared<AsioService>();

    // Start the Asio service
    std::cout << "Asio service starting...";
    service->Start();
    std::cout << "Done!" << std::endl;

    // Create a new TCP chat server
    auto server = std::make_shared<ChatServer>(service, port);

    // Start the server
    std::cout << "Server starting...";
    server->Start();
    std::cout << "Done!" << std::endl;

    std::cout << "Press Enter to stop the server or '!' to restart the server..." << std::endl;

    // Perform text input
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.empty())
            break;

        // Restart the server
        if (line == "!")
        {
            std::cout << "Server restarting...";
            server->Restart();
            std::cout << "Done!" << std::endl;
            continue;
        }

        // Multicast admin message to all sessions
        line = "(admin) " + line;
        server->Multicast(line);
    }

    // Stop the server
    std::cout << "Server stopping...";
    server->Stop();
    std::cout << "Done!" << std::endl;

    // Stop the Asio service
    std::cout << "Asio service stopping...";
    service->Stop();
    std::cout << "Done!" << std::endl;

    return 0;
}
