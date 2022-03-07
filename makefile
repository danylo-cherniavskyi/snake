FLAGS = -g -Wall -Wextra -pedantic
LIBS = -lncurses
SOURCES = main.c funcs.c threads.c

snake: $(SOURCES)
	$(CC) $(SOURCES) -o snake $(FLAGS) $(LIBS)

exec: snake
	./snake