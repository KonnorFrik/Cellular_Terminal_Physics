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
#include "common/common.h"
#include "cursor/cursor.h"
#include "fast_commands/f_commands.h"

#define TRM_DEBUG 0
#define FPS (30 * 1000)

#define QUIT_KEY 'q'
#define FAST_COMMAND_KEY 'e'
#define INFO_KEY 'i'

#if TRM_DEBUG == 1
void print_status(Cursor* cursor);
#endif

void print_field(Field* field, Cursor* cursor);
void update_rule(Field* field);
int get_type_from_user();
void spawn_elem(Field* field, const Cursor* cursor);
int process_pressed_key(Field* field, Cursor* cursor);
void update_loop(Field* field, Cursor* cursor);
void init_cursor(Cursor* obj, size_t win_rows, size_t win_cols);

static void print_help_message(size_t offset);
static void print_hello_msg(size_t offset);
static void print_tab(size_t count);


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

                case SAND:
                    if (field->field[r][c]->status == NOT_UPDATED) {
                        field->field[r][c]->status = UPDATED;
                        sand_rule(field, r, c);
                    }

                    break;
            }
        }

        printf("\n");
    }
}

int get_type_from_user() {
    int result = 0;
    int last_max_elem = 0;
    int loop = 1;

    clear_screen();

    while (loop) {
        printf("Select new item:\n");
        size_t ind = 0;

        while (TABLE[ind].name != 0) {
            printf("\t%2d - %s\n", TABLE[ind].type, TABLE[ind].name);
            last_max_elem = ind;
            ind++;
        }

        printf("\t-1 - Exit\n");

        int input = 0;
        scanf("%d", &input);

        if (input > last_max_elem || input == 0) {
            printf("\nYou choose invalid element\n\n");
            getc(stdin);
            continue;

        } else {
            result = input;
            loop = 0;
        }
    }

    return result;
}

void spawn_elem(Field* field, const Cursor* cursor) {
    int new_type = cursor->hand;
    char* new_symbol = TABLE[new_type].symbol;
    char* new_color = TABLE[new_type].color;

    if (field->field[cursor->y][cursor->x]->color_status) {
        free(field->field[cursor->y][cursor->x]->symbol);
        field->field[cursor->y][cursor->x]->color_status = NOT_COLORED;
    }

    field->field[cursor->y][cursor->x]->type = new_type;
    field->field[cursor->y][cursor->x]->symbol = color(new_symbol, new_color);
    field->field[cursor->y][cursor->x]->color_status = COLORED;
}

int process_pressed_key(Field* field, Cursor* cursor) {
    char symb = getc(stdin);
    int work_status = 1;

    switch (symb) {
        case QUIT_KEY:
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
            int user_input = get_type_from_user();

            if (user_input == -1) {
                user_input = cursor->hand;
            }

            cursor->hand = user_input;
            break;

        case CURSOR_SPAWN_ELEM:
            spawn_elem(field, cursor);
            break;

        case FAST_COMMAND_KEY:
            process_fast_command(field);
            break;

        case INFO_KEY:
            size_t offset = (cursor->x_limit / 2) - 13;
            clear_screen();
            print_help_message(offset);
            getc(stdin);
            break;
    }

    return work_status;
}

#if TRM_DEBUG == 1
void print_status(Cursor* cursor) {
    printf("X: %d | Y: %d | Xlim: %d | Ylim: %d | hand: %s\n", cursor->x, cursor->y, cursor->x_limit, cursor->y_limit, TABLE[cursor->hand].name);
}
#endif

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

static void print_tab(size_t count) {
    for (size_t i = 0; i < count; ++i) {
        printf(" ");
    }
}

static void print_hello_msg(size_t offset) {
    print_tab(offset);
    printf("+-------------------------+\n");
    print_tab(offset);
    printf("|    Welcome to Termycs   |\n");
    print_tab(offset);
    printf("|    (Terminal Physics)   |\n");
    print_tab(offset);
    printf("+-------------------------+\n");
}

static void print_help_message(size_t offset) {
    printf("\n");
    print_tab(offset);
    printf("+-------------------------+\n");
    print_tab(offset);
    printf("|          Keys:          |\n");
    print_tab(offset);
    printf("|- - - - - Move - - - - - |\n");
    print_tab(offset);
    printf("|    h    - Move left     |\n");
    print_tab(offset);
    printf("|    j    - Move down     |\n");
    print_tab(offset);
    printf("|    k    - Move up       |\n");
    print_tab(offset);
    printf("|    l    - Move right    |\n");
    print_tab(offset);
    printf("|- - - - Control- - - - - |\n");
    print_tab(offset);
    printf("|    s    - Switch element|\n");
    print_tab(offset);
    printf("| 'space' - Spawn element |\n");
    print_tab(offset);
    printf("|    e    - Fast command  |\n");
    print_tab(offset);
    printf("|    i    - Help message  |\n");
    print_tab(offset);
    printf("|    q    - Quit          |\n");
    print_tab(offset);
    printf("+-------------------------+\n");
}

int main() {
    srand(time(0));
    struct winsize w_size = {0};
    ioctl(0, TIOCGWINSZ, &w_size);

    size_t win_rows = w_size.ws_row;
    size_t win_cols = w_size.ws_col;
    size_t msg_offset = (win_cols / 2) - 13;

    clear_screen();
    print_hello_msg(msg_offset);
    print_help_message(msg_offset);
    print_tab(msg_offset);
    printf("*Press enter for start\n");
    getc(stdin);

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
