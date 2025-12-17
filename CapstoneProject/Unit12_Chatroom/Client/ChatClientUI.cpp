#include "ChatClientUI.h"
#include "Network.h"
#include <iostream>
#include <thread>
#include <mutex>

ChatClientUI::ChatClientUI(int serverSock)
    : sock(serverSock), messageArea(nullptr), roomList(nullptr), inputArea(nullptr),
    h(0), w(0), topBarHeight(2), roomPanelWidth(22), messagePanelWidth(0)
{
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
        std::cerr << "Console too small. Minimum 60x15.\n";
        exit(1);
    }

    messagePanelWidth = w - roomPanelWidth;

    messageArea = new MessageArea(topBarHeight, 0, h - topBarHeight - 3, messagePanelWidth, 3);
    roomList = new RoomList(topBarHeight, messagePanelWidth, h - topBarHeight - 1, roomPanelWidth, 3);
    inputArea = new InputArea(h - 3, 0, 3, messagePanelWidth, 3);

    // Sample rooms
    roomList->setRooms({ "General", "Sports", "Programming" });

    messageArea->addMessage("Welcome to the chat!");
    messageArea->addMessage("Press TAB to toggle focus between input and room list.");
    messageArea->addMessage("Press ESC to exit the program or type .EXIT");
}

ChatClientUI::~ChatClientUI() {
    delete messageArea;
    delete roomList;
    delete inputArea;
    endwin();
}

void ChatClientUI::drawHeader() {
    attron(COLOR_PAIR(3));
    mvhline(1, 0, 0, w);
    attroff(COLOR_PAIR(3));
    mvprintw(0, 2, " Advanced C++ Chat Client ");
    refresh();
}

void ChatClientUI::run() {
    drawHeader();
    messageArea->draw();
    roomList->draw();
    inputArea->draw(true);

    std::mutex uiMutex;

    // --- Background thread to receive messages ---
    // --- Background thread to receive messages ---
    std::thread receiver([this, &uiMutex]() {
        char buffer[4096];
        std::string leftover;

        while (true) {
            int bytes = receiveMessage(sock, buffer, 4096);
            if (bytes <= 0) break;

            std::string received(buffer, bytes);
            received = leftover + received; // prepend leftover from last recv
            leftover.clear();

            size_t pos = 0;
            while (true) {
                size_t newlinePos = received.find('\n', pos);
                if (newlinePos == std::string::npos) {
                    leftover = received.substr(pos); // save partial line
                    break;
                }

                std::string line = received.substr(pos, newlinePos - pos);
                pos = newlinePos + 1;

                // Trim carriage return (Windows)
                if (!line.empty() && line.back() == '\r') line.pop_back();

                // Add line even if empty, to preserve newlines
                {
                    std::lock_guard<std::mutex> lock(uiMutex);
                    messageArea->addMessage(line);
                    messageArea->draw();
                }
            }
        }
        });
    receiver.detach();

    enum Focus { INPUT, ROOM };
    Focus focus = INPUT;
    bool running = true;

    while (running) {
        int ch = (focus == INPUT) ? wgetch(inputArea->winHandle()) : wgetch(roomList->winHandle());

        if (ch == 27) { running = false; break; } // ESC
        if (ch == '\t') { // TAB toggle
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
                if (out == ".EXIT") {
                    running = false;  // stop the main loop
                    break;            // exit immediately
                }
                sendMessage(sock, out + "\n"); // send normal messages
            }
        }
        else {
            // Room list navigation
            if (ch == KEY_UP) { roomList->moveUp(); roomList->draw(); }
            else if (ch == KEY_DOWN) { roomList->moveDown(); roomList->draw(); }
            else if (ch == '\n') {
                messageArea->addMessage("Switched to room: " + roomList->getSelectedName());
                messageArea->draw();
            }
            inputArea->draw(false);
        }
    }
}