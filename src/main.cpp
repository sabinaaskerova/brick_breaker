#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>


void draw_circle(SDL_Renderer* renderer,int center_x, int center_y, int radius_){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for(int x=center_x-radius_; x<=center_x+radius_; x++){
        for(int y=center_y-radius_; y<=center_y+radius_; y++){
            if((std::pow(center_y-y,2)+std::pow(center_x-x,2)) <= 
                std::pow(radius_,2)){
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1200, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    assert (renderer != nullptr);

    Game game;
    game.init();
    BrickGrid& brickGrid = game.getBrickGrid();
    
    // for (const std::vector<std::unique_ptr<Brick>>& row : brickGrid.getBricks()) {
    //     for (const std::unique_ptr<Brick>& brick : row) {
    for (const std::vector<std::unique_ptr<Brick>>& row : brickGrid.getBricks()) {
        for (const std::unique_ptr<Brick>& brick : row) {
            if (brick != nullptr) {
                std::cout<<" brick position x " << static_cast<int>(brick->getPosition().x)<<std::endl;
                std::cout<<" brick position y " << static_cast<int>(brick->getPosition().y)<<std::endl;
                // std::cout<<" brick width" << static_cast<int>(brick->getSize().width)<<std::endl;
                // std::cout<<" brick height" << static_cast<int>(brick->getSize().height)<<std::endl;
                // SDL_Rect rect2 = { (brick->getPosition().x), (brick->getPosition().y), (brick->getSize().width), (brick->getSize().height) };
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
                else{
                    
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); 
                }
                SDL_RenderFillRect(renderer, &rect);

                
            }
        }
    }
    SDL_Surface* surface = IMG_Load("./img/circ.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // we got the texture, we can free the surface

    SDL_Rect dst;
    dst.x =700;
    dst.y = 700;
    dst.w = 100; // width of the texture
    dst.h = 100; // height of the texture

    SDL_RenderCopy(renderer, texture, NULL, &dst);
    // draw_circle(renderer, 350, 700, 100);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

    bool keep_window_open = true;
    while(keep_window_open)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    keep_window_open = false;
                    break;
            }

            SDL_UpdateWindowSurface(window);
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
