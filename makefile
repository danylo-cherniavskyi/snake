FLAGS = -Wall -Wextra -pedantic
SOURCES = main.c someWinFuncs.c funcs.c

snake: $(SOURCES)
	$(CC) $(SOURCES) -o snake $(FLAGS)