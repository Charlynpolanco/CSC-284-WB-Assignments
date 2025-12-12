#ifndef MESSAGEAREA_H
#define MESSAGEAREA_H

#include "WindowBase.h"
#include <string>
#include <vector>

class MessageArea : public WindowBase {
public:
    MessageArea(int y, int x, int h, int w, int color_pair);
    ~MessageArea() override;

    void addMessage(const std::string& msg);
    void draw(bool focused = false) override;

private:
    int color;
    std::vector<std::string> history;
};

#endif // MESSAGEAREA_H