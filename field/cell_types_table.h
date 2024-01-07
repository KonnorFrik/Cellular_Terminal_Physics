#ifndef __CELL_TYPES_TABLE_H__
#define __CELL_TYPES_TABLE_H__

typedef struct {
    int type;
    char* name;
} Table;

const Table TABLE[] = {
    {NONE, "NONE"},
    {WATER, "Water"},
    {0, 0},
};

#endif
