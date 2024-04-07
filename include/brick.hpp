#ifndef BRICK_H
#define BRICK_H
#include "gameObject.hpp"
#include "structs.hpp"
#include <iostream>

class Brick : public GameObject
{
    protected:
        position m_position;
        objectSize m_size;
        typeBrick m_type;
        bool m_destroyed;
        SDL_Renderer* m_renderer;

    
    public:
        Brick(position pos, objectSize size, typeBrick type);
        ~Brick();

        void update() override;
        void render() override;
        void draw(SDL_Renderer* renderer) override;

        bool collidesWith(const GameObject& obj) const override;
        bool isDestroyed() const;

        position getPosition(); // const 
        objectSize getSize();
        const typeBrick& getType();
        void setType(typeBrick);
        void setDestroyed(bool destroyed);
        
        void printProperties() const;



};

#endif // BRICK_H
