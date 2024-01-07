#include <sys/ioctl.h>

#define TRM_DEBUG 0

#if TRM_DEBUG == 1
#include <stdio.h>
#endif

int main() {
    struct winsize w_size = {0};
    ioctl(0, TIOCGWINSZ, &w_size);

    size_t win_rows = w_size.ws_row;
    size_t win_cols = w_size.ws_col;

    #if TRM_DEBUG == 1
    fprintf(stderr, "rows: %u\n", w_size.ws_row);
    fprintf(stderr, "cols: %u\n", w_size.ws_col);
    fprintf(stderr, "X pixels: %u\n", w_size.ws_xpixel);
    fprintf(stderr, "Y pixels: %u\n", w_size.ws_ypixel);
    #endif

    return 0;
}
