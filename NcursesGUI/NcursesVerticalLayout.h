#ifndef __JJC__NCURSES__VERTICAL__LAYOUT__H__
#define __JJC__NCURSES__VERTICAL__LAYOUT__H__

#include <ncurses.h>
#include <NcursesGUI/NcursesGUI.h>
#include <miniSTL/DynamicArray.h>

#define NVL NcursesVerticalLayout

class NcursesVerticalLayout : public NcursesItem {
private:
    DynamicArray<NcursesItem*> __item_vec;
    int currentItemIndex = 0;
public:
    // add an NcursesItem to this layout
    void addItemToLayout(NcursesItem*);

    // inherited virtual functions
    void update(void);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

void NVL::addItemToLayout(NcursesItem* _item) {
    __item_vec.pushBack(_item);
}

void NVL::update(void) {

}

void NVL::enter(void) {

}

void NVL::exit(void) {

}

int NVL::getWidth(void) {
    int s = __item_vec.arraySize();
    int w = 0;

    for(int i = 0; i < s; i++) {
        if(__item_vec[i]->getWidth() > w)
            w = __item_vec[i]->getWidth();
    }

    return w;
}

int NVL::getHeight(void) {
    int s = __item_vec.arraySize();
    int h = 0;
    for(int i = 0; i < s; i++) {
        h += __item_vec[i]->getHeight();
    }
    return h;
}

#endif // __JJC__NCURSES__VERTICAL__LAYOUT__H__
