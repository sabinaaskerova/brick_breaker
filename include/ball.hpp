#ifndef BALL_H
#define BALL_H
#include "gameObject.hpp"
#include "structs.hpp"

class Ball: public GameObject
{
    private:
        velocity m_velocity;
        bool m_moving;
        int m_x;
        int m_y;
        bool m_gameStarted;
        
        void setVelocity(velocity);
    public:
        Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel);
        Ball(position& pos, objectSize& size, velocity& vel);
        ~Ball() override;
        void init(SDL_Renderer *renderer, int x, int y);
        void update() override;
        void render() override;
        void draw(SDL_Renderer* renderer) override;
        
        void collidesWith(GameObject* obj) override;
        void setVelocityX(int);
        void setVelocityY(int);
        const velocity& getVelocity();
        bool isMoving();
        void setMoving(bool);
};
#endif // BALL_H