# Flags to give to the C preprocessor
CPPFLAGS =
# Program for compiling C++ programs; default g++
CXX = g++
# Program for compiling C programs; default cc
CC = g++
# Flags to give to the C++ compiler
CXXFLAGS = -Wall -g
# Flags to give to compilers when they are supposed to invoke the linker
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS := $(wildcard *.cpp) 			  # Finds all .cpp files
OBJS := $(patsubst %.cpp,%.o,$(SRCS)) # Replaces .cpp with .o

Main: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del *.exe
	del *.o