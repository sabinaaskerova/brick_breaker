CXX = g++-11

INCLUDES = -I./include 

OBJDIR = ./obj

CPPFLAGS = -Wall -std=c++14 $(INCLUDES) -I/usr/include/SDL2 
# CXXFLAGS = -std=c++14 -Wall -Wextra  $(INCLUDES) -pedantic

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

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