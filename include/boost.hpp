#ifndef BOOST_H
#define BOOST_H
#include "structs.hpp"
#include "gameObject.hpp"
#include "ball.hpp"
#include <type_traits>
#include "SDL2/SDL.h"
class Boost: public GameObject{
    protected:
        Uint32 m_activation_time;
        const Uint32 m_duration;        
        velocity m_speed;
        bool wasApplied;
        
    public:
        Boost(SDL_Renderer* renderer, const position pos, const objectSize size, const velocity speed, const Uint32 duration);
        virtual ~Boost();
        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
        bool collidesWith( const GameObject& obj) const;
        bool isActive(Uint32 current_time) const;
        bool getWasApplied() const;      
};

class BonusMultiBall : public Boost{
    public:
        BonusMultiBall(SDL_Renderer* renderer, const position pos, const objectSize size, const velocity speed, const Uint32 duration);
        ~BonusMultiBall() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};

class BonusWidePaddle : public Boost{
    public:
        BonusWidePaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~BonusWidePaddle() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};

class MalusNarrowPaddle : public Boost{
    public:
        MalusNarrowPaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~MalusNarrowPaddle() override;
        void update() override;
        void draw(SDL_Renderer* renderer) override;
};

#endif // BOOST_H