#include "ChatClientUI.h"
#include "Network.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Default IP and port
    std::string serverIP = "127.0.0.1";
    int serverPort = 54000;

    // Override with command-line arguments if provided
    if (argc >= 2) serverIP = argv[1];
    if (argc >= 3) serverPort = std::stoi(argv[2]);

    int sock = connectToServer(serverIP, serverPort);
    if (sock < 0) {
        std::cerr << "Could not connect to server at "
            << serverIP << ":" << serverPort << std::endl;
        return 1;
    }

    ChatClientUI ui(sock);
    ui.run();

    shutdownNetworking(); // cleanup Winsock if on Windows
    return 0;
}