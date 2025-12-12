#include "InputArea.h"
#include <curses.h>

//constructor
InputArea::InputArea(int y, int x, int h, int w, int color_pair)
    : WindowBase(y, x, h, w), color(color_pair),
      buffer(), cursorPos(0), scrollOffset(0)
{
}
//destructor
InputArea::~InputArea() 
{
}

//handles letter inputs and direction inputs and correctly positions the cursor in the right spot.
bool InputArea::handleKey(int ch, std::string& outMsg)
{
    if (ch == KEY_LEFT) {
        if (cursorPos > 0)
            cursorPos--;
    } else if (ch == KEY_RIGHT) {
        if (cursorPos < buffer.size())
            cursorPos++;
    } else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
        if (cursorPos > 0) {
            buffer.erase(buffer.begin() + cursorPos - 1);
            cursorPos--;
        }
    } else if (ch == KEY_DC) {
        if (cursorPos < buffer.size())
            buffer.erase(buffer.begin() + cursorPos);
    } else if (ch == '\n') {
        outMsg = buffer;
        buffer.clear();
        cursorPos = 0;
        scrollOffset = 0;
        return true;
    } else if (ch >= 32 && ch <= 126) { // printable characters
        buffer.insert(buffer.begin() + cursorPos, (char)ch);
        cursorPos++;
    }

    return false;
}
//creates the box where the user types messages and clears anything when it's called
void InputArea::draw(bool focused)
{
    werase(win);
    wattron(win, COLOR_PAIR(color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(color));

    int maxY, maxX;
    getmaxyx(win, maxY, maxX);
    int visibleWidth = maxX - 4;

    //Adjust scroll to keep cursor visible
    if (cursorPos < scrollOffset)
        scrollOffset = cursorPos;
    else if (cursorPos >= scrollOffset + visibleWidth)
        scrollOffset = cursorPos - visibleWidth + 1;

    std::string visible = "";
    if (scrollOffset < buffer.size())
        visible = buffer.substr(scrollOffset, visibleWidth);

    mvwprintw(win, 1, 2, "%s", visible.c_str());

    //Set cursor if focused
    if (focused) {
        int cx = 2 + (int)cursorPos - (int)scrollOffset;
        if (cx < 1) cx = 1;
        int maxCx = maxX - 2;
        if (cx >= maxCx) cx = maxCx - 1;
        wmove(win, 1, cx);
        curs_set(1);
    } else {
        curs_set(0);
    }

    wrefresh(win);
}
