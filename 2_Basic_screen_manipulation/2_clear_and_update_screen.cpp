#include <ncurses.h>

int main()
{
    initscr();

    printw("First line of text");
    refresh();
    getch();

    clear();

    mvprintw(0, 0, "Screen cleared!");
    
    refresh();
    getch();

    endwin();

    return 0;
}