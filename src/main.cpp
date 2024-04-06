#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>

int main(int argc, char* argv[]) {
    Game game;
    game.init();    
    game.game_loop();
    return 0;
}