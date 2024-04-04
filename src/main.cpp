#include <SDL2/SDL.h>
#include "game.hpp"
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
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return 1;
    }

    Game game;
    game.init();
    BrickGrid& brickGrid = game.getBrickGrid();
    // for (const std::vector<std::unique_ptr<Brick>>& row : brickGrid.getBricks()) {
    //     for (const std::unique_ptr<Brick>& brick : row) {
    //         std::cout<<" brick position x " << static_cast<int>(brick->getPosition().x)<<std::endl;
    //         std::cout<<" brick position y " << static_cast<int>(brick->getPosition().y)<<std::endl;
    //     }
    // }
    // for(int i=0;i<static_cast<int>(brickGrid.getBricks().size());i++)
    // {
    //     for(int j=0;j<static_cast<int>(brickGrid.getBricks()[i].size());j++)
    //     {
    //         std::unique_ptr<Brick>& brick = brickGrid.getBricks()[i][j];
    //         if(brickGrid.getBricks()[i][j] != nullptr)
    //         {
    //             // std::cout<<" brick position x " << static_cast<int>(brickGrid.getBricks()[i][j]->getPosition().x)<<std::endl;
    //             // std::cout<<" brick position y " << static_cast<int>(brickGrid.getBricks()[i][j]->getPosition().y)<<std::endl;
    //             // std::cout<<" brick width" << static_cast<int>(brickGrid.getBricks()[i][j]->getSize().width)<<std::endl;
    //             // std::cout<<" brick height" << static_cast<int>(brickGrid.getBricks()[i][j]->getSize().height)<<std::endl;
    //             std::cout<<" brick "<<i<<","<<j<< " type" << static_cast<int>(brickGrid.getBricks()[i][j]->getType())
    //                 << " x: " << static_cast<int>(brickGrid.getBricks()[i][j]->getPosition().x)
    //                 <<" y: " << static_cast<int>(brickGrid.getBricks()[i][j]->getPosition().y)
    //                 <<std::endl;
    //             if(brick->getType() == typeBrick::NORMAL)
    //             {
    //                 SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
    //                 SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    //                 SDL_RenderFillRect(renderer, &rect2);
    //                 SDL_RenderPresent(renderer); 
    //             }
    //             else if(brick->getType() == typeBrick::DOUBLE)
    //             {
    //                 SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
    //                 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
    //                 SDL_RenderFillRect(renderer, &rect2);
    //                 SDL_RenderPresent(renderer); 
    //             }
    //             else if(brick->getType() == typeBrick::TRIPLE)
    //             {
    //                 SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
    //                 SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
    //                 SDL_RenderFillRect(renderer, &rect2);
    //                 SDL_RenderPresent(renderer); 
    //             }
    //         }else{
    //             std::cout<<" brick "<<i<<","<<j<< " is null"<<std::endl;
            
    //         }
    //     }
    // }


    // Render the bricks
    
    for (const std::vector<std::unique_ptr<Brick>>& row : brickGrid.getBricks()) {
        for (const std::unique_ptr<Brick>& brick : row) {
            if (brick != nullptr) {
                // std::cout<<" brick position x " << static_cast<int>(brick->getPosition().x)<<std::endl;
                // std::cout<<" brick position y " << static_cast<int>(brick->getPosition().y)<<std::endl;
                // std::cout<<" brick width" << static_cast<int>(brick->getSize().width)<<std::endl;
                // std::cout<<" brick height" << static_cast<int>(brick->getSize().height)<<std::endl;
                // SDL_Rect rect1= { 100, 100, 200, 150 }; // x, y, width, height
                // SDL_RenderFillRect(renderer, &rect1);
                if(brick->getType() == typeBrick::NORMAL)
                {
                    SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
                    SDL_RenderFillRect(renderer, &rect2);
                    SDL_RenderPresent(renderer); 
                }
                else if(brick->getType() == typeBrick::DOUBLE)
                {
                    SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
                    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
                    SDL_RenderFillRect(renderer, &rect2);
                    SDL_RenderPresent(renderer); 
                }
                else if(brick->getType() == typeBrick::TRIPLE)
                {
                    SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
                    SDL_RenderFillRect(renderer, &rect2);
                    SDL_RenderPresent(renderer); 
                } 
                else{
                    SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color
                    SDL_RenderFillRect(renderer, &rect2);
                    SDL_RenderPresent(renderer);

                }
            
                // SDL_Rect rect2 = { static_cast<int>(brick->getPosition().x), static_cast<int>(brick->getPosition().y), static_cast<int>(brick->getSize().width), static_cast<int>(brick->getSize().height) };
                // SDL_RenderFillRect(renderer, &rect2);

                // SDL_SetRenderDrawColor(renderer, 255, 255,0, 0);
                
            }
        }
    }

    SDL_RenderPresent(renderer);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    // SDL_RenderClear(renderer);
    // SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, width, height
    // SDL_RenderFillRect(renderer, &rect);
    // SDL_RenderPresent(renderer);
    SDL_Delay(14000); 
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
