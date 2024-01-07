#define _DEFAULT_SOURCE // for legacy usleep func
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "field/cell_types.h"
#include "field/cell_types_table.h"
#include "field/field.h"
#include "field/rules.h"
#include "paint/paint.h"
#include "common.h"
#include "cursor.h"

#define TRM_DEBUG 0
#define FPS (30 * 1000)

#define QUIT_KEY_LOWER 'q'
#define QUIT_KEY_UPPER 'Q'

void print_field(Field* field, Cursor* cursor) {
    for (size_t r = 0; r < field->rows; ++r) {
        for (size_t c = 0; c < field->columns; ++c) {
            if ((size_t)cursor->x == c && (size_t)cursor->y == r) {
                printf(cursor->symbol);

            } else {
                printf(field->field[r][c]->symbol);
                field->field[r][c]->status = NOT_UPDATED;
            }
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

void cursor_check_limit(Cursor* cursor) {
    if (cursor-> x < 0) {
        cursor->x = 0;
    }

    if (cursor-> y <= 0) {
        cursor->y = 1;
    }

    if (cursor->x >= cursor->x_limit) {
        cursor->x = cursor->x_limit - 1;
    }

    if (cursor->y >= cursor->y_limit) {
        cursor->y = cursor->y_limit - 1;
    }
}

int get_type_from_user() {
    int result = 0;
    size_t ind = 0;
    int last_max_elem = 0;
    int loop = 1;

    clear_screen();

    while (loop) {
        printf("Select new item:\n");

        while (TABLE[ind].name != 0) {
            printf("\t%d - %s\n", TABLE[ind].type, TABLE[ind].name);
            last_max_elem = TABLE[ind].type;
            ind++;
        }

        int input = 0;
        scanf("%d", &input);

        if (input > last_max_elem) {
            printf("\nYou choose invalid element\n\n");
            continue;

        } else {
            result = input;
            loop = 0;
        }
    }

    return result;
}

void spawn_elem(Field* field, Cursor* cursor) {
    int new_type = cursor->hand;
    char* new_symbol = NONE_SYMB;
    char* new_color = RESET;

    switch (new_type) {
        case NONE:
            new_symbol = NONE_SYMB;
            new_color = RESET;
            break;

        case WATER:
            new_symbol = WATER_SYMB;
            new_color = FORE_BLUE;
            break;
    }

    field->field[cursor->y][cursor->x]->type = new_type;
    field->field[cursor->y][cursor->x]->symbol = color(new_symbol, new_color);
}

int process_pressed_key(Field* field, Cursor* cursor) {
    char symb = getc(stdin);
    int work_status = 1;

    switch (symb) {
        case QUIT_KEY_UPPER:
        case QUIT_KEY_LOWER:
            work_status = 0;
            break;

        case CURSOR_LEFT_KEY:
            cursor->x -= 1; 
            cursor_check_limit(cursor);
            break;

        case CURSOR_RIGHT_KEY:
            cursor->x += 1; 
            cursor_check_limit(cursor);
            break;

        case CURSOR_UP_KEY:
            cursor->y -= 1; 
            cursor_check_limit(cursor);
            break;

        case CURSOR_DOWN_KEY:
            cursor->y += 1; 
            cursor_check_limit(cursor);
            break;

        case CURSOR_SET_TYPE:
            cursor->hand = get_type_from_user();
            break;

        case CURSOR_SPAWN_ELEM:
            spawn_elem(field, cursor);
            break;
    }

    return work_status;
}

void update_loop(Field* field, Cursor* cursor) {
    int work = 1;

    while (work) {
        if (kbhit()) {
            work = process_pressed_key(field, cursor);
        }

        update_rule(field);

        clear_screen();
        print_field(field, cursor);

        usleep(FPS);
        //sleep(FPS);
    }
}

void init_cursor(Cursor* obj, size_t win_rows, size_t win_cols) {
    obj->x = win_cols / 2;
    obj->y = win_rows / 2;
    obj->x_limit = win_cols;
    obj->y_limit = win_rows;
    obj->hand = 0;
    obj->symbol = CURSOR_SYMBOL;
}

int main() {
    srand(time(0));
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

    Cursor cursor = {0};
    init_cursor(&cursor, win_rows, win_cols);

    Field* field = get_field(win_rows, win_cols);
    init_field(field);

    update_loop(field, &cursor);
    destroy_field(field);
    clear_screen();

    return 0;
}
