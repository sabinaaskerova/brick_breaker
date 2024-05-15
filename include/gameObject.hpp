/**
 * @file gameObject.hpp
 * @author Sabina Askerova
 * @brief Header file for the GameObject class.
 *
 * This file contains the declaration of the GameObject class, which is an abstract class representing
 * objects within the game environment. GameObject provides common functionality and properties
 * for all game objects.
 */
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structs.hpp"
/**
 * @brief Game Object abstract class.
 * 
 */
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
    GameObject(const position& pos, const objectSize& size);
    GameObject(SDL_Renderer* renderer, const position& pos, const objectSize& size);
    SDL_Rect getBoundingBox() const;
    virtual ~GameObject();
    virtual void update() = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual bool collidesWith( const GameObject& obj) const = 0;

    position& getPosition();
    objectSize& getSize();

};
#endif // GAMEOBJECT_H
