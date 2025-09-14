#include <ncurses.h>
#include <panel.h>

/*
In ncurses, windows can overlap. Also, when a window on top is refreshed, it may end up
erasing part of the window below. Panels provide stacking order, autoatic redraw and
convenient hiding. This way, windows can be ordered in the z axis and manual refreshments
are no longer required.
*/

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int height  = 10;
    int width   = 30;
    int st_y    = 2 ;
    int st_x    = 4 ;

    // Create two overlapping windows.
    WINDOW* win_1 = newwin(height, width, st_y, st_x);
    WINDOW* win_2 = newwin(height, width, st_y + 2, st_x + 10);

    // Draw windows.
    box(win_1, 0, 0);
    box(win_2, 0, 0);

    mvprintw(0, 0, "Press any key to swap panels");
    mvwprintw(win_1, 1, 1, "First window");
    mvwprintw(win_2, 1, 1, "Second window");

    // Create panels. Panel 2 is on top by default.
    // "new_panel" function wrap an ncurses window into a panel.
    PANEL* panel_1 = new_panel(win_1);
    PANEL* panel_2 = new_panel(win_2);

    update_panels();    // Refresh panel stack.
    doupdate();         // Refresh the screen rendering all panels in correct order.

    // AS a rule of thumb:
    // ·refresh and wrefresh with windows.
    // ·update_panels and doupdate with panels.

    getch();

    // Swap panels by moving panel_1 to the top: 
    top_panel(panel_1);
    update_panels();
    doupdate();

    getch();

    // Now move panel_1 back to the bottom:
    bottom_panel(panel_1);
    update_panels();
    doupdate();

    getch();

    // Panels can be hidden / shown by using hide_panel(panel) / show_panel(panel).
    // Let's hide current top panel.
    hide_panel(panel_2);
    update_panels();
    doupdate();

    getch();

    // Now let's show it again.
    show_panel(panel_2);
    update_panels();
    doupdate();

    getch();

    // Clean up. Always delete panels before deleting windows.
    del_panel(panel_1);
    del_panel(panel_2);
    delwin(win_1);
    delwin(win_2);

    endwin();

    return 0;
}