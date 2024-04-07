#include "gameObject.hpp"

GameObject::GameObject():m_position({0,0}), m_size{20,20}{

}

GameObject::GameObject(position& pos, objectSize& size){
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_size.height = size.height;
    m_size.width = size.width;
}

GameObject::GameObject(SDL_Renderer* renderer) : m_renderer(renderer) {
    
}
GameObject::GameObject(SDL_Renderer* renderer, position& pos, objectSize& size) : m_renderer(renderer) {
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_size.height = size.height;
    m_size.width = size.width;
}


SDL_Rect GameObject::getBoundingBox() const {
    return {(int)m_position.x, (int)m_position.y, (int)m_size.width, (int)m_size.height};
}

position& GameObject::getPosition(){
    return m_position;
}
GameObject::~GameObject() {}


