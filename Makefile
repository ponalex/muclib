# Makefile

CC = gcc
CFLAGS = -Wall -fPIC -pedantic
LIBS = -shared
TARGET = 
SRC = $(wildcard muclib/*.c)
TEST_PREFIX = test_

# .PHONY: all clean
#
# all: $(TARGET)

# Rule for creating so file
lib: $(SRC)
	$(CC) $(CFLAGS) $(LIBS) -o muclib.so $(SRC)

# Rule for compiling project from source code
elf: main.c
	$(CC) -o main main.c $(SRC) -g

# Rule for creating tests with information for debugging
$(TEST_PREFIX)%: $(TEST_PREFIX)%.c
	$(CC) -o $(@).o $< -Lmuclib $(SRC) $(CFLAGS) -g -fsanitize=leak

# The main rule 
%:
	@echo "Unknown target: $@"
	@echo "Available targets: lib, exe, test"

clean:
	rm -f muclib.so main test_*.o
