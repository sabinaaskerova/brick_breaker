#include "game.hpp"


Game::Game(){

};

void Game::init(){
    // m_brickGrid = new BrickGrid(9, 14, 35, 35); // TO DO auto detect grid size from file
    m_brickGrid = new BrickGrid(35, 35);
    m_brickGrid->initGridFromFile("grids/grid7.txt", INITX, INITY);
    position ballPosition = {350, 350};
    objectSize ballSize = {25, 25};
    velocity ballVelocity = {40, 40}; 
    m_ball = new Ball(ballPosition, ballSize, ballVelocity);
    position paddlePosition = {400, 400};
    objectSize paddleSize = {60, 30};
    // m_paddle = new Paddle(paddlePosition, paddleSize);
    m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);
    
    
}

void Game::update(){
    m_ball->update();
    m_paddle->update();
    m_brickGrid->update();
}

Game::~Game(){
    delete m_brickGrid;
    delete m_ball;
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}

std::unique_ptr<Paddle>& Game::getPaddle() {
    return m_paddle;
}

