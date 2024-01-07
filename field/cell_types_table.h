#ifndef __CELL_TYPES_TABLE_H__
#define __CELL_TYPES_TABLE_H__

#include "cell_types.h"
#include "../paint/paint.h"

typedef struct {
    int type;
    char* symbol;
    char* name;
    char* color;
} Table;

const Table TABLE[] = {
    {NONE, NONE_SYMB, "NONE", RESET},
    {WATER, WATER_SYMB, "Water", FORE_BLUE},
    {SAND, SAND_SYMB, "Sand", FORE_YELLOW},
    {0, 0, 0, 0},
};

#endif
