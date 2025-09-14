#include <ncurses.h>

#define MSG_USAGE           "Use UP/DOWN arrows, ENTER to select, q/Q to exit."
#define MSG_CHOSEN_OPTION   "You chose: \"%s\"."

#define KEY_ENTER_NO_NL     10
#define KEY_QUIT_L          'q'
#define KEY_QUIT_U          'Q'

const char *choices[] =
{
    "New file"  ,
    "Open file" ,
    "Save file" ,
    "Exit"      
};

int main()
{
    initscr();
    curs_set(0);
    cbreak();
    noecho();
    keypad(stdscr, true);

    bool term_has_colors = has_colors();

    if(term_has_colors)
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    }

    int num_of_choices = sizeof(choices) / sizeof(choices[0]);
    int highlight = 0;  // Holds the index of the choice to be highlighted.
    int ch;

    // Print the menu, by setting first option as highlighted by default, then let the user decide while waiting
    // for it to press either arrow or ENTER.
    while(true)
    {
        clear();

        // Print all menu items.
        for(int i = 0; i < num_of_choices; i++)
        {
            // If the option index is equal to the one to be highlighted, then do so. Otherwise, just print with no attribute it.
            if(highlight == i)
            {
                term_has_colors ? attron(COLOR_PAIR(1)) : attron(A_BOLD | A_UNDERLINE);
                mvprintw(i + 1, 2, "%s", choices[i]);
                term_has_colors ? attroff(COLOR_PAIR(1)) : attroff(A_BOLD | A_UNDERLINE);
            }
            else
            {
                mvprintw(i + 1, 2, "%s", choices[i]);
            }
        }

        // Add a footer to tell the user what to do.
        mvprintw(num_of_choices + 2, 2, MSG_USAGE);
        refresh();

        // Wait until a key is pressed, then act in consequence.
        ch = getch();
        switch(ch)
        {
            // Pressing up/down keys will result in changing the option to highlight.
            // Always take care of any possible integer overflow.
            case KEY_UP:
            {
                highlight = (highlight - 1 + num_of_choices) % num_of_choices;
            }
            break;

            case KEY_DOWN:
            {
                highlight = (highlight + 1) % num_of_choices;
            }
            break;

            // If ENTER has been pressed, then show the chosen option and exit.
            case KEY_ENTER:
            case KEY_ENTER_NO_NL:
            {
                clear();
                mvprintw(2, 2, MSG_CHOSEN_OPTION, choices[highlight]);
                refresh();
                getch();
                endwin();
                return 0;
            }
            break;

            // If q/Q has been pressed, then simply exit.
            case KEY_QUIT_L:
            case KEY_QUIT_U:
            {
                endwin();
                return 0;
            }
            break;
        }
    }

    endwin();

    return 0;
}