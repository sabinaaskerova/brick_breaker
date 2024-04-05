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
    public:
        Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel);
        Ball(position& pos, objectSize& size, velocity& vel);
        ~Ball() override;
        void update() override;
        void render() override;
        void collidesWith(GameObject* obj) override;
        void setVelocityX(int);
        void setVelocityY(int);
        const velocity& getVelocity();
        bool isMoving();
        void setMoving(bool);
};
#endif // BALL_H