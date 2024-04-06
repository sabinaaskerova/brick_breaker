#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>

int main(int argc, char* argv[]) {
    Game game;
    game.init();    

    // SDL_Rect ball;
    // ball.w = 20; 
    // ball.h = 20;
    // ball.x = paddle.x + (paddle.w - ball.w) / 2;
    // ball.y = paddle.y - ball.h-20;
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, &ball);



    // SDL_RenderPresent(renderer);
    // SDL_UpdateWindowSurface(window);

    game.game_loop();

    

    return 0;
}
