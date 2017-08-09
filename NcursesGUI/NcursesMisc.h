#ifndef __JJC__NCURSES__MISC__H__
#define __JJC__NCURSES__MISC__H__

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

#endif // __JJC__NCURSES__MISC__H__
