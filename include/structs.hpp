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
#define BALLSPEED 5

typedef struct position {
    double x;
    double y;
} position;


typedef struct velocity {
    double x;
    double y;
} velocity;

typedef struct size {
    int width;
    int height;
} objectSize;

enum typeBrick {
    NORMAL,
    DOUBLE,
    TRIPLE,
    EMPTY
};

#endif // STRUCTS_H