#include "field.h"
#include "cell_types.h"
#include "../common.h"

#define FLD_DEBUG 0
#if FLD_DEBUG == 1
#include <stdio.h>
#endif

void water_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (curr_row + 1 < field->rows && field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empty
        cell_swap(&(field->field[curr_row + 1][curr_col]),
                  &(field->field[curr_row][curr_col]));

    } else if (curr_col > 0 && field->field[curr_row][curr_col - 1]->type == NONE ) { // not a next to border cell
        cell_swap(&(field->field[curr_row][curr_col]),
                  &(field->field[curr_row][curr_col - 1]));

    } else if (curr_col + 1 < field->rows && field->field[curr_row][curr_col + 1]->type == NONE) {
            cell_swap(&(field->field[curr_row][curr_col]),
                      &(field->field[curr_row][curr_col + 1]));
    }
}

//void none_rule(Field* field, size_t curr_rows, size_t curr_col) {
    //return;
//}
