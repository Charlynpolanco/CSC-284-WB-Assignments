#include "User.h"
#include "Room.h"

User::User(int socketFd, const std::string& name)
    : socket(socketFd), username(name), currentRoom(nullptr) {
}

int User::getSocket() const {
    return socket;
}

std::string User::getUsername() const {
    return username;
}

void User::setUsername(const std::string& name) {
    username = name;
}

void User::setRoom(Room* r) {
    currentRoom = r;
}

Room* User::getRoom() const {
    return currentRoom;
}