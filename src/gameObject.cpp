#include "gameObject.hpp"

GameObject::GameObject(){
    
}

GameObject::GameObject(SDL_Renderer* renderer) : m_renderer(renderer) {
    
}
GameObject::GameObject(SDL_Renderer* renderer, position pos, objectSize size) : m_renderer(renderer), m_position(pos), m_size(size) {
    
}

GameObject::~GameObject() {}


