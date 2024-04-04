#ifndef BOOST_H
#define BOOST_H
#include "structs.hpp"
#include "gameObject.hpp"
#include "ball.hpp"

class Boost: public GameObject{
    protected:
        int m_duration;
        
    public:
        Boost(SDL_Renderer* renderer, position pos, objectSize size, int speed, int duration);
        virtual ~Boost();
        virtual void update();
        virtual void render();
        virtual void collidesWith(GameObject* obj);
        virtual void applyBoost();
};

// class BonusBoost: public Boost{
    
//     public:
//         BonusBoost(SDL_Renderer* renderer, position pos, objectSize size, int speed, int duration);
//         ~BonusBoost();
//         void update();
//         void render();
//         void collidesWith(GameObject* obj);
//         void applyBoost();
// };

class BonusMultiBall : public Boost{
    public:
        BonusMultiBall(SDL_Renderer* renderer, position pos, objectSize size, int speed, int duration);
        ~BonusMultiBall();
        void update();
        void render();
        void collidesWith(GameObject* obj);
        void applyBoost();
};

#endif // BOOST_H