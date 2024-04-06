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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = {m_position.x, m_position.y, m_size.width, m_size.height};
    SDL_RenderFillRect(renderer, &rect);
}