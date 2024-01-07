#ifndef __CELL_TYPES_H__
#define __CELL_TYPES_H__

#define NONE_SYMB " "
#define WATER_SYMB "~"

enum { // types
    NONE = 0,
    WATER,
};

enum { // statuses
    NOT_UPDATED = 0,
    UPDATED,
};

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
