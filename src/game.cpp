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
    // m_ball = new Ball(ballPosition, ballSize, ballVelocity);
    m_balls.push_back(std::make_unique<Ball>(ballPosition, ballSize, ballVelocity));
    position paddlePosition = {400, 400};
    objectSize paddleSize = {60, 30};
    // m_paddle = new Paddle(paddlePosition, paddleSize);
    m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);
    
    
}


void Game::game_loop()
{
    bool keep_running = true;
    while(keep_running)
    {
		while(SDL_PollEvent(&m_window_event) > 0)
		{
			switch(m_window_event.type)
			{
			case SDL_QUIT:
				keep_running = false;
			}

			m_paddle->handle_input(m_window_event);
		}

		update();
		draw();
    }
}

void Game::update(){
    m_ball->update();
    m_paddle->update();
    m_brickGrid->update();
}

Game::~Game(){
    // if(m_brickGrid != nullptr){
        // delete m_brickGrid;
    // }
   
    
}

BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}

std::unique_ptr<Paddle>& Game::getPaddle() {
    return m_paddle;
}


void Game::draw()
{
    SDL_RenderClear(m_renderer);

	m_paddle->draw(m_renderer);
	
    SDL_RenderPresent(m_renderer);
}
