#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL2/SDL.h>
#include "structs.hpp"
class GameObject
{
protected:
    SDL_Renderer* m_renderer;
    position m_position;
    objectSize m_size;

public:
    GameObject();
    GameObject(SDL_Renderer* renderer);
    GameObject(position& pos, objectSize& size);
    GameObject(SDL_Renderer* renderer, position& pos, objectSize& size);
    virtual ~GameObject();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void collidesWith(GameObject* obj) = 0;


};
#endif // "GAMEOBJECT_H"