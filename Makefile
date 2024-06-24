# Compiler
CXX = g++

# Source files
SRC = main.cpp \
      src/include/boids/boid_item.cpp \
      src/include/pVector/pVector.cpp \
      src/include/screen/screen.cpp \
      src/include/flocking/flocking.cpp

# Include directories
INC_DIR = -I src/include

# Library directories and libraries
LIB_DIR = -L src/lib
LIBS = -lmingw32 -lSDL2main -lSDL2

# Output executable
OUTPUT = Test

# Targe
all:
	$(CXX) $(SRC) $(INC_DIR) $(LIB_DIR) $(LIBS) -o $(OUTPUT)
