# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Source files
SOURCES = main.cpp

# Output executable
OUTPUT = out

# Build target
all: $(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm -f $(OUTPUT)
