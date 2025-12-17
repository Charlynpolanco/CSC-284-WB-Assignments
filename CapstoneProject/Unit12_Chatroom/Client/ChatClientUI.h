#ifndef CHATCLIENTUI_H
#define CHATCLIENTUI_H

#include "MessageArea.h"
#include "RoomList.h"
#include "InputArea.h"

class ChatClientUI {
public:
    ChatClientUI(int serverSock);
    ~ChatClientUI();

    void run();

private:
    void drawHeader();

    MessageArea* messageArea;
    RoomList* roomList;
    InputArea* inputArea;
    int sock;

    int h, w;
    int topBarHeight;
    int roomPanelWidth;
    int messagePanelWidth;
};

#endif