#include "game.hpp"


Game::Game(){

};

void Game::init(){
    m_brickGrid = new BrickGrid(9, 14, 30, 30); // TO DO auto detect grid size from file
    m_brickGrid->initGridFromFile("grids/grid1.txt");
    position ballPosition = {350, 350};
    objectSize ballSize = {25, 25};
    velocity ballVelocity = {40, 40}; 
    Ball* ball = new Ball(ballPosition, ballSize, ballVelocity);
    m_gameObjects.push_back(ball);
    
}

Game::~Game(){
    delete m_brickGrid;
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}