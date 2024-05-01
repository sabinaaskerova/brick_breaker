#ifndef STRUCTS_H
#define STRUCTS_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define WALLSW 600
#define WALLSH 800
#define WALLSX ((SCREEN_WIDTH - WALLSW) / 2)
#define WALLSY ((SCREEN_HEIGHT - WALLSH) / 2)

#define BRICKW 35
#define INITX (WALLSX) + (BRICKW)
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



typedef struct position {
  double x;
  double y;
  position() : x(0), y(0) {}  // Default constructor
  position(double x_, double y_)
      : x(x_), y(y_) {}  // TO DO: use the constructor wherever possible
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

// struct Hex {  // Cube storage, axial constructor
//   const int q, r, s;
//   Hex(int q_, int r_) : q(q_), r(r_), s(-q_ - r_) {}
// };

// struct Orientation {
//   const double f0, f1, f2, f3;
//   const double b0, b1, b2, b3;
//   const double start_angle;  // in multiples of 60°
//   Orientation(double f0_, double f1_, double f2_, double f3_, double b0_,
//               double b1_, double b2_, double b3_, double start_angle_)
//       : f0(f0_),
//         f1(f1_),
//         f2(f2_),
//         f3(f3_),
//         b0(b0_),
//         b1(b1_),
//         b2(b2_),
//         b3(b3_),
//         start_angle(start_angle_) {}
// };
// const Orientation layout_flat =
//     Orientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0), 2.0 / 3.0, 0.0,
//                 -1.0 / 3.0, sqrt(3.0) / 3.0, 0.0);

// struct Layout {
//   const Orientation orientation;
//   const position size;
//   const position origin;
//   Layout(Orientation orientation_, position size_, position origin_)
//       : orientation(orientation_), size(size_), origin(origin_) {}
// };

#endif // STRUCTS_H