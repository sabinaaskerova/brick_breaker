#include "paddle.hpp"


Paddle::Paddle(position& pos, objectSize& size): GameObject(pos, size){
    m_width = size.width;
    m_height = size.height;
    
}
Paddle::~Paddle(){

}

void Paddle::render(){

}

void Paddle::update(){

}

bool Paddle::collidesWith(const GameObject& obj) const{
    return false;
}

void Paddle::move(int x){
    m_position.x += x;
}

const int& Paddle::getWidth(){
    return m_width;
}

void Paddle::draw(SDL_Renderer* renderer){
    SDL_Rect paddle = {static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_size.width, m_size.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
}

void Paddle::handle_input(SDL_Event const &event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
        
            m_position.x = event.motion.x - m_width / 2; // center the paddle on the mouse
            if (m_position.x < WALLSX) {
                m_position.x = WALLSX;
            } else if (m_position.x + m_width > WALLSX + WALLSW) {
                m_position.x = WALLSX + WALLSW - m_width;
            }
        
            break;
    }
}