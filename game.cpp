#include "game.hpp"


Game::Game(){

};

void Game::init(){
    BrickGrid brickGrid({0, 0}, {640, 480}, 10, 10, 64, 32);
    brickGrid.initGridFromFile("grids/grid1.txt");
}