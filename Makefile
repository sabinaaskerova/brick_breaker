CXX = g++-11

INCLUDES = -I./include 

OBJDIR = ./obj

CPPFLAGS = -Wall -std=c++14 $(INCLUDES) -I/usr/include/SDL2

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_gfx

SRCS = $(wildcard src/*.cpp)

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

docs : 
	doxygen Doxyfile

clean:
	$(RM) $(OBJDIR)/*.o *~ $(MAIN)