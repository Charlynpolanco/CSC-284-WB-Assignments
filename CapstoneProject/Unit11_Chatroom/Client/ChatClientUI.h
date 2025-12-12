#ifndef CHATCLIENTUI_H
#define CHATCLIENTUI_H

#include "MessageArea.h"
#include "RoomList.h"
#include "InputArea.h"
#include <mutex>

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

    int h, w;
    int topBarHeight;
    int roomPanelWidth;
    int messagePanelWidth;

    int sock;               // server socket
    std::mutex uiMutex;     // mutex for thread-safe UI updates
};

#endif // CHATCLIENTUI_H