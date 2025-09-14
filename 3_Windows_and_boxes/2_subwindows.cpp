#include <ncurses.h>
#include "box_dims.hpp"

#define WB_CHAR '*'

int main()
{
    initscr();
    noecho();
    curs_set(0);

    int max_y, max_x;

    getmaxyx(stdscr, max_y, max_x);

    BOX_DIMS main_screen_dims =
    {
        .height = max_y - 1 ,
        .width  = max_x - 1 ,
        .min_y  = 0         ,
        .min_x  = 0         ,
    };

    BOX_DIMS box_1_dims =
    {
        .height = main_screen_dims.height       ,
        .width  = (main_screen_dims.width / 2)  ,
        .min_y  = main_screen_dims.min_y        ,
        .min_x  = 0                             ,
    };

    BOX_DIMS box_2_dims =
    {
        .height = main_screen_dims.height                       ,
        .width  = (main_screen_dims.width - box_1_dims.width)   ,
        .min_y  = main_screen_dims.min_y                        ,
        .min_x  = (main_screen_dims.min_x + box_1_dims.width)   ,
    };

    WINDOW* box_1 = newwin(box_1_dims.height, box_1_dims.width, box_1_dims.min_y, box_1_dims.min_x);
    WINDOW* box_2 = newwin(box_2_dims.height, box_2_dims.width, box_2_dims.min_y, box_2_dims.min_x);

    box(box_1, WB_CHAR, WB_CHAR);
    box(box_2, WB_CHAR, WB_CHAR);

    refresh();

    mvwprintw(box_1, box_1_dims.min_y + 1, box_1_dims.min_y + 1, "Hello! this is box 1");
    mvwprintw(box_1, box_1_dims.min_y + 2, box_1_dims.min_y + 1, "Press any key");

    wrefresh(box_1);

    getch();

    mvwprintw(box_2, box_2_dims.min_y + 1, box_2_dims.min_y + 1, "Hello! this is box 2");
    mvwprintw(box_2, box_2_dims.min_y + 2, box_2_dims.min_y + 1, "Look at box 1!");

    wrefresh(box_2);

    getch();

    BOX_DIMS sub_box_1_dims =
    {
        .height = (box_1_dims.height / 2)   ,
        .width  = (box_1_dims.width / 2)    ,
        .min_y  = (box_1_dims.height / 4)   ,
        .min_x  = (box_1_dims.width / 4)    ,
    };

    // derwin is like subwin but uses relative coordinates from the parent window.
    WINDOW* sub_box_1 = subwin(box_1, sub_box_1_dims.height, sub_box_1_dims.width, sub_box_1_dims.min_y, sub_box_1_dims.min_x);
    box(sub_box_1, WB_CHAR, WB_CHAR);

    mvwprintw(sub_box_1, sub_box_1_dims.height / 2, sub_box_1_dims.width / 4, "This is a subwindow!");
    wrefresh(sub_box_1);

    getch();

    BOX_DIMS overlapping_box_dims =
    {
        .height = (main_screen_dims.height / 2) ,
        .width  = (main_screen_dims.width / 2)  ,
        .min_y  = (main_screen_dims.height / 4) ,
        .min_x  = (main_screen_dims.width / 4)  ,
    };

    WINDOW* overlapping_box = newwin(overlapping_box_dims.height, overlapping_box_dims.width, overlapping_box_dims.min_y, overlapping_box_dims.min_x);
    box(overlapping_box, WB_CHAR, WB_CHAR);

    mvwprintw(overlapping_box, overlapping_box_dims.height / 2, overlapping_box_dims.width / 2, "This is an overlapping window!");
    wrefresh(overlapping_box);

    getch();

    werase(overlapping_box);
    wrefresh(overlapping_box);
    delwin(overlapping_box);

    touchwin(sub_box_1);
    touchwin(box_1);
    touchwin(box_2);

    wrefresh(sub_box_1);
    wrefresh(box_1);
    wrefresh(box_2);

    getch();

    werase(sub_box_1);
    wrefresh(sub_box_1);
    delwin(sub_box_1);

    getch();

    werase(box_1);
    wrefresh(box_1);
    delwin(box_1);

    getch();

    werase(box_2);
    wrefresh(box_2);
    delwin(box_2);

    mvprintw(main_screen_dims.min_y + main_screen_dims.height, main_screen_dims.min_x, "Bye bye!");
    refresh();

    getch();

    endwin();

    return 0;
}
