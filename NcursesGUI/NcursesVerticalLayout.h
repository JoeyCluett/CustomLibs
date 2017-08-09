#ifndef __JJC__NCURSES__VERTICAL__LAYOUT__H__
#define __JJC__NCURSES__VERTICAL__LAYOUT__H__

class NcursesVerticalLayout {
private:
    vector<NcursesItem*> __item_vec;
public:
    int getHeight(void) {
        int s = __item_vec.size();
        int h = 0;
        for(int i = 0; i < s; i++) {
            h += __item_vec[i]->getHeight();
        }
        return h;
    }
};

#endif // __JJC__NCURSES__VERTICAL__LAYOUT__H__
