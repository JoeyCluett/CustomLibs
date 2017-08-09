#ifndef __JJC__NCURSES__ITEM__H__
#define __JJC__NCURSES__ITEM__H__

class NcursesItem {
protected:
    // where on screen is the item located
    int x = 0, y = 0;
    int colorIndex;

public:
    void setPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    // when a menu item as actually used
    // this function is called
    // menu items are used by pressing ENTER
    // when they are hovered over
    virtual void update(void) = 0;

    // when a menu item is hovered over
    virtual void enter(void) = 0;

    // when a menu item that was hovered over is no longer hovered over
    virtual void exit(void) = 0;

    // height depends on what item this is
    virtual int getHeight(void) = 0;

    // width depends on what item this is
    virtual int getWidth(void) = 0;
};

#endif // __JJC__NCURSES__ITEM__H__
