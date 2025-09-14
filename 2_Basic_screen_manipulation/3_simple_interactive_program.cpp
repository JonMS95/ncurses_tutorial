#include <ncurses.h>

#define CURSOR_CHAR "O"

int main()
{
    initscr();

    keypad(stdscr, true);   // Enable arrow keys.
    noecho();               // Don't show typed characters.
    curs_set(0);            // Hide cursor.

    mvprintw(0, 0, "Press arrows to move the cursor, q to quit.");

    int row = 5;
    int col = 5;

    mvprintw(row, col, CURSOR_CHAR);
    
    refresh();

    int ch;

    while( (ch = getch()) != 'q' )  // While pressed key (character is retrievable by getch), keep it going if different from 'q'.
    {
        clear();
        
        if(ch == KEY_UP)    // KEY_UP/DOWN_LEFT/RIGHT are related to keyboard arrows.
            --row;
        if(ch == KEY_DOWN)
            ++row;
        if(ch == KEY_LEFT)
            --col;
        if(ch == KEY_RIGHT)
            ++col;
        
        mvprintw(row, col, CURSOR_CHAR);

        refresh();
    }

    endwin();

    return 0;
}