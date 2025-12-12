#ifndef CHATCLIENTUI_H
#define CHATCLIENTUI_H

#include "MessageArea.h"
#include "RoomList.h"
#include "InputArea.h"
#include <curses.h>

class ChatClientUI {
public:
    ChatClientUI();
    ~ChatClientUI();

    void run();

private:
    void drawHeader();

    MessageArea* messageArea;
    RoomList* roomList;
    InputArea* inputArea;

    int h, w;
    int topBarHeight;
    int roomPanelWidth;
    int messagePanelWidth;
};

#endif
