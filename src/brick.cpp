#include "brick.hpp"

Brick::Brick(position pos, objectSize size, typeBrick type) : m_type(type), m_destroyed(false)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_size.height = size.height;
    m_size.width = size.width;
}
Brick::~Brick() = default;

objectSize Brick::getSize()
{
    return m_size;
}
position Brick::getPosition()
{
    return m_position;
}

bool Brick::isDestroyed() const {
    return m_destroyed;
}

const typeBrick& Brick::getType(){
    return m_type;
}

void Brick::render(){
    // SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    // SDL_Rect rect = {m_position.x, m_position.y, m_size.width, m_size.height};
    // SDL_RenderFillRect(m_renderer, &rect);
}

void Brick::setType(typeBrick type){
    m_type = type;
}

void Brick::update() {
}

bool Brick::collidesWith(const GameObject& obj) const{
}

void Brick::printProperties() const {
        std::cout <<  static_cast<int>(m_type) ;
}
void Brick::draw(SDL_Renderer* renderer) {
       
}
void Brick::setDestroyed(bool destroyed){
    m_destroyed = destroyed;
}

SDL_Rect Brick::getBoundingBox() const{
    return {(int)m_position.x, (int)m_position.y, (int)m_size.width, (int)m_size.height};
}