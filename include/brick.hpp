#ifndef BRICK_H
#define BRICK_H
#include "gameObject.hpp"
#include "structs.hpp"
#include <iostream>
#include <vector>
class Brick : public GameObject
{
    protected:
        typeBrick m_type;
        bool m_destroyed;
    
    public:
        Brick(position pos, objectSize size, typeBrick type);
        ~Brick();

        void update() override;
        void draw(SDL_Renderer* renderer) override;

        bool collidesWith(const GameObject& obj) const override;
        bool isDestroyed() const;

        position getPosition(); // const 
        objectSize getSize();
        const typeBrick& getType();
        void setType(typeBrick);
        void setDestroyed(bool destroyed);
        SDL_Rect getBoundingBox() const;
        void printProperties() const;



};


class HexagonalBrick : public Brick{
private:
    double m_q; // Axial q-coordinate
    double m_r; // Axial r-coordinate
    position m_center; 
    double m_radius;
    SDL_Renderer* m_renderer;

public:
    HexagonalBrick(double q, double r, objectSize size, typeBrick type, double radius);
    void draw(SDL_Renderer* renderer) override;
    void update() override;
    bool collidesWith(const GameObject& obj) const override;
    std::vector<position> getVertices() const;
    SDL_Rect getBoundingBox() const;



};

#endif // BRICK_H

