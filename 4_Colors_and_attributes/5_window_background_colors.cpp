#include <ncurses.h>

// Same as text, windows can have their very own background color in ncurses.

int main()
{
    initscr();
    cbreak();
    curs_set(0);
    noecho();

    if(!has_colors())
        return -1;

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    // Create two windows.
    int h_1 = 10;
    int w_1 = 30;
    int h_2 = h_1;
    int w_2 = w_1;

    int y_1 = 1;
    int x_1 = 1;
    int y_2 = 5;
    int x_2 = 15;

    WINDOW* win_1 = newwin(h_1, w_1, y_1, x_1);
    WINDOW* win_2 = newwin(h_2, w_2, y_2, x_2);

    // Don't forget to refresh the screen somewhere before printing to each window.
    refresh();

    // Set different background.
    wbkgd(win_1, COLOR_PAIR(1));
    wbkgd(win_2, COLOR_PAIR(2));

    // Don't get confused with wattron / wattroff, which is used to modify text's attributes only within a window.

    box(win_1, 0, 0);
    box(win_2, 0, 0);

    mvwprintw(win_1, 1, 1, "Blue background");
    mvwprintw(win_2, 1, 1, "Green background");

    wrefresh(win_1);
    wrefresh(win_2);

    getch();
    endwin();

    return 0;
}