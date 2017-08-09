#ifndef __JJC__NCURSES__MISC__H__
#define __JJC__NCURSES__MISC__H__

#include <ncurses.h>
#include <thread>
#include <boost/thread.hpp>

void initializeNcurses(int BACKGROUND_COLOR) {
    initscr();
    raw();
    keypad(stdscr, true);

    start_color();
    init_pair(1, COLOR_WHITE, BACKGROUND_COLOR); //<text color>, <background color>

    int row, col;
    getmaxyx(stdscr, row, col);

    attron(COLOR_PAIR(1));
    for(int y = 0; y < row; y++) {
        for(int x = 0; x < col; x++) {
            mvaddch(y, x, ' ');
        }
    }
    refresh();
}

// clear the entire screen
void clearNcursesScreen(int BACKGROUND_COLOR) {
    init_pair(1, COLOR_WHITE, BACKGROUND_COLOR); //<text color>, <background color>

    int row, col;
    getmaxyx(stdscr, row, col);

    attron(COLOR_PAIR(1));
    for(int y = 0; y < row; y++) {
        for(int x = 0; x < col; x++) {
            mvaddch(y, x, ' ');
        }
    }
}

// refresh stdscr in a thread-safe way
void threadSafeRefresh(void) {
    static boost::mutex mtx;
    mtx.lock();
    refresh();
    mtx.unlock();
}

// move cursor to bottom left of screen
void mvCursor(void) {
    int row, col;
    getmaxyx(stdscr, row, col);

    mvaddch(col-1, 0, ' ');
}

#endif // __JJC__NCURSES__MISC__H__
