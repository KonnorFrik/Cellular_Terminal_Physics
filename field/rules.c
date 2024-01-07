#include "field.h"

void water_rule(Field* field, size_t curr_row, size_t curr_col) {
    if (curr_row + 1 < field->rows && field->field[curr_row + 1][curr_col]->type == NONE) { // if 1 down is empy
        CELL* tmp = field->field[curr_row + 1][curr_col];
        field->field[curr_row + 1][curr_col] = field->field[curr_row][curr_col];
        field->field[curr_row][curr_col] = tmp;
    }

}

