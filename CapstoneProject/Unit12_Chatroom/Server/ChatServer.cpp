#include "ChatServer.h"
#include <iostream>
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
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#endif

// -------------------- helpers --------------------
static void trim(std::string& s) {
    s.erase(s.find_last_not_of(" \r\n\t") + 1);
    s.erase(0, s.find_first_not_of(" \r\n\t"));
}

// -------------------- ctor / dtor --------------------
ChatServer::ChatServer(const std::string& ip, int port)
    : listeningSocket(INVALID_SOCKET), anonCounter(1)
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        exit(1);
    }
#endif

    listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Cannot create socket.\n";
        exit(1);
    }

    sockaddr_in serverHint{};
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(port);

#ifdef _WIN32
    InetPtonA(AF_INET, ip.c_str(), &serverHint.sin_addr);
#else
    inet_pton(AF_INET, ip.c_str(), &serverHint.sin_addr);
#endif

    if (bind(listeningSocket, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR) {
        std::cerr << "Bind failed.\n";
        exit(1);
    }

    if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed.\n";
        exit(1);
    }

    // Create default Lobby
    rooms.push_back(new Room("Lobby"));

    std::cout << "Server listening on " << ip << ":" << port << "\n";
}

ChatServer::~ChatServer() {
    for (auto u : users) delete u;
    for (auto r : rooms) delete r;

    closesocket(listeningSocket);
#ifdef _WIN32
    WSACleanup();
#endif
}

// -------------------- helpers --------------------
bool ChatServer::isUsernameTaken(const std::string& name) {
    for (auto u : users) {
        if (u->getUsername() == name) return true;
    }
    return false;
}

Room* ChatServer::getRoomByName(const std::string& name) {
    for (auto r : rooms) {
        if (r->getName() == name) return r;
    }
    return nullptr;
}

User* ChatServer::createUser(int clientSocket) {
    std::lock_guard<std::mutex> lock(usersMutex);

    std::string username;
    do {
        username = "anon" + std::to_string(anonCounter++);
    } while (isUsernameTaken(username));

    User* user = new User(clientSocket, username);

    Room* lobby = getRoomByName("Lobby");
    lobby->addUser(user);
    user->setRoom(lobby);

    users.push_back(user);
    return user;
}

// -------------------- server loop --------------------
void ChatServer::run() {
    while (true) {
        sockaddr_in clientAddr{};
        int addrSize = sizeof(clientAddr);

        int clientSocket = accept(listeningSocket, (sockaddr*)&clientAddr, &addrSize);
        if (clientSocket == INVALID_SOCKET) continue;

        User* newUser = createUser(clientSocket);
        std::thread(&ChatServer::handleClient, this, newUser).detach();
    }
}

// -------------------- command handling --------------------
void ChatServer::handleCommand(User* user, const std::string& msg) {
    if (msg.find(".CREATE_ROOM ") == 0) {
        std::string roomName = msg.substr(13);
        trim(roomName);
        if (!roomName.empty() && !getRoomByName(roomName)) {
            Room* newRoom = new Room(roomName);
            std::lock_guard<std::mutex> lock(roomsMutex);
            rooms.push_back(newRoom);
            std::string reply = "Room created: " + roomName + "\n";
            send(user->getSocket(), reply.c_str(), reply.size(), 0);
        }
    }
    else if (msg.find(".LIST_ROOMS") == 0) {
        std::string roomList = "Rooms:\n";
        {
            std::lock_guard<std::mutex> lock(roomsMutex);
            for (auto r : rooms) roomList += "- " + r->getName() + "\n";
        }
        send(user->getSocket(), roomList.c_str(), roomList.size(), 0);
    }
    else if (msg.find(".JOIN_ROOM ") == 0) {
    std::string roomName = msg.substr(11);
    trim(roomName);

    if (roomName.empty()) {
        send(user->getSocket(), "Room name cannot be empty.\n", 27, 0);
        return;
    }

    Room* targetRoom = getRoomByName(roomName);
    if (!targetRoom) {
        std::string notExist = "Room does not exist: " + roomName + "\n";
        send(user->getSocket(), notExist.c_str(), notExist.size(), 0);
        return;
    }

    Room* currentRoom = user->getRoom();
    if (currentRoom == targetRoom) {
        send(user->getSocket(), "You are already in that room.\n", 30, 0);
        return;
    }

    // Remove user from current room
    if (currentRoom) {
        currentRoom->removeUser(user);
        broadcastToRoom(currentRoom, user->getUsername() + " has left the room.\n");
    }

    // Add user to new room
    targetRoom->addUser(user);
    user->setRoom(targetRoom);
    broadcastToRoom(targetRoom, user->getUsername() + " has joined the room.\n");

    std::string confirm = "You have joined room: " + roomName + "\n";
    send(user->getSocket(), confirm.c_str(), confirm.size(), 0);
}
}

// -------------------- broadcast --------------------
void ChatServer::broadcastToRoom(Room* room, const std::string& msg) {
    std::lock_guard<std::mutex> lock(usersMutex);
    for (auto u : room->getUsers()) {
        send(u->getSocket(), msg.c_str(), msg.size(), 0);
    }
}

// -------------------- client handler --------------------
void ChatServer::handleClient(User* user) {
    char buffer[4096];
    bool usernameSet = false;

    // Get the Lobby (already created in server constructor)
    Room* lobby = getRoomByName("Lobby");
    if (!lobby) {
        // fallback: create if somehow missing
        lobby = new Room("Lobby");
        std::lock_guard<std::mutex> lock(roomsMutex);
        rooms.push_back(lobby);
    }

    // Ensure the user is only added once (createUser() already added them)
    user->setRoom(lobby);

    // Welcome message only to this user
    std::string welcome = "Welcome! Your first input will be your username.\n";
    send(user->getSocket(), welcome.c_str(), welcome.size(), 0);

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(user->getSocket(), buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';
        std::string msg(buffer);
        trim(msg);
        if (msg.empty()) continue;

        // --- First message = username ---
        if (!usernameSet) {
            if (!isUsernameTaken(msg)) {
                user->setUsername(msg);
            }
            usernameSet = true;

            // Broadcast join message to everyone in the room
            std::string joinMsg = user->getUsername() + " has joined the Lobby.\n";
            broadcastToRoom(lobby, joinMsg); // exclude sender from duplicate self-message

            // Send confirmation to this user
            std::string selfMsg = "You are now known as " + user->getUsername() + "\n";
            send(user->getSocket(), selfMsg.c_str(), selfMsg.size(), 0);

            continue; // do NOT treat first message as chat
        }

        // --- Commands ---
        if (msg[0] == '.') {
            handleCommand(user, msg);
            continue;
        }

        // --- Normal chat message ---
        Room* currentRoom = user->getRoom();
        if (currentRoom) {
            std::string fullMsg = user->getUsername() + ": " + msg + "\n";
            broadcastToRoom(currentRoom, fullMsg); // send to all including sender
            std::cout << fullMsg; // server log
        }
    }

    // --- User disconnect ---
    Room* currentRoom = user->getRoom();
    if (currentRoom) {
        currentRoom->removeUser(user);
        std::string leaveMsg = user->getUsername() + " has left the room.\n";
        broadcastToRoom(currentRoom, leaveMsg);
    }

    closesocket(user->getSocket());
    {
        std::lock_guard<std::mutex> lock(usersMutex);
        users.erase(std::remove(users.begin(), users.end(), user), users.end());
    }
    delete user;
    std::cout << "User disconnected. Active users: " << users.size() << "\n";
}