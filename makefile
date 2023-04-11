#############################################################
#  Variables
#############################################################
CPPFLAGS =#			 Flags to give to the C preprocessor
CXX      = g++#		 Program for compiling C++ programs; default g++
CC       = g++#		 Program for compiling C programs; default cc
CXXFLAGS = -Wall -g# Flags to give to the C++ compiler

# Flags to give to compilers when they are supposed to invoke the linker
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = src/$(wildcard *.cpp)# 				Finds all .cpp files
OBJS = $(patsubst %.cpp,%.o,$(SRCS))#	Replaces .cpp with .o

#############################################################
#  Build Targets
#############################################################
Main: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del *.exe
	del *.o