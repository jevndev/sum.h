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

$(TARGET): $(SRC) sum.h
	$(CC) $(CFLAGS) $(SRC) -o $@

clean:
	rm -rf $(BUILD_DIR)

test:
	$(CC) $(CFLAGS) test.c -o $(BUILD_DIR)/test
	$(BUILD_DIR)/test

preprocess_test:
	$(CC) -E $(CFLAGS) test.c -o $(BUILD_DIR)/test.i

.PHONY: all clean preprocess test
