#include "common.h"
#include "field/field.h"

void clear_screen() {
    printf("\033[2J");
}

void cell_swap(CELL** from_addr, CELL** to_addr) {
    CELL* tmp = *from_addr;
    *from_addr = *to_addr;
    *to_addr = tmp;
}

int kbhit() {
    struct termios oldt = {0}, newt = {0};
    int ch = 0;
    int oldf = 0;
    int result = 0;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        result = 1;
    }

    return result;
}
