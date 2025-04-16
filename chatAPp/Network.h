#ifndef NETWORK_H
#define NETWORK_H

#include <string>

class Network {
public:
    bool startServer(int port);
    bool connectToPeer(const std::string& ip, int port);
    bool sendMessage(const std::string& message);
    std::string receiveMessage();

private:
    int sockfd;
    int clientSock;
};

#endif
