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

void Brick::setType(typeBrick type){
    m_type = type;
}

void Brick::update() {
}

bool Brick::collidesWith(const GameObject& obj) const{
    return false;
}

void Brick::printProperties() const {
        std::cout <<  static_cast<int>(m_type) ;
}
void Brick::draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = getPosition().x;
    rect.y = getPosition().y;
    rect.w = getSize().width;
    rect.h = getSize().height;
       SDL_RenderFillRect(renderer, &rect);
}
void Brick::setDestroyed(bool destroyed){
    m_destroyed = destroyed;
}

SDL_Rect Brick::getBoundingBox() const{
    return {(int)m_position.x, (int)m_position.y, (int)m_size.width, (int)m_size.height};
}


HexagonalBrick::HexagonalBrick(double q, double r, objectSize size, typeBrick type, double radius) 
    : Brick(position(), size, type), m_q(q), m_r(r), m_radius(radius){
    double x = m_size.width * (3.0 / 2.0) * m_q;
    double y = m_size.height * sqrt(3) * (m_r + m_q / 2.0);
    m_center.x = m_size.width * (3.0 / 2.0) * m_q;
    m_center.y = m_size.height * sqrt(3) * (m_r + m_q / 2.0);
}


bool HexagonalBrick::collidesWith(const GameObject& obj) const{
    return false;
}

void HexagonalBrick::draw(SDL_Renderer* renderer) {
    std::vector<SDL_Point> points(6);
    for (int i = 0; i < 6; ++i) {
        points[i].x = m_center.x + m_radius * cos(i * M_PI / 3);
        points[i].y = m_center.y + m_radius * sin(i * M_PI / 3);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < 6; ++i) {
        SDL_RenderDrawLine(renderer, points[i].x, points[i].y, points[(i + 1) % 6].x, points[(i + 1) % 6].y);
    }
}


std::vector<position> HexagonalBrick::getVertices() const {
    std::vector<position> vertices(6);
    float angle = M_PI / 6; // Start at 30 degrees
    float angleIncrement = M_PI / 3; // Each vertex is 60 degrees apart

    for (int i = 0; i < 6; i++) {
        vertices[i].x = m_position.x + m_size.width * cos(angle);
        vertices[i].y = m_position.y + m_size.width * sin(angle);
        angle += angleIncrement;
    }

    return vertices;
}

SDL_Rect HexagonalBrick::getBoundingBox() const {
    // Get the vertices of the hexagon
    std::vector<position> vertices = getVertices();

    // Initialize the bounding box to the first vertex
    SDL_Rect boundingBox;
    boundingBox.x = vertices[0].x;
    boundingBox.y = vertices[0].y;
    boundingBox.w = 0;
    boundingBox.h = 0;

    // Expand the bounding box to include each vertex
    for (const position& vertex : vertices) {
        if (vertex.x < boundingBox.x) {
            boundingBox.w += boundingBox.x - vertex.x;
            boundingBox.x = vertex.x;
        } else if (vertex.x > boundingBox.x + boundingBox.w) {
            boundingBox.w = vertex.x - boundingBox.x;
        }

        if (vertex.y < boundingBox.y) {
            boundingBox.h += boundingBox.y - vertex.y;
            boundingBox.y = vertex.y;
        } else if (vertex.y > boundingBox.y + boundingBox.h) {
            boundingBox.h = vertex.y - boundingBox.y;
        }
    }

    return boundingBox;
}

void HexagonalBrick::update() {
}

