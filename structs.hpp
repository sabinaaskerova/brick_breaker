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
} size;

enum typeBrick {
    NORMAL,
    DOUBLE,
    TRIPLE
};