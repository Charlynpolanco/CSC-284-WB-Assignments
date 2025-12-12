#include "MessageArea.h"
#include <algorithm>
//constructor
MessageArea::MessageArea(int y, int x, int h, int w, int color_pair)
    : WindowBase(y, x, h, w), color(color_pair) {
}
//destructor
MessageArea::~MessageArea() {}
//adds new messages to the history of the chat
void MessageArea::addMessage(const std::string& msg) {
    history.push_back(msg);
}

void MessageArea::draw(bool){
    werase(win);
    wattron(win, COLOR_PAIR(color));
    box(win, 0, 0);
    wattroff(win, COLOR_PAIR(color));

    int maxY, maxX;
    getmaxyx(win, maxY, maxX);
    int availableLines = maxY - 2;
    std::vector<std::string> wrapped;
 //Wrap each message to fit the window width
    for (const auto& msg : history) {
        size_t start = 0;
        int maxWidth = maxX - 4;
        
        while (start < msg.size()) {
            size_t len = std::min((size_t)maxWidth, msg.size() - start);
            size_t end = start + len;
             //Avoid splitting words in the middle
            if (end < msg.size() && msg[end] != ' ') {
                size_t lastSpace = msg.rfind(' ', end - 1);
                if (lastSpace != std::string::npos && lastSpace >= start) {
                    end = lastSpace;
                }
            }
            
            std::string line = msg.substr(start, end - start);
            
            //Trim spaces at start and end
            while (!line.empty() && line.front() == ' ') line.erase(0, 1);
            while (!line.empty() && line.back() == ' ') line.pop_back();
             
             //If trimming removed everything, force take a slice
            if (line.empty() && end < msg.size()) {
               
                line = msg.substr(start, std::min((size_t)maxWidth, msg.size() - start));
                start += line.size();
            }
            else {
                start = end;
            }
    
            wrapped.push_back(line);
            while (start < msg.size() && msg[start] == ' ') start++;
        }
    }
    //Determine starting line to display
    int startIndex = 0;
    if ((int)wrapped.size() > availableLines) startIndex = (int)wrapped.size() - availableLines;
    //Print wrapped lines in the window
    int lineNo = 1;
    for (int i = startIndex; i < (int)wrapped.size() && lineNo < maxY - 1; ++i) {
        mvwprintw(win, lineNo++, 2, "%s", wrapped[i].c_str());
    }

    wrefresh(win);

}
