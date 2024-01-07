.RECIPEPREFIX = >

cmp = gcc
wflags = -Wall -Werror -Wextra
flags = -std=c11 #-g

src_dirs = . paint
SRC := $(foreach dir, $(src_dirs), $(wildcard $(dir)/*.c))
OBJ := $(SRC:.c=.o)

%.o: %.c
> $(cmp) $(wflags) $(flags) $? -o $@

show:
> @echo $(SRC)
> @echo $(OBJ)
