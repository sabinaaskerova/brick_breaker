#ifndef PADDLE_H
#define PADDLE_H
#include "gameObject.hpp"
// #include "structs.hpp"

class Paddle: public GameObject{
    private:
        // int m_width;
        // int m_height;
        
    public:
        Paddle(SDL_Renderer* renderer, position pos, objectSize size);
        Paddle(position& pos, objectSize& size); // & because we are not copying the object valgrind --leak-check=full ./your_program
        ~Paddle();
        void update() override;
        // void render() override;
        void draw(SDL_Renderer* renderer) override;
        void handle_input(SDL_Event const &event);
        void setWidth(int);

        bool collidesWith(const GameObject& obj) const override;
        void move(int x);
        const int& getWidth();
};


#endif // PADDLE_H