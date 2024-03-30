#include <SDL2/SDL.h>
#include "game.hpp"
// g++ main.cpp -o main -lSDL2
int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        return 1;
    }

    Game game;
    game.init();
    // Get the brick grid from the game
    BrickGrid& brickGrid = game.getBrickGrid();

    // Render the bricks
    for (const auto& row : brickGrid.getBricks()) {
        for (const auto& brick : row) {
            if (brick != nullptr) {
                // Render the brick
                SDL_Rect rect = { brick->getPosition().x, brick->getPosition().y, brick->getSize().width, brick->getSize().height };
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Render the changes to the screen
    SDL_RenderPresent(renderer);


    // // Set the color for drawing
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color

    // // Clear the renderer with the color
    SDL_RenderClear(renderer);



    // // Create a rectangle
    SDL_Rect rect = { 100, 100, 200, 150 }; // x, y, width, height

    // // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);

    // // Render the changes to the screen
    SDL_RenderPresent(renderer);



    // // Wait for 30 seconds
    SDL_Delay(30000);

    // // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
