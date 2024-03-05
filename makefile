# Definir el compilador
CC=gcc

# Definir los archivos fuente y archivos objeto
SRCS=merge_sort.c generate_random_numbers.c clone.c parallel_merge_sort.c vector_mode.c main.c
OBJS=$(SRCS:.c=.o)

# Definir el nombre del ejecutable
TARGET=main.exe

# Regla de compilación
%.o: %.c
		$(CC) -c $< -o $@

# Regla de enlace
$(TARGET): $(OBJS)
		$(CC) $(OBJS) -o $(TARGET)

# Regla predeterminada
all: $(TARGET)

# Limpiar los archivos objeto y ejecutable
clean:
		rm -f $(OBJS) $(TARGET)

# PHONY targets
.PHONY: all clean
