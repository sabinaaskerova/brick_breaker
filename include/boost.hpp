#ifndef BOOST_H
#define BOOST_H
#include "structs.hpp"
#include "gameObject.hpp"
#include "ball.hpp"
#include <type_traits>
class Boost: public GameObject{
    protected:
        int m_duration;
        velocity m_speed;
        
    public:
        Boost(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        virtual ~Boost();
        virtual void update();
        virtual void render();
        virtual void draw(SDL_Renderer* renderer);
        virtual bool collidesWith( const GameObject& obj) const;
        virtual void applyBoost() = 0;
};


class BonusMultiBall : public Boost{
    public:
        BonusMultiBall(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~BonusMultiBall() override;
        void update() override;
        void render() override;
        void draw(SDL_Renderer* renderer) override;
        bool collidesWith(const GameObject& obj) const override;
        void applyBoost() override;
};

class BonusWidePaddle : public Boost{
    public:
        BonusWidePaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~BonusWidePaddle() override;
        void update() override;
        void render() override;
        void draw(SDL_Renderer* renderer) override;
        bool collidesWith(const GameObject& obj) const override;
        void applyBoost() override;
};

class MalusNarrowPaddle : public Boost{
    public:
        MalusNarrowPaddle(SDL_Renderer* renderer, position pos, objectSize size, velocity speed, int duration);
        ~MalusNarrowPaddle() override;
        void update() override;
        void render() override;
        void draw(SDL_Renderer* renderer) override;
        bool collidesWith(const GameObject& obj) const override;
        void applyBoost() override;
};

#endif // BOOST_H