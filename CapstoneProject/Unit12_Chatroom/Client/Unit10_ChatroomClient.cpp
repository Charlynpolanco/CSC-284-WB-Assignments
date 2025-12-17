#include "ChatClientUI.h"
#include "Network.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string ip = "127.0.0.1";
    int port = 54000;

    if (argc >= 2) ip = argv[1];
    if (argc >= 3) port = std::stoi(argv[2]);

    int sock = connectToServer(ip, port);
    if (sock < 0) {
        std::cerr << "Could not connect to server.\n";
        return 1;
    }

    ChatClientUI ui(sock);
    ui.run();

    shutdownNetworking();
    return 0;
}