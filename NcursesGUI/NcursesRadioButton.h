#ifndef __JJC__NCURSES__RADIO__BUTTON__H__
#define __JJC__NCURSES__RADIO__BUTTON__H__

#include <iostream>
#include <NcursesGUI/NcursesGUI.h>

/*
    +-+        +-+
    | |  <-->  |#|
    +-+        +-+
*/

class NcursesRadioButton : public NcursesItem {
private:
    char* __border = "+-+";
    char  __ind[4] = {'|', ' ', '|', 0x00};

public:
    // constructor
    NcursesRadioButton(int color_pair_on, int color_pair_off);

    // interface method
    bool isActive(void);

    // inherited virtual functions:
    void update(int ch = 0);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NcursesRadioButton::NcursesRadioButton(int color_pair_on, int color_pair_off) {
    this->colorIndex_on  = color_pair_on;
    this->colorIndex_off = color_pair_off;
}

bool NcursesRadioButton::isActive(void) {
    if(__ind[1] == '#')
        return true;
    return false;
}

// inherited virtual function definitions

void NcursesRadioButton::update(int ch) {
    //std::cout << "Letter: " << ch << std::endl;
    if(ch == 10) {
        switch(__ind[1]) {
            case ' ':
                __ind[1] = '#';
                break;
            case '#':
                __ind[1] = ' ';
                break;
            default:
                break;
        }
    }
    attron(COLOR_PAIR(colorIndex_on));
    mvprintw(y,   x, "%s", __border);
    mvprintw(y+1, x, "%s", __ind);
    mvprintw(y+2, x, "%s", __border);
}

void NcursesRadioButton::enter(void) {
    update();
}

void NcursesRadioButton::exit(void) {
    attron(COLOR_PAIR(colorIndex_off));
    mvprintw(y,   x, "%s", __border);
    mvprintw(y+1, x, "%s", __ind);
    mvprintw(y+2, x, "%s", __border);
}

int NcursesRadioButton::getHeight(void) {
    return 3;
}

int NcursesRadioButton::getWidth(void) {
    return 3;
}

#endif // __JJC__NCURSES__RADIO__BUTTON__H__
