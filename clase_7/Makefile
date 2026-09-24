# Compiler
CC = g++

# Compiler flags
CCFLAGS = -Wall -O3

# Source files
SOURCES = main.cpp

# Output executable
OUTPUT = out

# Build target
all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CC) $(CCFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm -f $(OUTPUT)
