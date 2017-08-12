#ifndef __JJC__NCURSES__TEXT__OUTPUT__H__
#define __JJC__NCURSES__TEXT__OUTPUT__H__

#include <ncurses.h>
#include <string.h>
#include <string>

#include <NcursesGUI/NcursesMisc.h>

class NcursesTextOutput : public NcursesItem {
private:
    std::string text, tag;
    int num_chars;

    // clears the line needed for characters
    void clearChars(int color_this);

    // put the string on screen but clamp the distance to num_chars
    void putString(std::string);

public:
    // all item constructors must be passed a color pair to use
    NcursesTextOutput(int color_pair_on, int color_pair_off, int num_chars);

    // set the primary text of this TextOutput
    void setText(std::string text);

    // set the tag of this TextOutput
    void setTag(std::string tag);

    // inherited virtual functions:
    void update(int ch = 0);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NcursesTextOutput::NcursesTextOutput(int color_pair_on, int color_pair_off, int num_chars) {
    this->colorIndex_on  = color_pair_on;
    this->colorIndex_off = color_pair_off;
    this->num_chars      = num_chars;
    this->__ITEM_TYPE    = __N_Type::id_text_output;
}

void NcursesTextOutput::setText(std::string text) {
    this->text = text;
}

void NcursesTextOutput::setTag(std::string tag) {
    this->tag = tag;
}

void NcursesTextOutput::clearChars(int color_this) {
    move(y, x);
    attron(COLOR_PAIR(color_this));
    for(int i = 0; i < num_chars; i++) {
        addch(' ');
    }
}

void NcursesTextOutput::putString(std::string str) {
    int max_chars = str.length();
    if(num_chars < max_chars)
        max_chars = num_chars;

    char* char_str = new char[num_chars + 1];
    for(int i = 0; i < num_chars; i++)
        char_str[i] = ' ';
    char_str[num_chars] = 0x00;

    for(int i = 0; i < max_chars; i++) {
        char_str[i] = str[i];
    }
    //char_str[max_chars] = 0x00;

    mvprintw(y, x, "%s", char_str);

    delete[] char_str;
}

// inherited virtual function definitions

void NcursesTextOutput::update(int ch) {
    clearChars(colorIndex_on);
    attron(COLOR_PAIR(colorIndex_on));
    std::string temp = tag + text;
    putString(temp);
}

void NcursesTextOutput::enter(void) {
    update();
}

void NcursesTextOutput::exit(void) {
    clearChars(colorIndex_off);
    attron(COLOR_PAIR(colorIndex_off));
    std::string temp = tag + text;
    putString(temp);
}

int NcursesTextOutput::getHeight(void) {
    return 1;
}

int NcursesTextOutput::getWidth(void) {
    return num_chars;
}

#endif // __JJC__NCURSES__TEXT__OUTPUT__H__
