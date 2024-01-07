#ifndef __COMMON_FUNCS_H__
#define __COMMON_FUNCS_H__

#include <termios.h>
#include <fcntl.h>

int kbhit();
void cell_swap(CELL** from_addr, CELL** to_addr);

#endif
