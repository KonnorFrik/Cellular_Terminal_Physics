#include "field.h"
#include "cell_types.h"

static void destroy_cell_matrix(CELL*** obj, size_t rows, size_t columns);
static void destroy_cell_array(CELL** obj, size_t size);
static CELL*** get_cell_matrix(size_t rows, size_t columns);
static CELL** get_cell_arr(size_t size);

//static void print_field(Field* obj);

void init_field(Field* obj) {
    for (size_t r = 0; r < obj->rows; ++r) {
        for (size_t c = 0; c < obj->columns; ++c) {
            obj->field[r][c]->type = NONE;
            obj->field[r][c]->symbol = NONE_SYMB;
        }
    }
}

//static void print_field(Field* obj) {
    //for (size_t r = 0; r < obj->rows; ++r) {
        //for (size_t c = 0; c < obj->columns; ++c) {
            //printf("X: %d; Y: %d\n", obj->field[r][c]->x, obj->field[r][c]->y);
        //}
    //}
//}
//

static CELL** get_cell_arr(size_t size) {
    CELL** res = calloc(size, sizeof(CELL*));

    for (size_t i = 0; i < size; ++i) {
        res[i] = calloc(1, sizeof(CELL));
    }

    return res;
}

static CELL*** get_cell_matrix(size_t rows, size_t columns) {
    CELL*** obj = calloc(rows, sizeof(CELL**));

    for (size_t r = 0; obj != 0 && r < rows; ++r) {
        obj[r] = get_cell_arr(columns);
    }

    return obj;
}

static void destroy_cell_array(CELL** obj, size_t size) {
    if (obj) {
        for (size_t i = 0; i < size; ++i) {
            if (obj[i]) {
                free(obj[i]);
            }
        }

        free(obj);
    }
}

static void destroy_cell_matrix(CELL*** obj, size_t rows, size_t columns) {
    if (obj) {
        for (size_t r = 0; r < rows; ++r) {
            if (obj[r]) {
                destroy_cell_array(obj[r], columns);
            }
        }

        free(obj);
    }
}

Field* get_field(size_t rows, size_t columns) {
    Field* obj = calloc(1, sizeof(Field));

    if (obj) {
        obj->rows = rows;
        obj->columns = columns;
        obj->field = get_cell_matrix(rows, columns);
    }

    return obj;
}

void destroy_field(Field* obj) {
    if (obj) {
        if (obj->field) {
            destroy_cell_matrix(obj->field, obj->rows, obj->columns);
        }

        free(obj);
    }
}

//int main() {
    //size_t rows = 3;
    //size_t columns = 3;
    //Field* fld = get_field(rows, columns);
    //init_field(fld);
    //print_field(fld);
    //destroy_field(fld);
    //return 0;
//}
