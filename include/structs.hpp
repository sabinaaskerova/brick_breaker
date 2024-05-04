/**
 * @file structs.hpp
 * @author Sabina Askerova
 * @brief This file contains the structures used in the game
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

#define WALLSW 600  // the width of the area inside the walls
#define WALLSH 800  // the height of the area inside the walls
// the x coordinate of the top left corner of the area inside the walls
#define WALLSX ((SCREEN_WIDTH - WALLSW) / 2)
// the y coordinate of the top left corner of the area inside the walls
#define WALLSY ((SCREEN_HEIGHT - WALLSH) / 2)

// the width of the bricks
#define BRICKW 35
// the x coordinate of the top left corner of the first brick
#define INITX (WALLSX) + (BRICKW)
// the y coordinate of the top left corner of the first brick
#define INITY (WALLSY) + (BRICKW)

#define PADDLEW 100
#define PADDLEH 30
#define PADDLEX (WALLSW-PADDLEW)/2 + WALLSX
#define PADDLEY (WALLSY + WALLSH - PADDLEH) - 40

#define BALLSIZE 25
#define BALLX PADDLEX + PADDLEW/2 - BALLSIZE/2
#define BALLY PADDLEY - BALLSIZE
#define BALLSPEED 8

#define BOOSTSIZE BALLSIZE
#define BOOSTDURATION 5000 
#define BOOSTSPEED 2000

#define GRIDN 7

typedef struct position {
  double x;
  double y;
  position() : x(0), y(0) {}  // Default constructor
  position(double x_, double y_)
      : x(x_), y(y_) {}  // TO DO: use the constructor wherever possible
  position operator-(const position& other) const {
    return position{x - other.x, y - other.y};
  }
  double length() const { return std::sqrt(x * x + y * y); }
} position;


typedef struct velocity {
    double x;
    double y;
} velocity;

typedef struct size {
  double width;
  double height;
} objectSize;

enum typeBrick {
    NORMAL,
    DOUBLE,
    TRIPLE,
    EMPTY
};


enum class BoostType {
    MultiBall,
    WidePaddle,
    NarrowPaddle
};

struct Color {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
};

#endif // STRUCTS_H