#ifndef WALL_H
#define WALL_H
#include "gameObject.hpp"
class Wall : public GameObject{
    public:
        Wall();
        Wall(const position& pos, const objectSize& size);
        void update() override;
        void draw(SDL_Renderer* const renderer) override;
        bool collidesWith(const GameObject& obj) const override;
};
#endif // WALL_H