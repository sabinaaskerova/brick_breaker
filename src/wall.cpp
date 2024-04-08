#include "wall.hpp"

Wall::Wall(position& pos, objectSize& size): GameObject(pos, size) {}

Wall::Wall(){
}

void Wall::update() {
}

void Wall::render() {
}

void Wall::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect wallRect = getBoundingBox();
    int thickness = 5; // Set the thickness of the wall
    for (int i = 0; i < thickness; i++) {
        SDL_Rect thickWallRect = { wallRect.x - i, wallRect.y - i, wallRect.w + 2 * i, wallRect.h + 2 * i };
        SDL_RenderDrawRect(renderer, &thickWallRect);
    }
}
bool Wall::collidesWith(const GameObject& obj) const {
    SDL_Rect wallBox = getBoundingBox();
    SDL_Rect objBox = obj.getBoundingBox();

    if (objBox.x < wallBox.x + wallBox.w &&
        objBox.x + objBox.w > wallBox.x &&
        objBox.y < wallBox.y + wallBox.h &&
        objBox.y + objBox.h > wallBox.y) {
        return true;
    }

    return false;
}