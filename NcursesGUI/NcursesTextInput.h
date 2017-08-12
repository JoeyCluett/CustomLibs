#ifndef __JJC__NCURSES__TEXT__INPUT__H__
#define __JJC__NCURSES__TEXT__INPUT__H__

#include <ncurses.h>
#include <string.h>
#include <string>

class NcursesTextInput : public NcursesItem {
private:
    std::string __contents;
    int num_chars;
    void clearChars(int color_this);
    bool __editing = false;

public:
    NcursesTextInput(int color_pair_on, int color_pair_off, int num_chars);

    // get the current contents of this TextInput
    std::string getText(void);

    // return the internal state of this Item
    bool isEditing(void);

    // inherited virtual functions:
    void update(int ch = 0);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NcursesTextInput::NcursesTextInput(int color_pair_on, int color_pair_off, int num_chars) {
    this->colorIndex_on  = color_pair_on;
    this->colorIndex_off = color_pair_off;
    this->num_chars      = num_chars;
    this->__ITEM_TYPE    = __N_Type::id_text_input;
}

bool NcursesTextInput::isEditing(void) {
    return __editing;
}

void NcursesTextInput::clearChars(int color_this) {
    attron(COLOR_PAIR(color_this));
    move(y, x);
    for(int i = 0; i < num_chars+2; i++)
        addch(' ');
}

std::string NcursesTextInput::getText(void) {
    return __contents;
}

// inherited virtual function definitions

void NcursesTextInput::update(int ch) {
    if(__contents.length() < num_chars) {
        if(__editing == false) {
            if(ch == 10)
                __editing = true;
        } else {
            if(ch == 27)
                __editing = false;
            else {
                if(ch != 10) {
                    if(ch == 263 && __contents.length() > 0) // backspace
                        __contents.pop_back();
                    else
                        __contents += (char)ch;
                }
            }
        }
    }

    clearChars(colorIndex_on);

    if(__editing) {
        attron(COLOR_PAIR(colorIndex_on) | A_BLINK | A_BOLD);
        mvprintw(y, x, "%s", "> ");
        attroff(COLOR_PAIR(colorIndex_on) | A_BLINK | A_BOLD);

        attron(COLOR_PAIR(colorIndex_on));
        mvprintw(y, x+2, "%s", __contents.c_str());
    } else {
        attron(COLOR_PAIR(colorIndex_on));
        mvprintw(y, x, "%s", __contents.c_str());
    }
}

void NcursesTextInput::enter(void) {
    update(0x00000000);
}

void NcursesTextInput::exit(void) {
    clearChars(colorIndex_off);
    attron(COLOR_PAIR(colorIndex_off));
    mvprintw(y, x, "%s", __contents.c_str());
}

int NcursesTextInput::getHeight(void) {
    return 1;
}

int NcursesTextInput::getWidth(void) {
    return num_chars + 2;
}

#endif // __JJC__NCURSES__TEXT__INPUT__H__
