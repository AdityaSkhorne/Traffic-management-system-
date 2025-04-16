#include "network.h"
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


bool Network::startServer(int port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) return false;

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) return false;
    if (listen(sockfd, 1) < 0) return false;

    std::cout << "Server listening on port " << port << "...\n";
    clientSock = accept(sockfd, nullptr, nullptr);
    return clientSock != -1;
}

bool Network::connectToPeer(const std::string& ip, int port) {
    clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock == -1) return false;

    sockaddr_in peerAddr{};
    peerAddr.sin_family = AF_INET;
    peerAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &peerAddr.sin_addr);

    return connect(clientSock, (sockaddr*)&peerAddr, sizeof(peerAddr)) != -1;
}

bool Network::sendMessage(const std::string& message) {
    return send(clientSock, message.c_str(), message.size(), 0) != -1;
}

std::string Network::receiveMessage() {
    char buffer[1024] = {0};
    ssize_t bytes = recv(clientSock, buffer, sizeof(buffer), 0);
    return bytes > 0 ? std::string(buffer, bytes) : "";
}
