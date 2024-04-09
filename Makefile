# Define the compiler
CC=gcc

# Define any compile-time flags
CFLAGS=-Wall -Wextra -g

# Define the target executable name
TARGET=UnixLs

# Define source files
SOURCES=UnixLs.c

# Define object files
OBJECTS=$(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Rule for building the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Rule for creating object files from C source files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Phony target for cleaning up the project
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJECTS)
