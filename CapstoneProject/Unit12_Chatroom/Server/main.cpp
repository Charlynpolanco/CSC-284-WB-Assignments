#include "ChatServer.h"

int main() {
    ChatServer server("127.0.0.1", 54000);
    server.run();
    return 0;
}