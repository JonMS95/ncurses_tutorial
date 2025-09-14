#include <ncurses.h>

int main()
{
    initscr();

    // Color funcitonality should be started just after initscr and
    // before using any color functionality. Also, whether the target
    // terminal supports colors can be checked by using has_colors
    // function. Use start_color to init colors.
    if(!has_colors())
        return -1;
    
    start_color();

    // ncurses does not apply colors directly to text. Instead, color
    // pairs comprising foreground and background are defined. For
    // such purpose, init pair function is used, which syntax is the
    // following:
    // init_pair(short index, short fg, short bg);
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Use attron and attrof in combination with COLOR_PAIR(index) so
    // as to turn on/off a color pair.
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "This is red on white.");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    mvprintw(1, 0, "This is green on black.");
    attroff(COLOR_PAIR(2));

    refresh();

    getch();

    endwin();

    return 0;
}