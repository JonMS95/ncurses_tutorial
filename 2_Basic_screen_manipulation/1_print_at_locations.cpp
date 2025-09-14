#include <ncurses.h>

int main()
{
    initscr();
    
    mvprintw(5, 10, "This text starts at row 5, column 10.");       // "mvprintw" stands for "move print window".
    mvprintw(6, 0, "This text starts at the beginning of row 6.");  // Cursor does not move after executing mvprintw (it remains where it was left by mvprintw).
    printw(" Hello!");                                              // In this case, row 6.
    mvprintw(0, 5, "This text starts at the first line.");          // Rows and columns are 0-indexed.
    
    // As seen above, the order does not matter as long as different rows are organized before refreshing.

    move(8, 10);    // Cursor can be moved freely without forcing it to print anything (0, 0 by default unless explicitly modified).
    addch('X');     // Print a single character.

    refresh();

    getch();
    endwin();

    return 0;
}