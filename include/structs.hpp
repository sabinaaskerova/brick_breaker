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
const int WALLSX =
    ((SCREEN_WIDTH - WALLSW) / 2); /**the x coordinate of the top left corner of
                                      the area inside the walls */
const int WALLSY =
    ((SCREEN_HEIGHT - WALLSH) / 2); /**the y coordinate of the top left corner
                                       of the area inside the walls*/

const int BRICKW = 35; /**the width of the bricks*/
const int INITX =
    (WALLSX) +
    (BRICKW); /**the x coordinate of the top left corner of the first brick*/
const int INITY =
    (WALLSY) +
    (BRICKW); /**the y coordinate of the top left corner of the first brick*/

const int PADDLEW = 100; /** the width of the paddle*/
const int PADDLEH = 30;  /** the height of the paddle*/
const int PADDLEX = (WALLSW - PADDLEW) / 2 +
                    WALLSX; /** the initial x coordinate of the paddle*/
const int PADDLEY = (WALLSY + WALLSH - PADDLEH) -
                    40; /** the initial y coordinate of the paddle*/

const int BALLSIZE = 25; /** the size of the ball*/
const int BALLX = PADDLEX + PADDLEW / 2 -
                  BALLSIZE / 2;       /** the initial x coordinate of the ball*/
const int BALLY = PADDLEY - BALLSIZE; /** the initial y coordinate of the ball*/
const int BALLSPEED = 8;              /** the speed of the ball*/

const int BOOSTSIZE = BALLSIZE; /** the size of the boost*/
const int BOOSTDURATION = 5000; /** the duration of the boost*/
const int BOOSTSPEED = 2000;    /** the speed of the boost*/

const int GRIDN = 7; /** the number of grids*/
/**
 * @struct position
 * @brief Represents a 2D position with x and y coordinates.
 */

typedef struct position {
  double x; /**< The x-coordinate. */
  double y; /**< The y-coordinate. */
  position() : x(0), y(0) {}
  position(double x_, double y_) : x(x_), y(y_) {}
  position operator-(const position& other) const {
    return position{x - other.x, y - other.y};
  }
  double length() const { return std::sqrt(x * x + y * y); }
} position;

/**
 * @struct velocity
 * @brief Represents a 2D velocity with x and y components.
 */
typedef struct velocity {
  double x; /**< The velocity along the x-axis. */
  double y; /**< The velocity along the y-axis. */
} velocity;
/**
 * @struct size
 * @brief Represents the width and height of an object.
 */
typedef struct size {
  double width;  /**< The width of the object. */
  double height; /**< The height of the object. */
} objectSize;
/**
 * @enum typeBrick
 * @brief Enumeration of brick types.
 */
enum typeBrick {
  NORMAL, /**< Normal brick. */
  DOUBLE, /**< Double brick. */
  TRIPLE, /**< Triple brick. */
  EMPTY   /**< Empty brick. */
};
/**
 * @enum BoostType
 * @brief Enumeration of boost types.
 */
enum class BoostType {
  MultiBall,   /**< Multi-ball boost. */
  WidePaddle,  /**< Wide paddle boost. */
  NarrowPaddle /**< Narrow paddle boost. */
};
/**
 * @struct Color
 * @brief Represents a color with RGBA components.
 */
struct Color {
  Uint8 r; /**< The red component. */
  Uint8 g; /**< The green component. */
  Uint8 b; /**< The blue component. */
  Uint8 a; /**< The alpha component. */
};

#endif // STRUCTS_H