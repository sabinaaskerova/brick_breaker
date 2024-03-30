#include "brick.hpp"

Brick::Brick(position pos, size size, typeBrick type) : m_type(type), m_destroyed(false)
{
    m_position = pos;
    m_size = size;
}

size Brick::getSize()
{
    return m_size;
}
position Brick::getPosition()
{
    return m_position;
}