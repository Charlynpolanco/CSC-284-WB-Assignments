#include "WindowBase.h"
#include <stdexcept>

WindowBase::WindowBase(int y, int x, int h, int w)
    : startY(y), startX(x), height(h), width(w) {
    win = newwin(height, width, startY, startX);
    if (!win) throw std::runtime_error("Failed to create window");
    keypad(win, TRUE);
}

WindowBase::~WindowBase() {
    if (win) {
        delwin(win);
        win = nullptr;
    }
}