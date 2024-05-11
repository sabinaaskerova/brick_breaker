#ifndef WALL_H
#define WALL_H
#include "gameObject.hpp"
/**
 * @brief The Wall class represents a wall object in the game.
 */
class Wall : public GameObject{
    public:
        Wall();
        /**
         * @brief Constructor for the Wall class.
         *
         * @param pos The position of the wall.
         * @param size The size of the wall.
         */
        Wall(const position& pos, const objectSize& size);
        void update() override;
        void draw(SDL_Renderer* const renderer) override;
        bool collidesWith(const GameObject& obj) const override;
};
#endif // WALL_H