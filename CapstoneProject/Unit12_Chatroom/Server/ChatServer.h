#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "User.h"
#include "Room.h"

#ifdef _WIN32
#include <winsock2.h>
#else
using SOCKET = int;
#endif

class ChatServer {
public:
    ChatServer(const std::string& ip, int port);
    ~ChatServer();

    void run();
    void handleClient(User* user);

private:
    SOCKET listeningSocket;           // <--- make sure this is declared
    std::vector<User*> users;
    std::vector<Room*> rooms;
    std::mutex usersMutex;
    std::mutex roomsMutex;
    int anonCounter;

    // Helpers
    bool isUsernameTaken(const std::string& name);
    Room* getRoomByName(const std::string& name);
    User* createUser(int clientSocket);

    // Commands
    void handleCommand(User* user, const std::string& msg);

    // Messaging
    void broadcastToRoom(Room* room, const std::string& msg);
};