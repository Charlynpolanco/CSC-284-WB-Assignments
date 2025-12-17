#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

class User; // forward declaration

class Room {
public:
    Room(const std::string& name);

    std::string getName() const;

    void addUser(User* user);
    void removeUser(User* user);
    std::vector<User*> getUsers() const;

private:
    std::string roomName;
    std::vector<User*> users;
};

#endif