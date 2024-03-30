#include "gameObject.hpp"

GameObject::GameObject(){
    
}

GameObject::GameObject(SDL_Renderer* renderer) : m_renderer(renderer) {
    
}

GameObject::~GameObject() {}

