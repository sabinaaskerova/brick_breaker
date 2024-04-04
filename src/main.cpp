#include <SDL2/SDL.h>
#include "game.hpp"
// g++ main.cpp -o main -lSDL2
int main(int argc, char* argv[]) {


    Game game;
    game.init();
    BrickGrid& brickGrid = game.getBrickGrid();
    // std::cout<<" brickgrid size " << brickGrid.getBricks()[0][0]->getPosition().x<<std::endl;

    for (const std::vector<Brick>& row : brickGrid.getBricks()) {
        std::cout<<"row" <<std::endl;
        // std::cout<<" row size " <<std::endl;
        // for (const Brick& brick : row) {
        //     std::cout<<" brick " << brick->getSize().height<<","<<brick->getSize().width <<std::endl;
        //     if (brick != nullptr) {
        //         std::cout<<"    not null brick"<<std::endl;
        //         // SDL_Rect rect = { brick->getPosition().x, brick->getPosition().y, brick->getSize().width, brick->getSize().height };
        //         // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        //         // SDL_RenderFillRect(renderer, &rect);
        //     }
        // }
    }


    return 0;
}
