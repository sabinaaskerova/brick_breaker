#include "ball.hpp"
#include <iostream>

Ball::Ball(SDL_Renderer* renderer, const position& pos, const objectSize& size, const velocity& vel): GameObject(renderer, pos, size){
    m_velocity = vel;
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


void Ball::update(){
    m_position.x += m_velocity.x;
    m_position.y += m_velocity.y;
}
void Ball::draw(SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.x = static_cast<int>(m_position.x);
    rect.y = static_cast<int>(m_position.y);
    rect.w = m_size.width;
    rect.h = m_size.height;
    SDL_RenderCopy(renderer, m_image, nullptr, &rect);
}

bool Ball::collidesWith(const GameObject& obj) const {
    auto hexagonalBrick = dynamic_cast<const HexagonalBrick*>(&obj);
    if (hexagonalBrick != nullptr) {
        for (int i = 0; i < 6; ++i) {
            position point = {hexagonalBrick->getPosition().x + hexagonalBrick->getSize().height * cos(i * M_PI / 3),
                                                hexagonalBrick->getPosition().y + hexagonalBrick->getSize().width * sin(i * M_PI / 3)};
            position difference = m_position - point;
            if (difference.length() <= m_size.width / 2.0) {
                return true;
            }
        }
        return false;
    } else {
        SDL_Rect ballBox = getBoundingBox();
        SDL_Rect objBox = obj.getBoundingBox();
        return SDL_HasIntersection(&ballBox, &objBox);
    }
}

void Ball::setVelocityX(double x){
    m_velocity.x = x;
}

void Ball::setVelocityY(double y){
    m_velocity.y = y;
}
double Ball::getVelocityX() const{
    return m_velocity.x;
}

double Ball::getVelocityY() const{
    return m_velocity.y;
}

void Ball::setPositionX(double x){
    m_position.x = x;
}

void Ball::setPositionY(double y){
    m_position.y = y;
}