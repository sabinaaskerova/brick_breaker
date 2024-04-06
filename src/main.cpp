#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Kirpish syndyru", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    assert (window != nullptr);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    assert (renderer != nullptr);

    Game game;
    game.init();
    BrickGrid& brickGrid = game.getBrickGrid();
    assert (!brickGrid.getBricks().empty());

    SDL_Rect walls;
    walls.x = WALLSX;
    walls.y = WALLSY;
    walls.w = WALLSW; 
    walls.h = WALLSH;

    SDL_SetRenderDrawColor(renderer, 204, 153, 255, 255);
    for (int i = 0; i < 5; i++) {
        SDL_Rect thickWalls;
        thickWalls.x = walls.x - i;
        thickWalls.y = walls.y - i;
        thickWalls.w = walls.w + 2 * i;
        thickWalls.h = walls.h + 2 * i;
        SDL_RenderDrawRect(renderer, &thickWalls);
    }
    SDL_RenderDrawRect(renderer, &walls);
    
    for (const std::vector<std::unique_ptr<Brick>>& row : brickGrid.getBricks()) {
        for (const std::unique_ptr<Brick>& brick : row) {
            if (brick != nullptr) {
                if(brick->getType()!=typeBrick::EMPTY){
                    SDL_Rect rect;
                    rect.x = brick->getPosition().x;
                    rect.y = brick->getPosition().y;
                    rect.w = brick->getSize().width;
                    rect.h = brick->getSize().height;
                    if(brick->getType() == typeBrick::NORMAL)
                    {
                        
                        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
                    }
                    else if(brick->getType() == typeBrick::DOUBLE)
                    {
                        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
                        
                    }
                    else if(brick->getType() == typeBrick::TRIPLE)
                    {
                        
                        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
                    } 
                    SDL_RenderFillRect(renderer, &rect);
                }

            }
        }
    }

    // SDL_Rect paddle;
    // paddle.w = game.getPaddle()->getWidth(); 
    // paddle.h = 20; 
    // paddle.x = (walls.w - paddle.w) / 2 + walls.x; 
    // paddle.y = walls.y + walls.h - paddle.h - 40; 
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, &paddle);

    // SDL_Rect ball;
    // ball.w = 20; 
    // ball.h = 20;
    // ball.x = paddle.x + (paddle.w - ball.w) / 2;
    // ball.y = paddle.y - ball.h-20;
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_RenderFillRect(renderer, &ball);



    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

    // bool keep_window_open = true;
    // while(keep_window_open)
    // {
    //     SDL_Event e;
    //     while(SDL_PollEvent(&e) > 0)
    //     {
    //         switch(e.type)
    //         {
    //             case SDL_QUIT:
    //                 keep_window_open = false;
    //                 break;
    //         }

    //         SDL_UpdateWindowSurface(window);
    //     }
    // }

    // game.game_loop();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
