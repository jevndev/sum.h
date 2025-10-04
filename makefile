# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra

# Directories
BUILD_DIR = build

# Files
TARGET = $(BUILD_DIR)/main
SRC = main.c

# Make sure build directory exists
$(shell mkdir -p $(BUILD_DIR))

all: $(TARGET)

preprocess:
	$(CC) -E $(CFLAGS) $(SRC) -o $(BUILD_DIR)/main.i

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean preprocess
