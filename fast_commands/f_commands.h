#ifndef __FAST_COMMANDS_H__
#define __FAST_COMMANDS_H__

#include "../field/field.h"
#include "../field/cell_types.h"
#include "../common/common.h"
#include <stdio.h>
#include <stdlib.h>

enum { // Commands codes
    CLEAR = 1,
};

//int get_fast_command_input();
void process_fast_command(Field* field);

#endif
