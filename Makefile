.RECIPEPREFIX = >
.PHONY := all

cmp = gcc
wflags = -Wall -Werror -Wextra
flags = -std=c11 -c -g

src_dirs = . paint field cursor common fast_commands
SRC = $(foreach dir, $(src_dirs), $(wildcard $(dir)/*.c))
OBJ = $(SRC:.c=.o)

targets = physics
all: $(targets) clean

physics: $(OBJ)
> $(cmp) $(OBJ) -o $@

%.o: %.c
> $(cmp) $(wflags) $(flags) $? -o $@

clean:
> rm -f $(OBJ)

clean_all: clean
> rm -f $(targets)

show:
> @echo $(SRC)
> @echo $(OBJ)
