#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <string>

#define MSG_WELCOME     "Welcome! Enter your name: "
#define MSG_GAME_HEADER "Player: %s | Score: %d | Press 'q' to quit"

#define CHAR_ALPHABET_BASE  'A'
#define CHAR_QUIT_GAME      'q'
#define CHAR_CATCHER        '^'

#define SIZE_NAME       30
#define SIZE_ALPHABET   26

int main()
{
    // 1 - Init ncurses. Enable arrows and show cursor on screen while avoiding echo
    // (manually typed characters will not be displayed).
    initscr();
    keypad(stdscr, true);
    noecho();
    curs_set(1);

    // 2 - Print welcome message and promp the user for a name to be inputted. "echo"
    // must be enabled again since user should be able to see anything that's being typed
    // on the keyboard. Finally, disable echo again and set the cursor to default position.
    mvprintw(0, 0, MSG_WELCOME);
    char name[SIZE_NAME];
    echo();                         // Enable echo for the user to see what's typed.
    getnstr(name, SIZE_NAME - 1);   // Gets a string from the user (which size could be at most SIZE_NAME - 1 in this case). Same as getch but with a whole string.
    noecho();                       // Disable echo once typed string has been stored.
    curs_set(0);

    // 3 - Setup game.
    timeout(200);                   // Set typing delay: waits 200 ms for the following characters to be received. Goes ahead unconditionally.
    srand(time(NULL));
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);   // Get boundary coordinates for current screen.

    int catcherX = maxX / 2;        // Catcher position.
    int fallX = rand() % maxX;
    int fallY = 1;
    char fallingChar = CHAR_ALPHABET_BASE + rand() % SIZE_ALPHABET;
    int score = 0;

    // 4 - Game loop. Same as in 3rd lesson, evaluates each typed characters acting in
    // consequence depending on whether the character in question is equal to 'q' or not.
    int ch;
    while( (ch = getch()) != CHAR_QUIT_GAME )
    {
        clear();

        // Draw header.
        mvprintw(0, 0, MSG_GAME_HEADER, name, score);

        // Handle input.
        if(ch == KEY_LEFT && catcherX > 0)  // If left arrow is pressed and left X boundary has not been reached yet, then move cursor leftwards.
            --catcherX;
        if(ch == KEY_RIGHT && catcherX < maxX - 1)  // If right arrow is pressed and right X boundary has not been reached yet, then move cursor rightwards.
            ++catcherX;
        if(ch == fallingChar)   // Typed the character that's currently falling.
        {
            ++score;
            fallY = 1;
            fallX = rand() % maxX;
            fallingChar = CHAR_ALPHABET_BASE + rand() % SIZE_ALPHABET;
        }

        mvaddch(fallY, fallX, fallingChar);         // Draw falling character.
        mvaddch(maxY - 1, catcherX, CHAR_CATCHER);  // Draw catcher.
        
        // Move falling character.
        ++fallY;

        // Check if bottom has been reached.
        if(fallY >= maxY - 1)
        {
            if(fallX == catcherX) // Check whether catcher was coincidentally in falling character's position.
                ++score;
            else
                --score;
            
            fallY = 1;
            fallX = rand() % maxX;
            fallingChar = CHAR_ALPHABET_BASE + rand() % SIZE_ALPHABET;
        }

        refresh();
    }

    endwin();

    return 0;
}