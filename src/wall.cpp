#include "wall.hpp"

Wall::Wall(position& pos, objectSize& size): GameObject(pos, size) {}

Wall::Wall(){
}

void Wall::update() {
}

void Wall::render() {
}

void Wall::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_Rect wallRect = getBoundingBox();
    int thickness = 5; // Set the thickness of the wall
    for (int i = 0; i < thickness; i++) {
        SDL_Rect thickWallRect = { wallRect.x - i, wallRect.y - i, wallRect.w + 2 * i, wallRect.h + 2 * i };
        SDL_RenderDrawRect(m_renderer, &thickWallRect);
    }
}

bool Wall::collidesWith(const GameObject& obj) const {
    SDL_Rect wallBox = getBoundingBox();
    SDL_Rect objBox = obj.getBoundingBox();
    return SDL_HasIntersection(&wallBox, &objBox);
}