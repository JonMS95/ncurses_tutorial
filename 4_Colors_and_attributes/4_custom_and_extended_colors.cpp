#include <ncurses.h>

// Ncurses was originally designed back when terminals had just 8 colors, but modern terminals
// can handle way more colors than those: 256 or even 24 bit truecolor. Ncurses lets you access
// some of these features depending on how your terminal and ncurses are built. Also, it lets
// the user custom its very own colors. If true colors are featured within the program, then
// --enable-ext-colors flag may need to be used at compile-time.

// These arrays below will store default color values.
short saved_r[8], saved_g[8], saved_b[8];

void save_defaults()
{
    for (int i = 0; i < 8; i++)
    {
        color_content(i, &saved_r[i], &saved_g[i], &saved_b[i]);
    }
}

void restore_defaults() {
    for (int i = 0; i < 8; i++) {
        init_color(i, saved_r[i], saved_g[i], saved_b[i]);
    }
}

int main()
{
    initscr();
    curs_set(0);
    noecho();
    cbreak();

    if(!has_colors())
        return -1;
    
    start_color();

    // Check if the terminal lets color customization. The function in questions gets a color +
    // red, green and blue values for it.
    if(can_change_color())
    {
        save_defaults();
        
        clear();

        init_pair(1, COLOR_RED, COLOR_BLACK);

        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "Original COLOR_RED.");
        attroff(COLOR_PAIR(1));

        refresh();
        getch();

        // Turn default red color into pinkish.
        init_color(COLOR_RED, 1000, 500, 500);

        clear();

        attron(COLOR_PAIR(1));
        mvprintw(1, 1, "Modified COLOR_RED.");
        attroff(COLOR_PAIR(1));

        refresh();

        getch();

        // Call use_default_colors to reset to default colors again.
        restore_defaults();
    }

    // If your terminal supports 256 colors (as most modern ones do), then color constnts are
    // extended to 0-255, where:
    // ·0-7:        standard colors.
    // ·8-15:       brighter versions.
    // ·16-231:     6 x 6 x 6 RGB cube.
    // ·232-255:    grayscale ramp. 

    init_pair(1, 196, 0);           // Bright red.
    init_pair(2, COLOR_RED, 0);     // Default red.
    init_pair(3, 46, 0);            // Bright green.
    init_pair(4, COLOR_GREEN, 0);   // Default green.
    init_pair(5, 21, 0);            // Bright blue.
    init_pair(6, COLOR_BLUE, 0);    // Default blue.

    clear();

    attron(A_BOLD | COLOR_PAIR(1));
    mvprintw(1, 1, "Bright red.");
    attroff(A_BOLD | COLOR_PAIR(1));

    attron(A_BOLD | COLOR_PAIR(2));
    mvprintw(2, 1, "Default red.");
    attroff(A_BOLD | COLOR_PAIR(2));

    attron(A_BOLD | COLOR_PAIR(3));
    mvprintw(3, 1, "Bright green.");
    attroff(A_BOLD | COLOR_PAIR(3));

    attron(A_BOLD | COLOR_PAIR(4));
    mvprintw(4, 1, "Default green.");
    attroff(A_BOLD | COLOR_PAIR(4));

    attron(A_BOLD | COLOR_PAIR(5));
    mvprintw(5, 1, "Bright blue.");
    attroff(A_BOLD | COLOR_PAIR(5));

    attron(A_BOLD | COLOR_PAIR(6));
    mvprintw(6, 1, "Default blue.");
    attroff(A_BOLD | COLOR_PAIR(6));

    refresh();

    getch();

    // // True color is supported on some ncurses build experimentally in 6.1+ versions.
    // init_extended_color(33, 255, 178, 102); // Orange-ish (33 is just an ID).
    // init_extended_pair(7, 33, COLOR_BLACK);

    // clear();

    // attron(COLOR_PAIR(7));
    // mvprintw(1, 1, "Custom orange true color.");
    // attroff(COLOR_PAIR(7));

    // refresh();

    endwin();

    return 0;
}