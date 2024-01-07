#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "field/cell_types.h"
#include "field/field.h"
#include "field/rules.h"

#define TRM_DEBUG 0
#define FPS 2//30


void print_field(Field* field) {
    for (size_t r = 0; r < field->rows; ++r) {
        for (size_t c = 0; c < field->columns; ++c) {
            printf(field->field[r][c]->symbol);
        }

        printf("\n");
    }
}

void update_rule(Field* field) {
    for (size_t r = 0; r < field->rows; ++r) {
        for (size_t c = 0; c < field->columns; ++c) {
            switch (field->field[r][c]->type) {
                case NONE:
                    break;

                case WATER:
                    water_rule(field, r, c);
                    break;
            }
        }

        printf("\n");
    }
}

void update_loop(Field* field) {
    int work = 1;

    while (work) {
        update_rule(field);
        print_field(field);
        printf("> ");
        getc(stdin);
        //sleep(FPS);
    }
}

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

    Field* field = get_field(win_rows, win_cols);
    init_field(field);

    field->field[win_rows / 2][win_cols / 2]->type = WATER;
    field->field[win_rows / 2][win_cols / 2]->symbol = WATER_SYMB;

    update_loop(field);
    destroy_field(field);

    return 0;
}
