# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directories
SRC_DIR = .
OBJ_DIR = ./obj
BIN_DIR = ./bin
DEVCARD_DIR = ./DevelopmentCards

# Executable names
TARGET = catan_game
TEST_TARGET = test_catan

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
DEVCARD_SRCS = $(wildcard $(DEVCARD_DIR)/*.cpp)
MAIN_SRCS = $(filter-out $(SRC_DIR)/Test.cpp $(SRC_DIR)/Demo.cpp, $(SRCS))
DEMO_SRCS = $(SRC_DIR)/Demo.cpp
TEST_SRCS = $(SRC_DIR)/Test.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(MAIN_SRCS))
DEMO_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(DEMO_SRCS))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SRCS))
DEVCARD_OBJS = $(patsubst $(DEVCARD_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(DEVCARD_SRCS))

# Include directories
INCLUDES = -I$(SRC_DIR) -I$(DEVCARD_DIR)

# Create directories if they don't exist
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Link object files to create the main executable
$(BIN_DIR)/$(TARGET): $(OBJS) $(DEMO_OBJS) $(DEVCARD_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(DEMO_OBJS) $(DEVCARD_OBJS) -o $@

# Link object files to create the test executable
$(BIN_DIR)/$(TEST_TARGET): $(OBJS) $(TEST_OBJS) $(DEVCARD_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(TEST_OBJS) $(DEVCARD_OBJS) -o $@

# Compile each source file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(DEVCARD_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the catan_game executable
catan: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

# Run the test executable
test: $(BIN_DIR)/$(TEST_TARGET)
	./$(BIN_DIR)/$(TEST_TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TEST_TARGET)

# Phony targets
.PHONY: all clean catan test
