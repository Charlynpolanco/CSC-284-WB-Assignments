#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
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

std::vector<int> clients;
std::mutex clientsMutex;

void handleClient(int clientSocket) {
    char buffer[4096];

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) break;

        //Broadcast to all other clients
        std::lock_guard<std::mutex> lock(clientsMutex);
        for (int c : clients) {
            if (c != clientSocket) {
                send(c, buffer, bytesReceived, 0);
            }
        }
    }

    //Remove client when disconnected
    closesocket(clientSocket);
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
    }
    //prints out the number of active clients left
    std::cout << "Client disconnected. Active clients: " << clients.size() << "\n";
}

int main(int argc, char* argv[]) {
#ifdef _WIN32
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    std::string ip = "127.0.0.1";
    int port = 54000;

    if (argc >= 2) ip = argv[1];
    if (argc >= 3) port = std::stoi(argv[2]);

    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening < 0) {
        std::cerr << "Cannot create socket\n";
        return 1;
    }

    sockaddr_in hint{};
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(listening, SOMAXCONN) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server listening on " << ip << ":" << port << "\n";

    while (true) {
        sockaddr_in client{};
        socklen_t clientSize = sizeof(client);
        int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
        if (clientSocket < 0) {
            std::cerr << "Accept failed\n";
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            clients.push_back(clientSocket);
        }

        std::cout << "New client connected. Active clients: " << clients.size() << "\n";

        std::thread(handleClient, clientSocket).detach();
    }
    
    closesocket(listening);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
