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