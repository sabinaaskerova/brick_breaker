#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>

int main(int argc, char* argv[]) {
  if (argc <= 2) {
    throw std::runtime_error(
        "Please provide the grid type (hexagonal, classic) and the grid "
        "number");
  }
  std::string gridType = argv[1];
  int gridNumber = std::stoi(argv[2]);
  if (gridNumber <= 0 || gridNumber > GRIDN) {
    throw std::runtime_error("Grid number must be between 1 and " +
                             std::to_string(GRIDN) + " inclusive.");
  }
  Game game(gridType, gridNumber);
  game.game_loop();
  return 0;
}