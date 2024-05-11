#ifndef BALL_H
#define BALL_H
#include "gameObject.hpp"
#include "structs.hpp"
#include "brick.hpp"

class Ball: public GameObject
{
    private:
        velocity m_velocity;
        bool m_gameStarted;
        
    public:
        Ball(SDL_Renderer* renderer, const position& pos, const objectSize& size, const velocity& vel);
        Ball(position& pos, objectSize& size, velocity& vel);
        ~Ball() override;
        void init(SDL_Renderer *renderer, double x, double y);
        void update() override;
        void draw(SDL_Renderer* renderer) override;
        
        bool collidesWith(const GameObject& obj) const override;
        
        void setVelocityX(double x);
        void setVelocityY(double y);
        void setPositionX(double x);
        void setPositionY(double y);
        
        double getVelocityX() const;
        double getVelocityY() const;
        const velocity& getVelocity() const;
};
#endif // BALL_H