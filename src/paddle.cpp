#include "paddle.hpp"


Paddle::Paddle(position& pos, objectSize& size): GameObject(pos, size){
    m_width = size.width;
    
}
Paddle::~Paddle(){

}

void Paddle::render(){

}

void Paddle::update(){

}

void Paddle::collidesWith(GameObject* obj){

}

void Paddle::move(int x){
    m_position.x += x;
}

const int& Paddle::getWidth(){
    return m_width;
}

void Paddle::draw(SDL_Renderer* renderer){
    SDL_Rect paddle = {m_position.x, m_position.y, m_size.width, m_size.height};
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderPresent(renderer);
    // SDL_RenderFillRect(renderer, &paddle);
}

void Paddle::handle_input(SDL_Event const &event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
            m_position.x = event.motion.x;
            break;
    }
}