#include "game.hpp"


Game::Game(){

};

void Game::init(){
    m_brickGrid = new BrickGrid(10, 10, 64, 32);
    m_brickGrid->initGridFromFile("grids/grid1.txt");
}

Game::~Game(){
    delete m_brickGrid;
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}