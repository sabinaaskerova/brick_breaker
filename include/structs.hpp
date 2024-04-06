#ifndef STRUCTS_H
#define STRUCTS_H

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define WALLSW 600
#define WALLSH 900
#define WALLSX ((SCREEN_WIDTH - WALLSW) / 2)
#define WALLSY ((SCREEN_HEIGHT - WALLSH) / 2)
#define INITX (WALLSX) +35 
#define INITY (WALLSY)+35

typedef struct position {
    int x;
    int y;
} position;


typedef struct velocity {
    int x;
    int y;
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