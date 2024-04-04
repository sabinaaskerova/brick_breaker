#ifndef PADDLE_H
#define PADDLE_H
#include "gameObject.hpp"
// #include "structs.hpp"

class Paddle: public GameObject{
    private:
        int m_width;
        void setWidth(int);
    public:
        Paddle(SDL_Renderer* renderer, position pos, objectSize size, int speed);
        ~Paddle();
        void update();
        void render();
        void collidesWith(GameObject* obj);
        void move(int);
        const int& getWidth();
};


#endif // PADDLE_H