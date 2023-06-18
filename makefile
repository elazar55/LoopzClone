# ============================================================================ #
#                                   Variables                                  #
# ============================================================================ #
CPPFLAGS =#			Flags for the C preprocessor
CXX      = g++#		Program for compiling C++ programs; default g++
CC       = gcc#		Program for compiling C programs; default cc
CXXFLAGS =-Wall#	Flags for the C++ compiler
ASM      = nasm#	Program for compiling ASM programs
ASMFLAGS =-fwin64#	Flags for the ASM compiler

# Flags for compilers when they invoke the linker
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DIR = build#							Directory where build files go
SRC_DIR   = src#							Directory where the source files are
CPP_SRCS  = $(wildcard $(SRC_DIR)/*.cpp)#	Finds all .cpp files in ./src/
ASM_SRCS  = $(wildcard $(SRC_DIR)/*.asm)#	Finds all .cpp files in ./src/

# Replaces .cpp with .o and SRC_DIR with BUILD_DIR
OBJS  = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
OBJS += $(patsubst $(SRC_DIR)/%.asm,$(BUILD_DIR)/%.o,$(ASM_SRCS))
DEPS  = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(CPP_SRCS))

ifeq ($(OS),Windows_NT)# Executable extension
	EXT = .exe
endif

# Final executable target which is the name of the parent folder + $(BUILD_DIR)
EXE = $(BUILD_DIR)/$(notdir $(shell pwd))$(EXT)

# ============================================================================ #
#                                 Build Targets                                #
# ============================================================================ #
all: $(EXE)

# Links all .o files in BUILD_DIR
$(EXE): $(BUILD_DIR) $(SRC_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compiles every source file into .o files and generates dependency files to
# trigger recompilation if headers change.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	$(ASM) $(ASMFLAGS) -MD -MP $< -o $@

# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	
# Creates SRC_DIR if it doesn't exist
$(SRC_DIR):
	mkdir $(SRC_DIR)

test:
	@printf "CPP Source files:\n"
	@printf "%s\n" $(CPP_SRCS)
	@printf "\nASM Source files:\n"
	@printf "%s\n" $(ASM_SRCS)
	@printf "\nObject files:\n"
	@printf "%s\n" $(OBJS)
	@printf "\nDepend files:\n"
	@printf "%s\n" $(DEPS)
	@printf "\nExecutable:\n"
	@printf "%s\n" $(EXE)
	@printf "\nOperating System:\n"
	@printf "%s\n" $(OS)

clean:
	rm -rf $(BUILD_DIR)/

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want
# those errors to show up
-include $(DEPS)