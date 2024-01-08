#include "field.h"
#include "cell_types.h"
#include "../common/common.h"

//#if FLD_DEBUG == 1
//fprintf(stderr, "[FLD_DEBUG] Move col + 1:\n");
//#endif

enum {
    LEFT = 0,
    RIGHT,
};

#define FLD_DEBUG 0
#if FLD_DEBUG == 1
#include <stdio.h>
#endif

void sand_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (!(curr_row + 1 < field->rows)) {
        return;
    }

    if (field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empty
        cell_swap(&(field->field[curr_row + 1][curr_col]),
                  &(field->field[curr_row][curr_col]));

    } else { // random left right move
        if (rand() % 2 == 0 && curr_col > 0 && (field->field[curr_row + 1][curr_col - 1]->type == NONE)) { // move left
            cell_swap(&(field->field[curr_row][curr_col]),
                    &(field->field[curr_row + 1][curr_col - 1]));

        } else if (curr_col < field->columns - 1 && field->field[curr_row + 1][curr_col + 1]->type == NONE) { // move right
            cell_swap(&(field->field[curr_row][curr_col]),
                    &(field->field[curr_row + 1][curr_col + 1]));
        }

    }
}

void water_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (curr_row + 1 < field->rows && field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empty
        cell_swap(&(field->field[curr_row + 1][curr_col]),
                  &(field->field[curr_row][curr_col]));

    } else if (curr_col > 0 && curr_col < field->columns - 1) { // random left right move
        if (rand() % 2 == LEFT && field->field[curr_row][curr_col - 1]->type == NONE) { // move left
            cell_swap(&(field->field[curr_row][curr_col]),
                    &(field->field[curr_row][curr_col - 1]));

        } else if (field->field[curr_row][curr_col + 1]->type == NONE) { // move right
                cell_swap(&(field->field[curr_row][curr_col]),
                        &(field->field[curr_row][curr_col + 1]));
        }

    } else if ((field->columns - curr_col) == 1) { // right border
        cell_swap(&(field->field[curr_row][curr_col]),
                  &(field->field[curr_row][curr_col - 1]));

    } else if (curr_col == 0) { // left border
            cell_swap(&(field->field[curr_row][curr_col]),
                      &(field->field[curr_row][curr_col + 1]));
    }
}

