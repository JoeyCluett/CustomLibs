#ifndef __JJC__NCURSES__CHECKBOX__H__
#define __JJC__NCURSES__CHECKBOX__H__

#include <NcursesGUI/NcursesGUI.h>

/*
    +--+        +--/
    |  |  <-->  |\/|
    +--+  <-->  +--+
*/

class NcursesCheckbox : public NcursesItem {
private:
    bool __checked = false;
    void fillChars(int color_this);

public:
    NcursesCheckbox(int color_pair_on, int color_pair_off);

    // inherited virtual functions:
    void update(int ch = 0);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NcursesCheckbox::NcursesCheckbox(int color_pair_on, int color_pair_off) {
    this->colorIndex_on  = color_pair_on;
    this->colorIndex_off = color_pair_off;
}

void NcursesCheckbox::fillChars(int color_this) {
    attron(COLOR_PAIR(color_this));
    mvprintw(y,   x, "+--+");
    mvprintw(y+1, x, "|  |");
    mvprintw(y+2, x, "+--+");
    attroff(COLOR_PAIR(color_this));
}

// inherited virtual function definitions

void NcursesCheckbox::update(int ch) {
    if(ch == 10)
        __checked = !__checked;

    fillChars(colorIndex_on);

    if(__checked) {
        attron(COLOR_PAIR(colorIndex_on) | A_BOLD);
        mvaddch(y+0, x+3, '/');
        mvaddch(y+1, x+1, '\\');
        mvaddch(y+1, x+2, '/');
        attroff(COLOR_PAIR(colorIndex_on) | A_BOLD);
    }

}

void NcursesCheckbox::enter(void) {
    update(0x00000000);
}

void NcursesCheckbox::exit(void) {

}

int NcursesCheckbox::getHeight(void) {
    return 3;
}

int NcursesCheckbox::getWidth(void) {
    return 4;
}

#endif // __JJC__NCURSES__CHECKBOX__H__
