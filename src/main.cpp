#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"
#include <cassert>

int main(int argc, char* argv[]) {
  assert(
      argc > 2 &&
      "Please provide the grid type (hexagonal, classic) and the grid number");
  std::string gridType = argv[1];
  int gridNumber = std::stoi(argv[2]);
  //   assert(gridNumber > 0 && gridNumber <= GRIDN && "Grid number must be
  //   between 1 and "+std::to_string(GRIDN) + " inclusive.)");
  assert(gridNumber > 0 && gridNumber <= GRIDN && "Invalid grid number");
  Game game(gridType, gridNumber);
  game.game_loop();
  return 0;
}