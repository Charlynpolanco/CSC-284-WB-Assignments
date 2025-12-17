#ifndef USER_H
#define USER_H

#include <string>

class Room; // forward declaration

class User {
public:
    User(int socketFd, const std::string& name);

    int getSocket() const;
    std::string getUsername() const;
    void setUsername(const std::string& name);

    void setRoom(Room* r);
    Room* getRoom() const;

private:
    int socket;
    std::string username;
    Room* currentRoom;
};

#endif