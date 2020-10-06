// First, i call the libraries i need
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// This structure allows the program
// to hide the shell and start the console
// as a blank screen
struct termios orig_termios;

// This function disables de Raw mode when we
// Press Q to exit the program
void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

// This one activates the Raw mode
// when we start the program
void enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    enableRawMode();

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
        return 0;
}