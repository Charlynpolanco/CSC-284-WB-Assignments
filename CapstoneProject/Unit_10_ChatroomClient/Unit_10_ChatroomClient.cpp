#include <curses.h>
#include <string>

int main() {
 
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    //Enable color
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_YELLOW, COLOR_BLACK);   //message text
        init_pair(2, COLOR_CYAN, COLOR_BLACK);     //menu items
        init_pair(3, COLOR_WHITE, COLOR_BLACK);    //borders
    }

    //Get terminal size
    int h, w;
    getmaxyx(stdscr, h, w);

   //size
    if (h < 30 || w < 90) {
        endwin();
        printf("ERROR: Console too small. Make it at least 100x35.\n");
        return 1;
    }

    //Layout
    
    int topBarHeight = 2;
    int borderThickness = 1;
    int roomPanelWidth = 25;
    int messagePanelWidth = w - roomPanelWidth;

    //Draw top bar
    attron(COLOR_PAIR(3));
    mvhline(1, 0, 0, w);
    attroff(COLOR_PAIR(3));
    mvprintw(0, 2, " Chat Application ");
    refresh();

    
    //Create windows
    WINDOW* messageWin = newwin(
        h - topBarHeight,
        messagePanelWidth,
        topBarHeight,
        0
    );

    WINDOW* roomWin = newwin(
        h - topBarHeight,
        roomPanelWidth,
        topBarHeight,
        messagePanelWidth
    );

    
    //Check window creation
    
    if (!messageWin || !roomWin) {
        endwin();
        printf("ERROR: Failed to create subwindows.\n");
        return 1;
    }

    //Draw borders
 
    wattron(messageWin, COLOR_PAIR(3));
    box(messageWin, 0, 0);
    wattroff(messageWin, COLOR_PAIR(3));

    wattron(roomWin, COLOR_PAIR(3));
    box(roomWin, 0, 0);
    wattroff(roomWin, COLOR_PAIR(3));

    wrefresh(messageWin);
    wrefresh(roomWin);

    
//intro messages
    
    wattron(messageWin, COLOR_PAIR(1));
    mvwprintw(messageWin, 1, 2, "Welcome to the chat!");
    mvwprintw(messageWin, 2, 2, "This is a placeholder message.");
    mvwprintw(messageWin, 3, 2, "More messages will appear here later.");
    wattroff(messageWin, COLOR_PAIR(1));

    wrefresh(messageWin);

  
//room list

    const char* rooms[] = { "General", "Sports", "Programming", "Music", "Random" };
    const int roomCount = 5;

    int selectedIndex = 0;

    auto drawRoomList = [&](int highlight) {
        werase(roomWin);
        wattron(roomWin, COLOR_PAIR(3));
        box(roomWin, 0, 0);
        wattroff(roomWin, COLOR_PAIR(3));

        for (int i = 0; i < roomCount; i++) {
            if (i == highlight) {
                wattron(roomWin, COLOR_PAIR(2) | A_REVERSE | A_BOLD);
                mvwprintw(roomWin, 1 + i, 2, rooms[i]);
                wattroff(roomWin, COLOR_PAIR(2) | A_REVERSE | A_BOLD);
            }
            else {
                wattron(roomWin, COLOR_PAIR(2));
                mvwprintw(roomWin, 1 + i, 2, rooms[i]);
                wattroff(roomWin, COLOR_PAIR(2));
            }
        }

        wrefresh(roomWin);
        };

    drawRoomList(selectedIndex);   

    //Input loop for navigation
   
    keypad(stdscr, TRUE);
    keypad(roomWin, TRUE);

    int ch;
    while ((ch = getch()) != 'q') {   // press 'q' to exit
        switch (ch) {
        case KEY_UP:
            if (selectedIndex > 0)
                selectedIndex--;
            break;

        case KEY_DOWN:
            if (selectedIndex < roomCount - 1)
                selectedIndex++;
            break;
        }

        drawRoomList(selectedIndex);
    }

    endwin();
    return 0;
}
