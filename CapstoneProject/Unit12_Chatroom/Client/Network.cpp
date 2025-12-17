#include "Network.h"
#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif

int connectToServer(const std::string& ip, int port) {
#ifdef _WIN32
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
#endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    sockaddr_in serverHint{};
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverHint.sin_addr);

    if (connect(sock, (sockaddr*)&serverHint, sizeof(serverHint)) < 0)
        return -1;

    return sock;
}

int sendMessage(int sock, const std::string& msg) {
    return send(sock, msg.c_str(), msg.size(), 0);
}

int receiveMessage(int sock, char* buffer, int bufferSize) {
    memset(buffer, 0, bufferSize);
    return recv(sock, buffer, bufferSize, 0);
}

void shutdownNetworking() {
#ifdef _WIN32
    WSACleanup();
#endif
}