#include "cursor.h"

void cursor_check_limit(Cursor* cursor) {
    if (cursor-> x < 0) {
        cursor->x = 0;
    }

    if (cursor-> y <= 0) {
        cursor->y = 1;
    }

    if (cursor->x >= cursor->x_limit) {
        cursor->x = cursor->x_limit - 1;
    }

    if (cursor->y >= cursor->y_limit) {
        cursor->y = cursor->y_limit - 1;
    }
}

