#include <ncurses.h>
#include <panel.h>
#include <vector>

#define NUM_OF_WINS 10

#define MSG_USAGE   "Use arrows to move main panel. Use q / Q to end the program."

/*
In this example, we will create 10 windows wrapped by another 10 panels.
By using up / down arrows, the order will be modified.
*/

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, true);

    int h       = 15;
    int w       = 30;
    int st_x    = 5 ;
    int st_y    = 5 ;

    int ch;

    int main_panel_index = 0;

    std::vector<WINDOW*>    win_vector(NUM_OF_WINS)     ;
    std::vector<panel*>     panel_vector(NUM_OF_WINS)   ;

    for(int idx = 0; idx < NUM_OF_WINS; idx++)
    {
        win_vector[idx] = newwin(h, w, st_y + idx, st_x + (2 * idx));

        box(win_vector[idx], 0, 0);

        panel_vector[idx] = new_panel(win_vector[idx]);

        bottom_panel(panel_vector[(main_panel_index + idx) % NUM_OF_WINS % NUM_OF_WINS]);
    }

    mvprintw(1, 1, MSG_USAGE);

    update_panels();
    doupdate();

    while(true)
    {
        ch = getch();

        if(ch == 'q' || ch == 'Q')
            break;

        if(ch == KEY_DOWN)
            main_panel_index = (main_panel_index + 1) % NUM_OF_WINS;
        else if(ch == KEY_UP)
            main_panel_index = (main_panel_index + NUM_OF_WINS - 1) % NUM_OF_WINS;
        else
            continue;

        for(int idx = 0; idx < NUM_OF_WINS; idx++)
            bottom_panel(panel_vector[(main_panel_index + idx) % NUM_OF_WINS]);

        update_panels();
        doupdate();
    }

    WINDOW* temp_win_ptr;

    for(int idx = 0; idx < NUM_OF_WINS; idx++)
    {
        temp_win_ptr = panel_window(panel_vector[idx]);
        
        del_panel(panel_vector[idx]);
        delwin(temp_win_ptr);
    }

    endwin();

    return 0;
}