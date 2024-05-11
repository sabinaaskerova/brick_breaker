#include "boost.hpp"
#include "paddle.hpp"
#include <iostream>
Boost::Boost(SDL_Renderer* renderer, const position pos, const objectSize size,
             const velocity speed, const Uint32 duration)
    : GameObject(renderer, pos, size),
      m_duration(duration),
      m_activation_time(SDL_GetTicks()) {
  m_speed = speed;
}

Boost::~Boost(){
}
void Boost::update()
{
    m_position.y += 1;
}
bool Boost::collidesWith(const GameObject& obj)  const {
  if (dynamic_cast<const Paddle*>(&obj)) {
    SDL_Rect boostBox = getBoundingBox();
    SDL_Rect paddleBox = obj.getBoundingBox();
    return SDL_HasIntersection(&boostBox, &paddleBox);
  } else {
    return false;
  }
}

bool Boost::isActive(Uint32 current_time) const {
    if (m_activation_time == 0) {
        return false;
    }
    return current_time <= (m_activation_time + m_duration);
}

void Boost::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

BonusMultiBall::BonusMultiBall(SDL_Renderer* renderer, const position pos,
                               const objectSize size, const velocity speed,
                               const Uint32 duration)
    : Boost(renderer, pos, size, speed, duration) {}

BonusMultiBall::~BonusMultiBall(){
}


void BonusMultiBall::update()
{
    m_position.y += 1;
}

void BonusMultiBall::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;

    SDL_Surface* tempSurface = IMG_Load("./img/ball_yellow.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

BonusWidePaddle::BonusWidePaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration) : Boost(renderer, pos, size, speed, duration)
{
}
BonusWidePaddle::~BonusWidePaddle(){
}

void BonusWidePaddle::update()
{
    m_position.y += 1;
}

void BonusWidePaddle::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_Surface* tempSurface = IMG_Load("./img/ball_green.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

MalusNarrowPaddle::MalusNarrowPaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration) : Boost(renderer, pos, size, speed, duration)
{
}
MalusNarrowPaddle::~MalusNarrowPaddle(){
}


void MalusNarrowPaddle::update()
{
    m_position.y += 1;
}

void MalusNarrowPaddle::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;

    SDL_Surface* tempSurface = IMG_Load("./img/ball_red.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}
