# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -std=c99

# Linker flags for Raylib
LDFLAGS = -lraylib -lm -ldl -lpthread -lGL -lX11

# Source and output
SRC = src/main.c
OUT = ./build/LaneShooter

# Default build
all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Clean build files
clean:
	rm -f $(OUT)
