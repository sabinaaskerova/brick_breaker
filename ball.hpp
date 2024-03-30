#ifndef BALL_H
#define BALL_H
#include "gameObject.hpp"
#include "structs.hpp"

class Ball: public GameObject
{
    private:
        velocity m_velocity;
        bool m_moving;
        void setVelocity(velocity);
        void setMoving(bool);
    public:
        Ball(SDL_Renderer* renderer, position pos, size size, velocity vel);
        ~Ball();
        void update();
        void render();
        void collidesWith(GameObject* obj);
        void setVelocityX(int);
        void setVelocityY(int);
        const velocity& getVelocity();
        bool isMoving();
        void setMoving(bool);
};
#endif // BALL_H