#ifndef __JJC__NCURSES__VERTICAL__LAYOUT__H__
#define __JJC__NCURSES__VERTICAL__LAYOUT__H__

#include <ncurses.h>
#include <NcursesGUI/NcursesGUI.h>
#include <miniSTL/DynamicArray.h>

#define NVL NcursesVerticalLayout

class NcursesVerticalLayout : public NcursesItem {
private:
    DynamicArray<NcursesItem*> __item_vec;
    int __item_space = 0; // how much padding for each menu item
    int currentItemIndex = 0;

public:
    // constructor
    NcursesVerticalLayout(int item_space = 0);

    // add an NcursesItem to this layout
    void addItemToLayout(NcursesItem* _item);

    // configure the layout with all of the Items inside
    void configure(void);

    // inherited virtual functions
    void update(int ch = 0);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

NcursesVerticalLayout::NcursesVerticalLayout(int item_space) {
    this->__item_space = item_space;
    this->__ITEM_TYPE  = __N_Type::id_vertical_layout;
}

void NVL::addItemToLayout(NcursesItem* _item) {
    __item_vec.pushBack(_item);
}

void NcursesVerticalLayout::configure(void) {
    int s = __item_vec.arraySize();
    int _y = __item_space;

    for(int i = 0; i < s; i++) {
        __item_vec[i]->setPosition(x, y+_y);
        _y += (__item_vec[i]->getHeight() + __item_space);

        // layout needs to be recursively configured
        int __id = __item_vec[i]->getType();
        if(__id == __N_Type::id_vertical_layout ||
                __id == __N_Type::id_horizontal_layout)
            __item_vec[i]->configure();
    }
}

// inherited virtual function definitions

void NcursesVerticalLayout::update(int ch) {
    int id = __item_vec[currentItemIndex]->getType();
    if(ch == 'w' || ch == 's') { // normally the menu item would change
        if(id == __N_Type::id_text_input){
            if(__item_vec[currentItemIndex]) { //

            }
        }
    }
}

void NcursesVerticalLayout::enter(void) {
    currentItemIndex = 0;
    int s = __item_vec.arraySize();

    for(int i = 0; i < s; i++)
        __item_vec[i]->exit();

    __item_vec[i]->enter();
}

void NcursesVerticalLayout::exit(void) {

}

int NcursesVerticalLayout::getWidth(void) {
    int s = __item_vec.arraySize();
    int w = 0;

    for(int i = 0; i < s; i++) {
        if(__item_vec[i]->getWidth() > w)
            w = __item_vec[i]->getWidth();
    }
    return w;
}

int NcursesVerticalLayout::getHeight(void) {
    int s = __item_vec.arraySize();
    int h = 0;

    for(int i = 0; i < s; i++) {
        h += __item_vec[i]->getHeight();
    }

    h += (__item_vec.arraySize() * __item_space + __item_space);

    return h;
}

#endif // __JJC__NCURSES__VERTICAL__LAYOUT__H__
