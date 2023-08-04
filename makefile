# ============================================================================ #
#                                   Variables                                  #
# ============================================================================ #
CPPFLAGS	=#					Flags for the C preprocessor
CXX			=	g++#			Program for compiling C++ programs; default g++
CC			=	gcc#			Program for compiling C programs; default cc
ASM			=	nasm#			Program for compiling ASM programs
ASMFLAGS	=	-fwin64#		Flags for the ASM compiler
CXXFLAGS	=	-Wall\
				-march=native\
				-g3#			Flags for the C++ compiler
LDFLAGS		=	-lsfml-graphics\
				-lsfml-window\
				-lsfml-system#	Flags for compilers when they invoke the linker

BUILD_DIR	=	build#							Directory where build files go
SRC_DIR		=	src#							Source files directory
CPP_SRCS	=	$(wildcard $(SRC_DIR)/*.cpp)#	Match all .cpp files in ./src/
ASM_SRCS	=	$(wildcard $(SRC_DIR)/*.asm)#	Match all .asm files in ./src/

# Replaces .cpp with .o and SRC_DIR with BUILD_DIR
OBJS	=	$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
OBJS	+=	$(patsubst $(SRC_DIR)/%.asm,$(BUILD_DIR)/%.o,$(ASM_SRCS))
DEPS	=	$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(CPP_SRCS))

ifeq ($(OS),Windows_NT)# Executable extension
	EXT = .exe
endif

# Final executable target which is the name of the parent folder + $(BUILD_DIR)
EXE = $(BUILD_DIR)/$(notdir $(shell pwd))$(EXT)

# ============================================================================ #
#                                 Build Targets                                #
# ============================================================================ #
.PHONY: all
all: $(EXE)

# Links all .o files in BUILD_DIR
$(EXE): $(BUILD_DIR) $(SRC_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# Compiles every source file into .o files and generates dependency files to
# trigger recompilation if headers change.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Same as above for assembly
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	$(ASM) $(ASMFLAGS) -MD -MP $< -o $@

# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Creates SRC_DIR if it doesn't exist
$(SRC_DIR):
	mkdir $(SRC_DIR)

.PHONY: test
test:
	@printf "\nOperating System: %s\n\n" $(OS)

	@printf "CXXFLAGS: "
	@printf "%s " $(CXXFLAGS)

	@printf "\n\nCPP_SRCS:\n"
	@printf "%s\n" $(CPP_SRCS)

	@printf "\nASM_SRCS:\n"
	@printf "%s\n" $(ASM_SRCS)

	@printf "\nOBJS:\n"
	@printf "%s\n" $(OBJS)

	@printf "\nDEPS:\n"
	@printf "%s\n" $(DEPS)

	@printf "\nEXE: "
	@printf "%s \n" $(EXE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want
# those errors to show up
-include $(DEPS)
