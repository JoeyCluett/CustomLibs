#ifndef __JJC__NCURSES__TEXT__OUTPUT__H__
#define __JJC__NCURSES__TEXT__OUTPUT__H__

class NcursesTextOutput : public NcursesItem {
private:
    string text, tag;

public:
    NcursesTextOutput(int color_pair) {
        this->colorIndex = color_pair;
    }

    void setText(string text) {
        this->text = text;
    }

    void setTag(string tag) {
        this->tag = tag;
    }

    // inherited virtual function definitions

    void update(void) {
        string temp = tag + text;
        attron(COLOR_PAIR(colorIndex));
        mvprintw(y, x, "%s", temp.c_str());
    }

    void enter(void) {
        update();
    }

    void exit(void) {
        update();
    }

    int getHeight(void) {
        return 1;
    }

    int getWidth(void) {
        return tag.length() + text.length();
    }
};


#endif // __JJC__NCURSES__TEXT__OUTPUT__H__
