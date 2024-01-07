#ifndef __TERM_PAINT_H__
#define __TERM_PAINT_H__

#define PNT_DEBUG 0

#if PNT_DEBUG == 1
#include <stdio.h>
#endif

#include <string.h>
#include <stdlib.h>

#define RESET "\033[39m\033[49m"

#define FORE_RED "\033[38;2;255;1;1m"
#define FORE_GREEN "\033[38;2;1;255;1m"
#define FORE_BLUE "\033[38;2;1;1;255m"

#define BACK_RED "\033[48;2;255;1;1m"
#define BACK_GREEN "\033[48;2;1;255;1m"
#define BACK_BLUE "\033[48;2;1;1;255m"

#endif
