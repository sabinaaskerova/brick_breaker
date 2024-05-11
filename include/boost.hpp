#ifndef BOOST_H
#define BOOST_H
#include "structs.hpp"
#include "gameObject.hpp"
#include "ball.hpp"
#include <type_traits>
#include "SDL2/SDL.h"

/**
 * @brief Base class for all types of boosts in the game.
 */
class Boost: public GameObject{
    protected:
        Uint32 m_activation_time;
        const Uint32 m_duration;        
        velocity m_speed;
        
    public:
        /**
         * @brief Constructor for the Boost class.
         * 
         * @param renderer The SDL renderer used for drawing.
         * @param pos The initial position of the boost.
         * @param size The size of the boost.
         * @param speed The speed of the boost.
         * @param duration The duration of the boost.
         */
        Boost(SDL_Renderer* renderer, const position pos, const objectSize size, const velocity speed, const Uint32 duration);
        virtual ~Boost();
        virtual void update();
        /**
         * @brief Draws the boost on the screen.
         * 
         * @param renderer The SDL renderer used for drawing.
         */
        virtual void draw(SDL_Renderer* renderer);
        /**
         * @brief Checks whether the boost collides with the paddle.
         * 
         * @param obj The game object to check collision with.
         * @return True if there is a collision with the paddle, false otherwise.
         */
        bool collidesWith( const GameObject& obj) const;
        /**
         * @brief Checks whether the boost is currently active.
         * 
         * @param current_time The current time.
         * @return True if the boost is active, false otherwise.
         */
        bool isActive(Uint32 current_time) const;
     
};
/**
 * @brief Class representing a bonus multi-ball boost.
 */
class BonusMultiBall : public Boost{
    public:
        BonusMultiBall(SDL_Renderer* renderer, const position pos, const objectSize size, const velocity speed, const Uint32 duration);
        ~BonusMultiBall() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};
/**
 * @brief Class representing a bonus wide paddle boost.
 */
class BonusWidePaddle : public Boost{
    public:
        BonusWidePaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~BonusWidePaddle() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};
/**
 * @brief Class representing a malus narrow paddle boost.
 */
class MalusNarrowPaddle : public Boost{
    public:
        MalusNarrowPaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~MalusNarrowPaddle() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};

#endif // BOOST_H