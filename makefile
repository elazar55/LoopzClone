# ============================================================================ #
#                                   Variables                                  #
# ============================================================================ #
CPPFLAGS =#                 Flags for the C preprocessor
CXX      = g++#             Program for compiling C++ programs; default g++
CC       = gcc#             Program for compiling C programs; default cc
CXXFLAGS = -Wall\
           -march=native\
           -g#              Flags for the C++ compiler
LDFLAGS  = -lsfml-graphics\
           -lsfml-window\
           -lsfml-system#   Flags for compilers when they invoke the linker

BUILD_DIR  = build#                           Build directory
SRC_DIR    = src#                             Source files directory
CPP_FILES  = $(wildcard $(SRC_DIR)/*.cpp)#    Match all .cpp files in ./src/
CPP_FILES += $(wildcard $(SRC_DIR)/**/*.cpp)# Match all .cpp files in ./src/**

# Generate build file list with string substitution
OBJS = $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(CPP_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.d)

# Get just the object file paths so you can create them in advance
OBJ_DIRS :=$(patsubst %/,%,$(dir $(OBJS)))
OBJ_DIRS :=$(filter-out $(BUILD_DIR), $(OBJ_DIRS))

# Append executable extension for Windows
ifeq ($(OS),Windows_NT)
	EXT = .exe
endif

# Final executable target which is the name of the parent folder + $(BUILD_DIR)
EXE = $(BUILD_DIR)/$(notdir $(shell pwd))$(EXT)

.PHONY: all
all: $(BUILD_DIR) $(SRC_DIR) $(OBJ_DIRS) $(EXE)

# Links all .o files
$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compiles every source file into .o files and generates dependency files to
# trigger recompilation if headers change.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Creates SRC_DIR if it doesn't exist
$(SRC_DIR):
	mkdir $(SRC_DIR)

# Creates OBJ_DIRS if they don't exist
$(OBJ_DIRS):
	mkdir $(OBJ_DIRS)

.PHONY: test
test:
	@printf "OS: %s\n" $(OS)
	@printf "EXE: %s\n" $(EXE)

	@printf "CXXFLAGS: "
	@printf "%s " $(CXXFLAGS)

	@printf "\nLDFLAGS: "
	@printf "%s " $(LDFLAGS)

	@printf "\n\nCPP_FILES:\n"
	@printf "%s\n" $(CPP_FILES)

	@printf "\nOBJS:\n"
	@printf "%s\n" $(OBJS)

	@printf "\nDEPS:\n"
	@printf "%s\n" $(DEPS)

	@printf "\nOBJ_DIRS:\n"
	@printf "%s\n" $(OBJ_DIRS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want
# those errors to show up
-include $(DEPS)
