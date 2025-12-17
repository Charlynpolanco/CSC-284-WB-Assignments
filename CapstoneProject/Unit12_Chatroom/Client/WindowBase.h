#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <curses.h>

class WindowBase {
public:
    WindowBase(int y, int x, int h, int w);
    virtual ~WindowBase();

    virtual void draw(bool focused = false) = 0;
    WINDOW* winHandle() const { return win; }

protected:
    WINDOW* win;
    int startY, startX, height, width;
};

#endif // WINDOWBASE_H