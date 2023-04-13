#############################################################
# Variables
#############################################################
CPPFLAGS =#			Flags for the C preprocessor
CXX      = g++#		Program for compiling C++ programs; default g++
CC       = gcc#		Program for compiling C programs; default cc
CXXFLAGS =-Wall#	Flags for the C++ compiler

# Flags for compilers when they invoke the linker
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DIR = build#	Directory where build files go
SRC_DIR   = src#	Directory where the source files are

# Finds all .cpp files in ./src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Replaces .cpp with .o and SRC_DIR with BUILD_DIR
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

#############################################################
# Build Targets
#############################################################

# Links all .o files in BUILD_DIR
$(BUILD_DIR)/Main: $(BUILD_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compiles every source file into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

test:
	@echo $(SRCS)
	@echo $(OBJS)

clean:
	rm -rf $(BUILD_DIR)/*