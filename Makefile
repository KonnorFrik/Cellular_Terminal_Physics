.RECIPEPREFIX = >

cmp = gcc
wflags = -Wall -Werror -Wextra
flags = -std=c11 -c -g

src_dirs = . paint field
SRC = $(foreach dir, $(src_dirs), $(wildcard $(dir)/*.c))
OBJ = $(SRC:.c=.o)

targets = physics

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
