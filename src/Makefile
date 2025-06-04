CC=gcc
CFLAGS=-Wall -Wextra -Werror -Wpedantic -std=c11
CHECK_FLAGS = $(shell pkg-config --cflags --libs check)

.PHONY: all clean rebuild

all: my_cat my_cat_tests 

clean: 
	rm -f my_cat my_cat_test

rebuild: clean all

my_cat:
	$(CC) $(CFLAGS) cat.c -o my_cat

my_cat_tests: my_cat
	$(CC) $(CFLAGS) ../tests/test_cat.c -o my_cat_test $(CHECK_FLAGS) 