#ifndef INPUTAREA_H
#define INPUTAREA_H

#include "WindowBase.h"
#include <string>

class InputArea : public WindowBase {
public:
    InputArea(int y, int x, int h, int w, int color_pair);
    ~InputArea() override;

    //handle a key; returns true if Enter pressed and outMsg filled
    bool handleKey(int ch, std::string& outMsg);
    void draw(bool focused) override;

private:
    int color;
    std::string buffer;
    size_t cursorPos;
    size_t scrollOffset;
};


#endif
