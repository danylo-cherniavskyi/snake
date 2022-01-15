FLAGS = -g -Wall -Wextra -pedantic
LIBS = -lncurses -lpthread
SOURCES = main.c funcs.c

snake: $(SOURCES)
	$(CC) $(SOURCES) -o snake $(FLAGS) $(LIBS)

exec: snake
	./snake