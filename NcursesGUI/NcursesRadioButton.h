#ifndef __JJC__NCURSES__RADIO__BUTTON__H__
#define __JJC__NCURSES__RADIO__BUTTON__H__

#include <NcursesGUI/NcursesGUI.h>

/*
    +-+        +-+
    | |  <-->  |#|
    +-+        +-+
*/

class NcursesRadioButton : public NcursesItem {
private:

public:
    // inherited virtual functions:
    void update(void);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

void NcursesRadioButton::update(void) {

}

void NcursesRadioButton::enter(void) {

}

void NcursesRadioButton::exit(void) {

}

#endif // __JJC__NCURSES__RADIO__BUTTON__H__
