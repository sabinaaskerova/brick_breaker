#include "paddle.hpp"

#include <iostream>

Paddle::Paddle(const position& pos, const objectSize& size)
    : GameObject(pos, size), m_type(PaddleType::NORMAL) {}

Paddle::~Paddle() {}

void Paddle::update() {}

bool Paddle::collidesWith(const GameObject& obj) const{
    return false;
}

void Paddle::move(int x){
    m_position.x += x;
}

const double& Paddle::getWidth() const { return m_size.width; }

void Paddle::setWidth(int width){
    m_size.width = width;
}

void Paddle::draw(SDL_Renderer* renderer){
    SDL_Rect paddle = {static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_size.width, m_size.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
}

void Paddle::handle_input(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
        
            m_position.x = event.motion.x - m_size.width / 2; // center the paddle on the mouse
            if (m_position.x < WALLSX) {
                m_position.x = WALLSX;
            } else if (m_position.x + m_size.width > WALLSX + WALLSW) {
                m_position.x = WALLSX + WALLSW - m_size.width;
            }
        
            break;
    }
}

void Paddle::setType(PaddleType type){
    m_type = type;
}
const PaddleType& Paddle::getType() const { return m_type; }