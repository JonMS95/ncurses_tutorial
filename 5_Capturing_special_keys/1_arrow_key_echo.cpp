#include <ncurses.h>

#define KEY_DEF_ESC     27
#define KEY_DEF_ENTER   10

// by default, getch() only "sees" raw ASCII. To get arrow keys, F-keys and so on
// captured you need keypad function.

int main()
{
    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, true);

    mvprintw(0, 0, "Press arrow keys (ESC/ENTER to quit).");

    int ch;

    while( (ch = getch()) != KEY_DEF_ESC )
    {
        move(1, 0);
        clrtoeol();
        move(1, 0);

        switch(ch)
        {
            case KEY_UP:
            {
                printw("Pressed UP.");
            }
            break;
            
            case KEY_DOWN:
            {
                printw("Pressed DOWN.");
            }
            break;
            
            case KEY_LEFT:
            {
                printw("Pressed LEFT.");
            }
            break;
            
            case KEY_RIGHT:
            {
                printw("Pressed RIGHT.");
            }
            break;

            case KEY_DEF_ESC:
            case KEY_DEF_ENTER:
            {
                endwin();
                return 0;
            }

            default:
            {
                printw("Pressed \'%c\' (not an arrow!).", ch);
            }
            break;
        }

        refresh();
    }

    endwin();
}