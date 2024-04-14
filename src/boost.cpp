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
// take into account : finish the game when no balls are left BEFORE this verification
bool BonusMultiBall::collidesWith(const GameObject& other) const {
    if (const Paddle* paddle = dynamic_cast<const Paddle*>(&other)) {
        

    } 
}

void BonusMultiBall::render()
{
}

void BonusMultiBall::draw(SDL_Renderer* renderer){
    SDL_SetRenderDrawColor(m_renderer, 144, 255, 117, 255); 
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;

    SDL_Surface* tempSurface = IMG_Load("./img/ball.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

void BonusMultiBall::applyBoost(){
    //m_paddle->setSpeed(m_paddle->getSpeed() + 1);
}

BonusWidePaddle::BonusWidePaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration) : Boost(renderer, pos, size, speed, duration)
{
}
BonusWidePaddle::~BonusWidePaddle(){
}

void BonusWidePaddle::applyBoost(){
    //m_paddle->setSize(m_paddle->getSize().width + 10, m_paddle->getSize().height);
}
void BonusWidePaddle::update()
{
    m_position.y += 1;
}
bool BonusWidePaddle::collidesWith(const GameObject& other) const {
    if (const Paddle* paddle = dynamic_cast<const Paddle*>(&other)) {
        SDL_Rect boostBox = getBoundingBox();
        SDL_Rect paddleBox = other.getBoundingBox();
        return SDL_HasIntersection(&boostBox, &paddleBox);
    } else{
        return false;
    }
}
void BonusWidePaddle::render()
{
}
void BonusWidePaddle::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;
    SDL_Surface* tempSurface = IMG_Load("./img/ball.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}

MalusNarrowPaddle::MalusNarrowPaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration) : Boost(renderer, pos, size, speed, duration)
{
}
MalusNarrowPaddle::~MalusNarrowPaddle(){
}

void MalusNarrowPaddle::applyBoost(){
    //m_paddle->setSize(m_paddle->getSize().width - 10, m_paddle->getSize().height);
}
void MalusNarrowPaddle::update()
{
    m_position.y += 1;
}

bool MalusNarrowPaddle::collidesWith(const GameObject& other) const {
    if (const Paddle* paddle = dynamic_cast<const Paddle*>(&other)) {
        SDL_Rect boostBox = getBoundingBox();
        SDL_Rect paddleBox = other.getBoundingBox();
        return SDL_HasIntersection(&boostBox, &paddleBox);
    } else{
        return false;
    }
}
void MalusNarrowPaddle::render()
{
}
void MalusNarrowPaddle::draw(SDL_Renderer* renderer){
    SDL_Rect dest;
    dest.x = m_position.x;
    dest.y = m_position.y;
    dest.w = m_size.width;
    dest.h = m_size.height;

    SDL_Surface* tempSurface = IMG_Load("./img/ball.png");
    m_image = SDL_CreateTextureFromSurface(m_renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_RenderCopy(m_renderer, m_image, NULL, &dest);
}