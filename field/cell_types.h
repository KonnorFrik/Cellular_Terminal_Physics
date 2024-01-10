#ifndef __CELL_TYPES_H__
#define __CELL_TYPES_H__

#define NONE_SYMB " "
#define WATER_SYMB "~"
#define SAND_SYMB "\u25A0"

enum { // types
    NONE = 0,
    WATER,
    SAND,
};

enum { // statuses
    NOT_UPDATED = 0,
    UPDATED,
};

enum {
    NOT_COLORED = 0,
    COLORED,
};

#endif
