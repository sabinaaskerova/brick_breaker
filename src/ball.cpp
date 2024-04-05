#include "ball.hpp"


Ball::Ball(position& pos, objectSize& size, velocity& vel): GameObject(pos, size){
    m_velocity = vel;
    m_moving = false;
}
Ball::Ball(SDL_Renderer* renderer, position& pos, objectSize& size, velocity& vel): GameObject(renderer, pos, size){
    m_velocity = vel;
    m_moving = false;
}

Ball::~Ball(){}

void Ball::update(){
    if(m_moving){
        m_position.x += m_velocity.x;
        m_position.y += m_velocity.y;
    }
}

void Ball::render(){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_Rect rect = {m_position.x, m_position.y, m_size.width, m_size.height};
    // SDL_RenderFillRect(m_renderer, &rect);
    // SDL_RenderGeometry(m_renderer, ) // draw a circle
}

void Ball::setMoving(bool moving){
    m_moving = moving;
}

void Ball::collidesWith(GameObject* obj){

}