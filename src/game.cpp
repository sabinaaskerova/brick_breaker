#include "game.hpp"


Game::Game(){

};

void Game::init(){
    m_brickGrid = new BrickGrid(9, 14, 30, 30); // TO DO auto detect grid size from file
    m_brickGrid->initGridFromFile("grids/grid3.txt");
    m_brickGrid->printAllBricks();
    // position ballPosition = {350, 350};
    // objectSize ballSize = {25, 25};
    // velocity ballVelocity = {40, 40}; 
    // m_ball = new Ball(ballPosition, ballSize, ballVelocity);
    // position paddlePosition = {400, 400};
    // objectSize paddleSize = {60, 30};
    // m_paddle = new Paddle(paddlePosition, paddleSize);
    
    
}

Game::~Game(){
    delete m_brickGrid;
    delete m_paddle;
    delete m_ball;
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}