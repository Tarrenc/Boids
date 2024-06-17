# Compiler
CXX = g++

# Source files
SRC = main.cpp \
      boids/boid_item.cpp \
      pVector/pVector.cpp \
      screen/screen.cpp \
      flocking/flocking.cpp

# Include directories
INC_DIR = -I src/include

# Library directories and libraries
LIB_DIR = -L src/lib
LIBS = -lmingw32 -lSDL2main -lSDL2

# Output executable
OUTPUT = Test

# Target
all:
	$(CXX) $(SRC) $(INC_DIR) $(LIB_DIR) $(LIBS) -o $(OUTPUT)
