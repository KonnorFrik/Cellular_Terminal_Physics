#define _DEFAULT_SOURCE // for legacy usleep func
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "field/cell_types.h"
#include "field/field.h"
#include "field/rules.h"
#include "common.h"

#define TRM_DEBUG 0
#define FPS (30 * 1500)

void print_field(Field* field) {
    for (size_t r = 0; r < field->rows; ++r) {
        for (size_t c = 0; c < field->columns; ++c) {
            printf(field->field[r][c]->symbol);
            field->field[r][c]->status = NOT_UPDATED;
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
                    if (field->field[r][c]->status == NOT_UPDATED) {
                        field->field[r][c]->status = UPDATED;
                        water_rule(field, r, c);
                    }
                    break;
            }
        }

        printf("\n");
    }
}

int process_pressed_key() {
    char symb = getc(stdin);
    int work_status = 1;

    switch (symb) {
        case 'q':
        case 'Q':
            work_status = 0;
            break;
    }

    return work_status;
}

void update_loop(Field* field) {
    int work = 1;

    while (work) {
        if (kbhit()) {
            work = process_pressed_key();
        }

        update_rule(field);

        clear_screen();
        print_field(field);

        usleep(FPS);
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
