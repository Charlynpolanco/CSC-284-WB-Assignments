#ifndef ROOMLIST_H
#define ROOMLIST_H

#include "WindowBase.h"
#include <string>
#include <vector>

class RoomList : public WindowBase {
public:
    RoomList(int y, int x, int h, int w, int color_pair);
    ~RoomList() override;

    void setRooms(const std::vector<std::string>& r);
    void draw(bool focused = false) override;

    void moveUp();
    void moveDown();
    int getSelected() const;
    std::string getSelectedName() const;

private:
    int color;
    std::vector<std::string> rooms;
    int selected;
    int scroll;
};


#endif
