#include "ball.hpp"
#include <iostream>

Ball::Ball(position& pos, objectSize& size, velocity& vel): GameObject(pos, size){
    m_velocity = vel;
    m_moving = false;
    m_gameStarted = false;

}
Ball::Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel): GameObject(renderer, pos, size){
    m_velocity = vel;
    m_moving = false;
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface *image = IMG_Load("./img/ball.png");
    if (!image) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
        
    m_image = SDL_CreateTextureFromSurface(renderer, image);
    if (!m_image) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_FreeSurface(image);
    IMG_Quit();
}

Ball::~Ball()
{
    SDL_DestroyTexture(m_image);
}

void Ball::init(SDL_Renderer *renderer, double x, double y)
{
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface *image = IMG_Load("./img/ball.png");
    if (!image) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
        
    m_image = SDL_CreateTextureFromSurface(renderer, image);
    if (!m_image) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_FreeSurface(image);
    IMG_Quit();

    m_position.x = x;
    m_position.y = y;

    int posX = static_cast<int>(m_position.x);
    int posY = static_cast<int>(m_position.y);

    SDL_QueryTexture(m_image, nullptr, nullptr, &posX, &posY);

    m_velocity.x = 3;
    m_velocity.y = 2;
}

void Ball::update(){
    std::cout << "Ball update" << std::endl;
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
}
void Ball::draw(SDL_Renderer *renderer)
{
    std::cout << "Ball draw" << std::endl;
    SDL_Rect rect;
    std::cout << "Ball position x: " << m_position.x << std::endl;
    rect.x = static_cast<int>(m_position.x);
    std::cout << "Ball position y: " << m_position.y << std::endl;
    rect.y = static_cast<int>(m_position.y);
    std::cout << "Ball size width: " << m_size.width << std::endl;
    rect.w = m_size.width;
    std::cout << "Ball size height: " << m_size.height << std::endl;
    rect.h = m_size.height;

    std::cout << "Ball image: " << m_image << std::endl;
    SDL_RenderCopy(renderer, m_image, nullptr, &rect);
}

void Ball::setMoving(bool moving){
    m_moving = moving;
}

bool Ball::collidesWith(const GameObject& obj) const{
    SDL_Rect ballBox = getBoundingBox();
    SDL_Rect objBox = obj.getBoundingBox();
    return SDL_HasIntersection(&ballBox, &objBox);
}

void Ball::setVelocityX(double x){
    m_velocity.x = x;
}

void Ball::setVelocityY(double y){
    m_velocity.y = y;
}
double Ball::getVelocityX(){
    return m_velocity.x;
}

double Ball::getVelocityY(){
    return m_velocity.y;
}

void Ball::setPositionX(double x){
    m_position.x = x;
}

void Ball::setPositionY(double y){
    m_position.y = y;
}