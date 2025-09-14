#include <ncurses.h>

int main()
{
    // 1 - Initialize ncurses.

    initscr();              // Start ncurses mode (takes control of the terminal).
    printw("Hello world!"); // Print at current cursor, same as printf but working inside ncurses.
    refresh();              // Refresh screen to show text (i.e., tells ncurses to update the screen).

    // 2 - Wait for user input.

    getch();                // Waits for a key to be pressed.

    // 3 - End ncurses mode.

    endwin();               // Ends ncurses mode by closing prevously created window.

    return 0;
}