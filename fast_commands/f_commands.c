#include "f_commands.h"

static int get_fast_command_input();

void f_cmd_clear(Field* field);

typedef struct {
    int cmd_type;
    char* name;
    void (*func)(Field* field);
} F_CMD_TABLE;

const F_CMD_TABLE f_cmd_table[] = {
    {0, 0, 0},
    {CLEAR, "Clear all", f_cmd_clear},
    {0, 0, 0}
};

static int get_fast_command_input() {
    int result = 0;
    int loop = 1;

    clear_screen();

    while (loop) {
        int ind = 1;
        int last_max_elem = ind;
        printf("Choose action:\n");

        while (f_cmd_table[ind].name != 0) {
            printf("\t%2d - %s\n", f_cmd_table[ind].cmd_type, f_cmd_table[ind].name);
            last_max_elem = ind;
            ind++;
        }

        printf("\t-1 - Exit\n");

        int input = 0;
        scanf("%d", &input);

        if (input > last_max_elem || input == 0) {
            printf("\n\t\tInvalid Input\n");
            getc(stdin);

        } else {
            result = input;
            loop = 0;
        }
    }

    return result;
}

void process_fast_command(Field* field) {
    int command_input = get_fast_command_input();;

    if (command_input != -1) {
        f_cmd_table[command_input].func(field);
    }
}

void f_cmd_clear(Field* field) {
    for (size_t r = 0; r < field->rows; ++r) {
        for (size_t c = 0; c < field->columns; ++c) {
            if (field->field[r][c]->color_status) {
                free(field->field[r][c]->symbol);
                field->field[r][c]->color_status = NOT_COLORED;
            }

            field->field[r][c]->type = NONE;
            field->field[r][c]->symbol = NONE_SYMB;
            field->field[r][c]->status = NOT_UPDATED;
        }
    }
}
