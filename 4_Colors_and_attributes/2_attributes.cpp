#include <ncurses.h>

int main()
{
    // On top of color pairs, other types of attributes can be applied:
    // ·A_BOLD
    // ·A_UNDERLINE
    // ·A_REVERSE (swap fg/bg)
    // ·A_DIM
    // ·A_BLINK
    // Where some of the ones above (for instance, the last couple) strongly
    // depend on the target terminal's support. A_BLINK is not commonly
    // supported.
    // Several attributes can be combined by using bitwise OR operator ( | ).

    initscr();

    if(!has_colors())
        return -1;
    
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    
    mvprintw(0, 0, "Simple text.");

    attron(A_BOLD | A_UNDERLINE);
    mvprintw(1, 0, "Bold and underlined text.");
    attroff(A_BOLD | A_UNDERLINE);

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);

    attron(A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
    mvprintw(2, 0, "Bold, underlined and colored text.");
    attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(1));
    
    attron(A_BOLD | A_UNDERLINE | COLOR_PAIR(1) | A_REVERSE);
    mvprintw(3, 0, "Bold, underlined and colored text with reverted colors.");
    attroff(A_BOLD | A_UNDERLINE | COLOR_PAIR(1) | A_REVERSE);

    attron(A_DIM);
    mvprintw(4, 0, "Dimmed text (press any key to exit).");
    attroff(A_DIM);

    getch();

    endwin();

    return 0;
}