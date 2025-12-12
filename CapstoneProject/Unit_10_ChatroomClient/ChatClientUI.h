#include "ChatClientUI.h"
#include <iostream>
//constructor
ChatClientUI::ChatClientUI()
    : messageArea(nullptr), roomList(nullptr), inputArea(nullptr),
      h(0), w(0), topBarHeight(2), roomPanelWidth(22), messagePanelWidth(0)
{
  //ncurses start
    initscr();
    noecho();
    cbreak();
    curs_set(1);
  //colors
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
    }
  //checks the size for the console
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

    //intro text
    roomList->setRooms({ "General", "Sports", "Programming", "Music", "Random", "ExtraRoom" });
    messageArea->addMessage("Welcome to the chat!");
    messageArea->addMessage("Press TAB to toggle focus between input and room list.");
    messageArea->addMessage("Press ESC to exit the program.");
}
//destructor
ChatClientUI::~ChatClientUI()
{
    delete messageArea;
    delete roomList;
    delete inputArea;
    endwin();
}

void ChatClientUI::drawHeader()
{
    attron(COLOR_PAIR(3));
    mvhline(1, 0, 0, w);
    attroff(COLOR_PAIR(3));
    mvprintw(0, 2, " Advanced C++ Chat Client ");
    refresh();
}

void ChatClientUI::run()
{
    drawHeader();
    messageArea->draw();
    roomList->draw();
    inputArea->draw(true);

    enum Focus { INPUT, ROOM };
    Focus focus = INPUT;
    bool running = true;

    while (running) {
        int ch;

        //choose where the focus is (chat bar or room selection)
        if (focus == INPUT)
            ch = wgetch(inputArea->winHandle());
        else
            ch = wgetch(roomList->winHandle());

        if (ch == 27) { // ESC
            running = false;
            break;
        }

        if (ch == '\t') { // TAB toggles focus
            focus = (focus == INPUT) ? ROOM : INPUT;
            roomList->draw();
            inputArea->draw(focus == INPUT);
            continue;
        }
        //adds your message to the chat box
        if (focus == INPUT) {
            std::string out;
            bool sent = inputArea->handleKey(ch, out);
            inputArea->draw(true);
            if (sent && !out.empty()) {
                messageArea->addMessage(out);
                messageArea->draw();
            }
        } else { //ROOM focus controls
            if (ch == KEY_UP) {
                roomList->moveUp();
                roomList->draw();
            } else if (ch == KEY_DOWN) {
                roomList->moveDown();
                roomList->draw();
            }
            //when the user presses enter on a room it displays "Switched to room ..." message but does not do anything other than that.
            else if (ch == '\n') {
                messageArea->addMessage(std::string("Switched to room: ") + roomList->getSelectedName());
                messageArea->draw();
            }
            inputArea->draw(false);
        }
    }
}
