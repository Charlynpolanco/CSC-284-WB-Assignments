#include "WindowBase.h"
#include <stdexcept>
#include <curses.h>
//constructor
WindowBase::WindowBase(int y, int x, int h, int w)
    : startY(y), startX(x), height(h), width(w)
{
  //creates the curses window
    win = newwin(height, width, startY, startX);
    if (!win)
        throw std::runtime_error("Failed to create window");
  //Enable function keys (arrows, etc.)
    keypad(win, TRUE); 
}
//destructor
WindowBase::~WindowBase()
{
    if (win) {
        delwin(win);
        win = nullptr;
    }
}
