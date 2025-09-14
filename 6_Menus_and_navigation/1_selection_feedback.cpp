#include <ncurses.h>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

#define KEY_DEF_ESC     27
#define KEY_DEF_ENTER   10

#define MSG_QUIT    "Press q/Q/ESC to exit or choose \"Exit\" option then ENTER."
#define MSG_BYE     "Bye bye!"

/*
This lesson will be the only one in the current chapter. Since it can be seen as the 
compilation of all of the lessons in the chapters before, no further explanation is
will be provided this time.
*/

int main()
{
    using options_list = std::vector<std::pair<std::string, std::string>>;

    initscr();
    noecho();
    curs_set(0);
    cbreak();
    keypad(stdscr, true);

    bool term_has_colors = has_colors();

    if(term_has_colors)
        start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);

    const options_list menu_options =
    {
        {"Name"     ,   "Hello, my name is John"},
        {"Surname"  ,   "My surname is Smith"   },
        {"Age"      ,   "I am 30 years old"     },
        {"Town"     ,   "I live in London"      },
        {"Exit"     ,   "Press enter to exit"   },
    };

    int opt_idx = 0;
    int opt_num = menu_options.size();
    int ch;
    bool keep_loop = true;

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    WINDOW* win_l = newwin(2 * max_y / 3, max_x / 3, 0, 0);
    WINDOW* win_r = newwin(2 * max_y / 3, max_x - (max_x / 3), 0, max_x - 2 * (max_x / 3));
    WINDOW* win_d = newwin(max_y -  (2 * max_y / 3), max_x, 2 * max_y / 3, 0);

    box(win_l, 0, 0);
    box(win_r, 0, 0);
    box(win_d, 0, 0);

    refresh();

    wrefresh(win_l);
    wrefresh(win_r);
    wrefresh(win_d);

    wclear(win_l);
    wclear(win_r);
    wclear(win_d);
    box(win_l, 0, 0);
    box(win_r, 0, 0);
    box(win_d, 0, 0);

    mvwprintw(win_d, 1, 1, MSG_QUIT);
    wrefresh(win_d);

    auto prn_opt = [&]() -> void
    {
        wclear(win_l);
        wclear(win_r);

        box(win_l, 0, 0);
        box(win_r, 0, 0);

        for(int i = 0; i < opt_num; i++)
        {
            if(i == opt_idx)
                wattron(win_l, COLOR_PAIR(1) | A_BOLD);

            mvwprintw(win_l, 1 + i, 1, "%s%s", (i == opt_idx ? ">> " : ""), menu_options[i].first.c_str());

            if(i == opt_idx)
                wattroff(win_l, COLOR_PAIR(1) | A_BOLD);
        }

        mvwprintw(win_r, 1, 1, "%s", menu_options[opt_idx].second.c_str());

        wrefresh(win_l);
        wrefresh(win_r);
    };

    prn_opt();

    while(keep_loop)
    {
        ch = getch();

        switch(ch)
        {
            case KEY_UP:
            {
                opt_idx = ((opt_idx + opt_num) - 1) % opt_num;
            }
            break;

            case KEY_DOWN:
            {
                opt_idx = (opt_idx + 1) % opt_num;
            }
            break;

            case 'q'        :
            case 'Q'        :
            case KEY_DEF_ESC:
            {
                keep_loop = false;
            }
            break;

            case KEY_DEF_ENTER:
            {
                if(opt_idx == (opt_num - 1))
                    keep_loop = false;
            }
            break;

            default:
            break;
        }

        prn_opt();
    }

    werase(win_d);
    box(win_d, 0, 0);
    mvwprintw(win_d, 1, 1, MSG_BYE);
    wrefresh(win_d);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    delwin(win_l);
    delwin(win_r);
    delwin(win_d);

    endwin();

    return 0;
}