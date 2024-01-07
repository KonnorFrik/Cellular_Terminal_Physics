#ifndef __FIELD_H__
#define __FIELD_H__

#include <stdlib.h>

typedef struct {
    char* symbol;
    int type;
    int status;
} CELL;

typedef struct {
    CELL*** field;
    size_t rows;
    size_t columns;
} Field;

void destroy_field(Field* obj);
Field* get_field(size_t rows, size_t columns);

#endif
