CXX = g++

INCLUDES = -I./include

OBJDIR = ./obj

CPPFLAGS = -Wall -std=c++11 $(INCLUDES)

LIBS = -lSDL2

# SRCS = main.cpp game.cpp gameObject.cpp brick.cpp brickgrid.cpp paddle.cpp ball.cpp
SRCS = $(wildcard src/*.cpp)

# OBJS = $(SRCS:.cpp=.o)
OBJS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))

MAIN = game

.PHONY: clean directories

all: directories $(MAIN)
	@echo  Compiled successfully.

directories: ${OBJDIR}

${OBJDIR}:
	mkdir -p ${OBJDIR}

$(MAIN): $(OBJS) 
	$(CXX) $(CPPFLAGS) -o $(MAIN) $(OBJS) $(LIBS)

$(OBJDIR)/%.o: src/%.cpp
	$(CXX) $(CPPFLAGS) -c $<  -o $@
clean:
	$(RM) $(OBJDIR)/*.o *~ $(MAIN)