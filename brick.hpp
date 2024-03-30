#ifndef BRICK_H
#define BRICK_H
#include "gameObject.hpp"
#include "structs.hpp"

class Brick : public GameObject
{
    private:
        position m_position;
        size m_size;
        typeBrick m_type;
        bool m_destroyed;
        SDL_Renderer* m_renderer;
        void setDestroyed(bool);
    
    public:
        Brick(position pos, size size, typeBrick type);
        // Brick(size size, typeBrick type);
        ~Brick();
        void update();
        void render();
        void collidesWith(GameObject* obj);
        bool isDestroyed();
        position getPosition(); // const ? if the size of window changes then no
        size getSize();
        const typeBrick& getType();
        void setType(typeBrick);


};

#endif // BRICK_H
