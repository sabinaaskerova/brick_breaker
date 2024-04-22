#ifndef PADDLE_H
#define PADDLE_H
#include "gameObject.hpp"

enum class PaddleType{
    NORMAL,
    WIDE,
    NARROW
};
class Paddle: public GameObject{   
    private:
        PaddleType m_type;     
    public:
        Paddle(SDL_Renderer* renderer, position pos, objectSize size);
        Paddle(position& pos, objectSize& size); // & because we are not copying the object valgrind --leak-check=full ./your_program
        ~Paddle();
        void update() override;
        void draw(SDL_Renderer* renderer) override;
        void handle_input(SDL_Event const &event);
        void setWidth(int);

        bool collidesWith(const GameObject& obj) const override;
        void move(int x);
        const double& getWidth();
        void setType(PaddleType type);
        const PaddleType& getType() const;
};


#endif // PADDLE_H