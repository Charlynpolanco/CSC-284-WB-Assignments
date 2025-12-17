#include "Room.h"
#include "User.h"
#include <algorithm>

Room::Room(const std::string& name)
    : roomName(name) {
}

std::string Room::getName() const {
    return roomName;
}

void Room::addUser(User* user) {
    users.push_back(user);
}

void Room::removeUser(User* user) {
    users.erase(std::remove(users.begin(), users.end(), user), users.end());
}

std::vector<User*> Room::getUsers() const {
    return users;
}