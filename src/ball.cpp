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
    m_x = m_position.x;
    m_y = m_position.y;

    int posX = static_cast<int>(m_position.x);
    int posY = static_cast<int>(m_position.y);

    SDL_QueryTexture(m_image, nullptr, nullptr, &posX, &posY);

    m_velocity.x = 3;
    m_velocity.y = 2;
}

void Ball::update(){
    // if (!m_gameStarted) {
    //     m_y = m_y + m_velocity.y*1/60;
    //     m_position.y = m_y;
    // }
    // else if(m_moving){
        m_x = m_x +  (m_velocity.x*1/60);
        m_y = m_y - (m_velocity.y*1/60);
        m_position.x = m_x;
        m_position.y = m_y;
        std::cout << "Ball x: " << m_x << " Ball y: " << m_y << std::endl;
        std::cout << "Ball velocity x: " << m_velocity.x << " Ball velocity y: " << m_velocity.y << std::endl;
    // }

}

void Ball::draw(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, m_image, nullptr, (SDL_Rect*)&m_position);
}


void Ball::setMoving(bool moving){
    m_moving = moving;
}

bool Ball::collidesWith(const GameObject& obj) const{
    SDL_Rect ballBox = getBoundingBox();
    SDL_Rect objBox = obj.getBoundingBox();

    return SDL_HasIntersection(&ballBox, &objBox);
}

void Ball::render(){
}

void Ball::setVelocityX(double x){
    m_velocity.x = x;
}

void Ball::setVelocityY(double y){
    m_velocity.y = y;
}

void Ball::startGame() {
    m_gameStarted = true;
}