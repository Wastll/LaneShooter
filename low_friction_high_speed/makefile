# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and object files (recursive)
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
BIN = $(BUILD_DIR)/lane_shooter

# Libraries (Linux example)
LIBS = -lraylib -lm -ldl -lpthread -lGL -lrt -lX11

# Default target
all: $(BIN)

# Link
$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $@ $(LIBS)

# Compile with directory creation
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BIN)
