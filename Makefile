CC = gcc
CFLAGS = -Wall -Wextra -I./include

# 1. Update the list of source files to include src/main.c
SRC = src/tcp.c src/main.c

# 2. This automatically converts all .c files in the SRC list to .o files
OBJ = $(SRC:.c=.o)
TARGET = server

all: $(TARGET)

# 3. Link all the object files together to create the binary
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)