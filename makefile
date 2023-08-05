# ============================================================================ #
#                                   Variables                                  #
# ============================================================================ #
CPPFLAGS	=#					Flags for the C preprocessor
CXX			=	g++#			Program for compiling C++ programs; default g++
CC			=	gcc#			Program for compiling C programs; default cc
CXXFLAGS	=	-Wall\
				-march=native\
				-g3#			Flags for the C++ compiler
LDFLAGS		=	-lsfml-graphics\
				-lsfml-window\
				-lsfml-system#	Flags for compilers when they invoke the linker

BUILD_DIR	=	build#							Build directory
SRC_DIR		=	src#							Source files directory
CPP_FILES	=	$(wildcard $(SRC_DIR)/*.cpp)#	Match all .cpp files in ./src/

# Generate build file list with string substitution
OBJS	=	$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))
DEPS	=	$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.d,$(CPP_FILES))

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

# ============================================================================ #
#                                  Executable                                  #
# ============================================================================ #
# Links all .o files in BUILD_DIR
$(EXE): $(BUILD_DIR) $(SRC_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# ============================================================================ #
#                                 Object Files                                 #
# ============================================================================ #
# Compiles every source file into .o files and generates dependency files to
# trigger recompilation if headers change.
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ============================================================================ #
#                                  Directories                                 #
# ============================================================================ #
# Creates BUILD_DIR if it doesn't exist
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Creates SRC_DIR if it doesn't exist
$(SRC_DIR):
	mkdir $(SRC_DIR)

# ============================================================================ #
#                                Print Variables                               #
# ============================================================================ #
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

# ============================================================================ #
#                                     Clean                                    #
# ============================================================================ #
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

# ============================================================================ #
#                                 Dependencies                                 #
# ============================================================================ #
# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want
# those errors to show up
-include $(DEPS)
