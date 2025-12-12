#include "ChatClientUI.h"
#include "Network.h"
#include <iostream>
#include <thread>
#include <string>
//constructor
ChatClientUI::ChatClientUI(int serverSock)
    : sock(serverSock), messageArea(nullptr), roomList(nullptr), inputArea(nullptr),
    h(0), w(0), topBarHeight(2), roomPanelWidth(22), messagePanelWidth(0) {

    initscr();
    noecho();
    cbreak();
    curs_set(1);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
    }

    getmaxyx(stdscr, h, w);

    if (h < 15 || w < 60) {
        endwin();
        std::cerr << "ERROR: Console too small. Minimum 60x15.\n";
        std::exit(1);
    }

    messagePanelWidth = w - roomPanelWidth;

    messageArea = new MessageArea(topBarHeight, 0, h - topBarHeight - 3, messagePanelWidth, 3);
    roomList = new RoomList(topBarHeight, messagePanelWidth, h - topBarHeight - 1, roomPanelWidth, 3);
    inputArea = new InputArea(h - 3, 0, 3, messagePanelWidth, 3);

    //Welcome messages and rooms
    roomList->setRooms({ "General", "Sports", "Programming", "Music", "Random", "ExtraRoom" });
    messageArea->addMessage("Welcome to the chat!");
    messageArea->addMessage("Press TAB to toggle focus between input and room list.");
    messageArea->addMessage("Press ESC to exit the program.");
}
//destructor
ChatClientUI::~ChatClientUI() {
    delete messageArea;
    delete roomList;
    delete inputArea;
    endwin();
}
//draws the title of the chat room and gives it attributes
void ChatClientUI::drawHeader() {
    attron(COLOR_PAIR(3));
    mvhline(1, 0, 0, w);
    attroff(COLOR_PAIR(3));
    mvprintw(0, 2, " Charly's Chat Room.");
    refresh();
}

void ChatClientUI::run() {
    drawHeader();
    messageArea->draw();
    roomList->draw();
    inputArea->draw(true);

    //Background thread to receive messages from server
    std::thread receiver([this]() {
        char buffer[4096];
        while (true) {
            int bytes = receiveMessage(sock, buffer, 4096);
            if (bytes <= 0) break;
            messageArea->addMessage(std::string(buffer, bytes));
            messageArea->draw();
        }
        });
    receiver.detach();
    //sets the key value for exiting and focus changing between the chat bar and the room selection.
    enum Focus { INPUT, ROOM };
    Focus focus = INPUT;

    bool running = true;
    while (running) {
        int ch;
        if (focus == INPUT) ch = wgetch(inputArea->winHandle());
        else ch = wgetch(roomList->winHandle());
        //ESC
        if (ch == 27) { 
            running = false;
            break;
        }

        if (ch == '\t') { //TAB toggles focus
            focus = (focus == INPUT) ? ROOM : INPUT;
            roomList->draw();
            inputArea->draw(focus == INPUT);
            continue;
        }

        if (focus == INPUT) {
            std::string out;
            bool sent = inputArea->handleKey(ch, out);
            inputArea->draw(true);

            if (sent && !out.empty()) {
                //send to server
                int bytesSent = sendMessage(sock, out);
                if (bytesSent > 0) {
                    //show immediately in your own UI
                    messageArea->addMessage("You: " + out);
                    messageArea->draw();
                }
                else {
                    messageArea->addMessage("Error: Could not send message");
                    messageArea->draw();
                }
            }
        }
        else { //ROOM focus
            if (ch == KEY_UP) {
                roomList->moveUp();
                roomList->draw();
            }
            else if (ch == KEY_DOWN) {
                roomList->moveDown();
                roomList->draw();
            }
            else if (ch == '\n') {
                std::lock_guard<std::mutex> lock(uiMutex);
                messageArea->addMessage("Switched to room: " + roomList->getSelectedName());
                messageArea->draw();
            }
            inputArea->draw(false);
        }
    }

}
