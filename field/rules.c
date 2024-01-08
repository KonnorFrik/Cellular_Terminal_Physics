#include "field.h"
#include "cell_types.h"
#include "../common/common.h"

#define FLD_DEBUG 0
#if FLD_DEBUG == 1
#include <stdio.h>
#endif
void sand_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (curr_row + 1 < field->rows && field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empty
        cell_swap(&(field->field[curr_row + 1][curr_col]),
                  &(field->field[curr_row][curr_col]));
    }
}

void water_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (curr_row + 1 < field->rows && field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empty
        cell_swap(&(field->field[curr_row + 1][curr_col]),
                  &(field->field[curr_row][curr_col]));

    } else if (curr_col > 0 && curr_col + 1 < field->columns) { // random left right move
        if (rand() % 2 == 0 && field->field[curr_row][curr_col - 1]->type == NONE) { // move left
            cell_swap(&(field->field[curr_row][curr_col]),
                    &(field->field[curr_row][curr_col - 1]));
        } else if (field->field[curr_row][curr_col + 1]->type == NONE) { // move right
                cell_swap(&(field->field[curr_row][curr_col]),
                        &(field->field[curr_row][curr_col + 1]));
        }

    // if it's left border -> move right
    } else if (curr_col == 0) { // field->field[curr_row][curr_col - 1]->type == NONE ) { // not a next to border cell
        cell_swap(&(field->field[curr_row][curr_col]),
                  &(field->field[curr_row][curr_col + 1]));

    } else if (curr_col == field->columns) { // && field->field[curr_row][curr_col + 1]->type == NONE) {
            cell_swap(&(field->field[curr_row][curr_col]),
                      &(field->field[curr_row][curr_col - 1]));
    }
}

