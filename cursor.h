#ifndef __CURSOR_H__
#define __CURSOR_H__

#define CURSOR_SYMBOL "\u2593"

#define CURSOR_LEFT_KEY 'h'
#define CURSOR_RIGHT_KEY 'l'
#define CURSOR_UP_KEY 'k'
#define CURSOR_DOWN_KEY 'j'
#define CURSOR_SET_TYPE 's'
#define CURSOR_SPAWN_ELEM ' '

typedef struct {
    size_t x;
    size_t y;
    int hand;
    char* symbol;
    size_t x_limit;
    size_t y_limit;
} Cursor;

#endif
