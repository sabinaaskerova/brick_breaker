#ifndef STRUCTS_H
#define STRUCTS_H
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