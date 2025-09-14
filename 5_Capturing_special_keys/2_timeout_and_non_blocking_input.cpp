#include <ncurses.h>

#define MSG_USAGE   "Use arrow keys to move O. Press ESC to quit."
#define MSG_CURSOR  "O"

#define KEY_DEF_ESC 27

// Up until now, getch has been strictly used to wait for the user to press a key.
// However, it sometimes happens that we don't want a blocking input but to have
// the possibility to go ahead anyways instead. For such purposes, timeout functions
// exist in ncurses as part of the library.
// ·timeout(ms): waits up to ms miliseconds for user input. If a key is pressed within
// the specified time window, then the key is returned. If no key is pressed: ERR.
// · halfdelay(t): similar to timeout, but t is defined in tenths of a second. It
// enables cbreak automatically and returns ERR if no input occurs within the given
// time.
// · nodelay(win, true): makes getch() non-blocking. If no key is pressed ERR is
// returned.
// In this case, timeout funciton usage will be covered.

int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();
    keypad(stdscr, true);

    int x = 0;
    int ch;
    bool leftwards = false;

    // Set timeout for upcoming getch function calls as 200 ms.
    timeout(200);

    while(true)
    {
        clear();
        mvprintw(0, 0, MSG_USAGE);
        mvprintw(2, x, MSG_CURSOR);
        refresh();

        ch = getch();

        if(ch == KEY_DEF_ESC)
            break;
        
        switch(ch)
        {
            case KEY_LEFT:
            {
                leftwards = true;
            }
            break;

            case KEY_RIGHT:
            {
                leftwards = false;
            }
            break;
        }

        if(leftwards)
        {
            if(x > 0)
                --x;
            else
                x = COLS - 1;   // COLS is the variable retrieved when calling getmaxx.
        }
        else
            x = (x + 1) % COLS;
    }

    endwin();

    return 0;
}