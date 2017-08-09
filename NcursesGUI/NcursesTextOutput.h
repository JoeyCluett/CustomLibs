#ifndef __JJC__NCURSES__TEXT__OUTPUT__H__
#define __JJC__NCURSES__TEXT__OUTPUT__H__

#include <ncurses.h>
#include <string.h>
#include <string>

#include <NcursesGUI/NcursesMisc.h>

#define NcursesTextOutput NTO

class NcursesTextOutput : public NcursesItem {
private:
    std::string text, tag;

public:
    // all item constructors must be passed a color pair to use
    NcursesTextOutput(int color_pair);

    // set the primary text of this TextOutput
    void setText(std::string text);

    // set the tag of this TextOutput
    void setTag(std::string tag);

    // inherited virtual functions:
    void update(void);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NTO::NcursesTextOutput(int color_pair) {
    this->colorIndex = color_pair;
}

void NTO::setText(std::string text) {
    this->text = text;
}

void NTO::setTag(std::string tag) {
    this->tag = tag;
}

// inherited virtual function definitions

void NTO::update(void) {
    std::string temp = tag + text;
    attron(COLOR_PAIR(colorIndex));
    mvprintw(y, x, "%s", temp.c_str());
}

void NTO::enter(void) {
    update();
}

void NTO::exit(void) {
    update();
}

int NTO::getHeight(void) {
    return 1;
}

int NTO::getWidth(void) {
    return tag.length() + text.length();
}

#endif // __JJC__NCURSES__TEXT__OUTPUT__H__
