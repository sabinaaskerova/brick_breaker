#ifndef BALL_H
#define BALL_H
#include "gameObject.hpp"
#include "structs.hpp"

class Ball: public GameObject
{
    private:
        velocity m_velocity;
        bool m_moving;

        bool m_gameStarted;
        
        void setVelocity(velocity);
    public:
        Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel);
        Ball(position& pos, objectSize& size, velocity& vel);
        ~Ball() override;
        void init(SDL_Renderer *renderer, double x, double y);
        void update() override;
        void draw(SDL_Renderer* renderer) override;
        
        bool collidesWith(const GameObject& obj) const override;

        void startGame();
        void setVelocityX(double x);
        void setVelocityY(double y);
        void setPositionX(double x);
        void setPositionY(double y);
        
        double getVelocityX();
        double getVelocityY();
        const velocity& getVelocity();
        bool isMoving();
        void setMoving(bool);
};
#endif // BALL_H