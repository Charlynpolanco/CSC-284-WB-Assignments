#include "RoomList.h"

RoomList::RoomList(int y, int x, int h, int w, int color_pair)
    : WindowBase(y, x, h, w), color(color_pair), selected(0), scroll(0) {
}

RoomList::~RoomList() {}

void RoomList::setRooms(const std::vector<std::string>& r) {
    rooms = r;
    selected = 0;
    scroll = 0;
}

void RoomList::draw(bool) {
    werase(win);
    wattron(win, COLOR_PAIR(color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(color));

    int maxY, maxX;
    getmaxyx(win, maxY, maxX);
    int visibleLines = maxY - 2;

    if (selected < scroll) scroll = selected;
    else if (selected >= scroll + visibleLines) scroll = selected - visibleLines + 1;

    for (int i = 0; i < (int)rooms.size(); ++i) {
        if (i < scroll || i >= scroll + visibleLines) continue;
        int y = 1 + (i - scroll);
        if (i == selected) {
            wattron(win, COLOR_PAIR(2) | A_REVERSE | A_BOLD);
            mvwprintw(win, y, 2, "%s", rooms[i].c_str());
            wattroff(win, COLOR_PAIR(2) | A_REVERSE | A_BOLD);
        }
        else {
            wattron(win, COLOR_PAIR(2));
            mvwprintw(win, y, 2, "%s", rooms[i].c_str());
            wattroff(win, COLOR_PAIR(2));
        }
    }

    wrefresh(win);
}

void RoomList::moveUp() {
    if (selected > 0) selected--;
}

void RoomList::moveDown() {
    if (selected < (int)rooms.size() - 1) selected++;
}

int RoomList::getSelected() const { return selected; }

std::string RoomList::getSelectedName() const {
    if (rooms.empty()) return "";
    return rooms[selected];
}