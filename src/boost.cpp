#include "boost.hpp"
#include "paddle.hpp"

Boost::Boost(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration)
: GameObject(renderer, pos, size), m_duration(duration)
{
    m_speed = speed;
}

Boost::~Boost(){
}
void Boost::update()
{
    m_position.y += 1;
}
bool Boost::collidesWith(const GameObject& obj)  const {
    if (const Paddle* paddle = dynamic_cast<const Paddle*>(&obj)) {
        SDL_Rect boostBox = getBoundingBox();
        SDL_Rect paddleBox = obj.getBoundingBox();
        return SDL_HasIntersection(&boostBox, &paddleBox);
    } else{
        return false;
    }
}
void Boost::render()
{
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}


void Boost::draw(SDL_Renderer* renderer){}

BonusMultiBall::BonusMultiBall(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration) : Boost(renderer, pos, size, speed, duration)
{
}


BonusMultiBall::~BonusMultiBall(){
}


void BonusMultiBall::update()
{
    m_position.y += 1;
}
// take into account : finish the game when no balls are left before this verification
bool BonusMultiBall::collidesWith(const GameObject& other) const {
    if (const Paddle* paddle = dynamic_cast<const Paddle*>(&other)) {
        

    } 
}

void BonusMultiBall::render()
{
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

void BonusMultiBall::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_RenderCopy(renderer, m_image, NULL, &dest);
}

void BonusMultiBall::applyBoost(){
    //m_paddle->setSpeed(m_paddle->getSpeed() + 1);
}


