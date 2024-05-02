#include "brick.hpp"

Brick::Brick(position pos, objectSize size, typeBrick type) : m_destroyed(false)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_size.height = size.height;
    m_size.width = size.width;
    m_type = type;
}

const typeBrick& Brick::getType(){
    return m_type;
}

void Brick::setType(typeBrick type){
    m_type = type;
}

bool Brick::isDestroyed() const {
    return m_destroyed;
}

Brick::~Brick() = default;

objectSize Brick::getSize() const
{
    return m_size;
}

position Brick::getPosition() const
{
    return m_position;
}


void Brick::setDestroyed(bool destroyed){
    m_destroyed = destroyed;
}



ClassicBrick::~ClassicBrick() {
}

ClassicBrick::ClassicBrick(position pos, objectSize size, typeBrick type) 
    : Brick(pos, size, type)
{
}


void ClassicBrick::update() {
}

void ClassicBrick::draw(SDL_Renderer* renderer) {
    SDL_Rect rect;
    rect.x = getPosition().x;
    rect.y = getPosition().y;
    rect.w = getSize().width;
    rect.h = getSize().height;
    SDL_RenderFillRect(renderer, &rect);
}

bool ClassicBrick::collidesWith(const GameObject& obj) const{
    return false;
}

void Brick::printProperties() const {
    std::cout <<  static_cast<int>(m_type) ;
}

SDL_Rect ClassicBrick::getBoundingBox() const{
    return {(int)m_position.x, (int)m_position.y, (int)m_size.width, (int)m_size.height};
}

HexagonalBrick::HexagonalBrick(double q, double r, objectSize size,
                               typeBrick type)
    : Brick({q, r}, size, type), m_q(q), m_r(r) {
  m_position.x = m_size.width * sqrt(1.2) * (m_q + 0.5 * (int(r) & 1)) +
                 static_cast<double>(INITX);
  if (int(r) % 2 == 0) {
    m_position.x += m_size.width / 2.0;
  }
  m_position.y = m_size.height * 3.0 / 2.5 * m_r + static_cast<double>(INITY);
  
  if (int(q) % 2 == 0) {
    m_position.y += m_size.height / 2.0;
  }
  m_radius = m_size.width / 2.0;
}

void HexagonalBrick::update() {
}

void HexagonalBrick::draw(SDL_Renderer* renderer) {
  Sint16 pointsX[6];
  Sint16 pointsY[6];
  for (int i = 0; i < 6; ++i) {
    pointsX[i] = getPosition().x + m_radius * cos(i * M_PI / 3);
    pointsY[i] = getPosition().y + m_radius * sin(i * M_PI / 3);
  }
  filledPolygonRGBA(renderer, pointsX, pointsY, 6, 255, 255, 255, 255);
}

void HexagonalBrick::draw(SDL_Renderer* renderer, Color color) {
    Sint16 pointsX[6];
    Sint16 pointsY[6];
    for (int i = 0; i < 6; ++i) {
        pointsX[i] = getPosition().x + m_radius * cos(i * M_PI / 3);
        pointsY[i] = getPosition().y + m_radius * sin(i * M_PI / 3);
    }
    filledPolygonRGBA(renderer, pointsX, pointsY, 6, color.r, color.g, color.b, color.a);
}

bool HexagonalBrick::collidesWith(const GameObject& obj) const{
    return false;
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

