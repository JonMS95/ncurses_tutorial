#include <ncurses.h>
#include "box_dims.hpp"

int main()
{
    // 1 - Initialize the screen, set as "no echo" and hide the cursor.
    initscr();
    noecho();
    curs_set(0);
    
    // 2 - Get max values for both height and width.
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // 3 - Set starting coordinates as well as height and width for each box.
    BOX_DIMS box_1_dims = 
    {
        .height = max_y - 1,
        .width  = max_x / 2,
        .min_y  = 0 ,
        .min_x  = 0 ,
    };

    BOX_DIMS box_2_dims = 
    {
        .height = max_y - 1,
        .width  = (max_x / 2) + 1,
        .min_y  = 0 ,
        .min_x  = box_1_dims.min_x +
                  box_1_dims.width,
    };

    // 4 - Initialize each new box by using values into each struct. Set borders for each box too.
    WINDOW* box_1 = newwin(box_1_dims.height, box_1_dims.width, box_1_dims.min_y, box_1_dims.min_x);
    WINDOW* box_2 = newwin(box_2_dims.height, box_2_dims.width, box_2_dims.min_y, box_2_dims.min_x);

    box(box_1, '|', '-');
    box(box_2, '*', '+');

    refresh();  // Refresh main screen before applying changes to any box within. Always refresh before wrefresh.

    // 5 - Add data to each box. Go step by step, prompting the user to press any key each time.
    mvwprintw(box_1, 1, 1, "Press any key");
    wrefresh(box_1);

    getch();

    mvwprintw(box_1, 2, 1, "This is my first box");
    wrefresh(box_1);

    getch();

    mvwprintw(box_2, 1, 1, "Press any key");    // Note that only the target window is updated each time.
    wrefresh(box_2);

    getch();

    mvwprintw(box_2, 2, 1, "This is my second box");
    wrefresh(box_2);

    getch();

    mvprintw(max_y - 1, 0, "This is a footer. It's not part of the windows above!");
    refresh();

    getch();

    // 6 - Clear and delete each box.
    werase(box_1);
    wrefresh(box_1);
    delwin(box_1);

    getch();

    werase(box_2);
    wrefresh(box_2);
    delwin(box_2);

    getch();

    // 7 - Erase final row to remove footer.
    move(max_y - 1, 0);
    clrtoeol();
    refresh();
    getch();

    // 8 - Close all windows.
    endwin();

    return 0;
}
