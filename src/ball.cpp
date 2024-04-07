#include "ball.hpp"
#include <iostream>

Ball::Ball(position& pos, objectSize& size, velocity& vel): GameObject(pos, size){
    m_velocity = vel;
    m_moving = false;
    m_gameStarted = false;
    m_x = m_position.x;
    m_y = m_position.y;
}
Ball::Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel): GameObject(renderer, pos, size){
    m_velocity = vel;
    m_moving = false;
}

Ball::~Ball(){}

void Ball::update(){
    if (!m_gameStarted) {
        m_y = m_y + m_velocity.y*1/60;
        m_position.y = m_y;
    }
    else if(m_moving){
        m_x = m_x +  m_velocity.x;
        m_y = m_y - m_velocity.y;
        m_position.x = m_x;
        m_position.y = m_y;
    }

}

void Ball::init(SDL_Renderer *renderer, int x, int y)
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

    m_x = m_position.x;
    m_y = m_position.y;

    SDL_QueryTexture(m_image, nullptr, nullptr, &m_position.y, &m_position.y);

    m_velocity.x = 3;

    m_velocity.y = 2;
    
}

void Ball::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, m_image, nullptr, (SDL_Rect*)&m_position);
}


void Ball::setMoving(bool moving){
    m_moving = moving;
}

void Ball::collidesWith(GameObject* obj){

}

void Ball::render(){
}

void Ball::setVelocityX(int x){
    m_velocity.x = x;
}

void Ball::setVelocityY(int y){
    m_velocity.y = y;
}