#include "game.hpp"


Game::Game(){

};

void Game::init(){
    BrickGrid brickGrid(10, 10, 64, 32);

    brickGrid.initGridFromFile("grids/grid1.txt");

    m_brickGrid = &brickGrid;

}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}