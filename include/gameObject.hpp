#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structs.hpp"
class GameObject
{
protected:
    SDL_Renderer* m_renderer;
    position m_position;
    objectSize m_size;
    SDL_Texture *m_image;

public:
    GameObject();
    GameObject(SDL_Renderer* renderer);
    GameObject(position& pos, objectSize& size);
    GameObject(SDL_Renderer* renderer, position& pos, objectSize& size);
    virtual ~GameObject();
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual void collidesWith(GameObject* obj) = 0;


};
#endif // GAMEOBJECT_H
