/**
 * @file structs.hpp
 * @author Sabina Askerova
 * @brief This file contains the structures used in the game
 *
 */
#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>

const int SCREEN_WIDTH =  1000;
const int SCREEN_HEIGHT = 1000;

const int WALLSW = 600;  /**< The width of the area inside the walls. */
const int WALLSH = 800;  /**< The height of the area inside the walls. */
// the x coordinate of the top left corner of the area inside the walls
const int WALLSX = ((SCREEN_WIDTH - WALLSW) / 2);
// the y coordinate of the top left corner of the area inside the walls
const int WALLSY = ((SCREEN_HEIGHT - WALLSH) / 2);

// the width of the bricks
const int BRICKW = 35;
// the x coordinate of the top left corner of the first brick
const int INITX = (WALLSX) + (BRICKW);
// the y coordinate of the top left corner of the first brick
const int INITY = (WALLSY) + (BRICKW);

const int PADDLEW = 100;
const int PADDLEH = 30;
const int PADDLEX = (WALLSW-PADDLEW)/2 + WALLSX;
const int PADDLEY =(WALLSY + WALLSH - PADDLEH) - 40;

const int BALLSIZE = 25;
const int BALLX = PADDLEX + PADDLEW/2 - BALLSIZE/2;
const int BALLY = PADDLEY - BALLSIZE;
const int BALLSPEED = 8;

const int BOOSTSIZE = BALLSIZE;
const int BOOSTDURATION = 5000;
const int BOOSTSPEED = 2000;

const int GRIDN = 7;

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