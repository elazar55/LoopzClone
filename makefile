#############################################################
# Variables
#############################################################
CPPFLAGS =#			Flags for the C preprocessor
CXX      = g++#		Program for compiling C++ programs; default g++
CC       = gcc#		Program for compiling C programs; default cc
CXXFLAGS =-Wall#	Flags for the C++ compiler

# Flags for compilers when they invoke the linker
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DIR = bin#	Directory where build files go
SRC_DIR   = src#	Directory where the source files are

# Finds all .cpp files in ./src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Finds all .h files in ./src/
HEADS = $(wildcard $(SRC_DIR)/*.h)

# Replaces .cpp with .o and SRC_DIR with BUILD_DIR
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable extension
ifeq ($(OS),Windows_NT)
	EXT = .exe
endif

# Final executable which is the name of the parent folder + /build
EXE = $(BUILD_DIR)/$(notdir $(shell pwd))$(EXT)

#############################################################
# Build Targets
#############################################################
all: $(EXE)

# Links all .o files in BUILD_DIR
# Header files included only for recompiling changes
$(EXE): $(BUILD_DIR) $(OBJS) $(HEADS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compiles every source file into .o files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

test:
	@printf "Source files:\n"
	@printf "%s\n" $(SRCS)
	@printf "\nHeader files:\n"
	@printf "%s\n" $(HEADS)
	@printf "\nObject files:\n"
	@printf "%s\n" $(OBJS)
	@printf "\nExecutable:\n"
	@printf "%s\n" $(EXE)
	@printf "\nOperating System:\n"
	@printf "%s\n" $(OS)

clean:
	rm -rf $(BUILD_DIR)/