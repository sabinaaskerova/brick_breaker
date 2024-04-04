#include "game.hpp"


Game::Game(){

};

void Game::init(){
    m_brickGrid = new BrickGrid(9, 14, 30, 30); // TO DO auto detect grid size from file
    m_brickGrid->initGridFromFile("grids/grid1.txt");
}

Game::~Game(){
    delete m_brickGrid;
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}