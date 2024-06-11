CC = gcc
CFLAGS = -ggdb3 -Wall -Wextra -lm -pedantic -I./src  -lpthread   -fsanitize=address

SRCDIR = src
BUILDDIR = build
CLI_SRC = cli_src/src
FILTERS = "main.c|test.c"
CLI_FILES:=$(shell find $(CLI_SRC) -type f -iname '*.c' | grep -Ev $(FILTERS))
CLI_OBJS =  $(CLI_FILES:.c=.o)

EXECUTABLE = $(BUILDDIR)/exe.exe

memmng:memmng.c
	gcc -o $(EXECUTABLE) memmng.c $(args)

mmg:memmng




%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) $(DEFINES) $(PROFILER) $(CFLAGS)

# chess
chess: $(CLI_OBJS) chess.c
	gcc $(CFLAGS)  $^ -o $@ $(LIBS)  $(PROFILER) $(CFLAGS)

run:
	./$(EXECUTABLE) $^ $@

r:run
clean:
	@rm -rf $(BUILDDIR)/*
	@find ./* -type f -iname *.o -exec rm {} \; 
	@find  $(CLI_SRC) -type f -iname *.o -exec rm {} \; 

.PHONY: all clean d