#ifndef __JJC__NCURSES__HORIZONTAL__LAYOUT__H__
#define __JJC__NCURSES__HORIZONTAL__LAYOUT__H__

#include <NcursesGUI/NcursesGUI.h>
#include <miniSTL/DynamicArray.h>

#define NHL NcursesHorizontalLayout

class NcursesHorizontalLayout : public NcursesItem {
private:
    DynamicArray<NcursesItem*> __item_vec;

public:
    void addItemToLayout(NcursesItem*);

    // inherited virtual functions
    void update(void);
    void enter(void);
    void exit(void);
    int getHeight(void);
    int getWidth(void);
};

void NHL::addItemToLayout(NcursesItem* _item) {
    __item_vec.pushBack(_item);
}



#endif // __JJC__NCURSES__HORIZONTAL__LAYOUT__H__
