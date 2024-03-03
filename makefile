# Define compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Define source files
SRC = generate_random_numbers.c merge_sort.c clone.c parallel_merge_sort.c vector_mode.c main.c

# Define object files
OBJ = $(SRC:.c=.o)

# Define default target
all: main

# Define main target and dependencies
main: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o main

# Compilation rule for each source file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Define clean target to remove object files and main executable
clean:
	rm -f $(OBJ) main
