#include "game.hpp"


Game::Game(){
    m_brickGrid = std::make_unique<BrickGrid>(BRICKW, BRICKW);
    m_brickGrid->initGridFromFile("grids/grid7.txt", INITX, INITY);
    
    position ballPosition = {BALLX, BALLY};
    objectSize ballSize = {BALLSIZE, BALLSIZE};
    velocity ballVelocity = {40, 40};
    m_balls.push_back(std::make_unique<Ball>(ballPosition, ballSize, ballVelocity));
    
    position paddlePosition = {PADDLEX, PADDLEY};
    objectSize paddleSize = {PADDLEW, PADDLEH};
    m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);
};

void Game::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return ;
    }

    m_window = SDL_CreateWindow("Kirpish syndyru", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    assert (m_window != nullptr);

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    assert (m_renderer != nullptr);
    
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
    // SDL_RenderClear(m_renderer);
    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->update();
        }
    }
    m_paddle->update();
    m_brickGrid->update();
}




void Game::draw()
{
    SDL_Rect walls;
    walls.x = WALLSX;
    walls.y = WALLSY;
    walls.w = WALLSW; 
    walls.h = WALLSH;

    SDL_SetRenderDrawColor(m_renderer, 204, 153, 255, 255);
    for (int i = 0; i < 5; i++) {
        SDL_Rect thickWalls;
        thickWalls.x = walls.x - i;
        thickWalls.y = walls.y - i;
        thickWalls.w = walls.w + 2 * i;
        thickWalls.h = walls.h + 2 * i;
        SDL_RenderDrawRect(m_renderer, &thickWalls);
    }
    SDL_RenderDrawRect(m_renderer, &walls);
    SDL_RenderPresent(m_renderer);
    SDL_UpdateWindowSurface(m_window);

    

	m_paddle->draw(m_renderer);
	
    SDL_RenderPresent(m_renderer);
}


BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}

std::unique_ptr<Paddle>& Game::getPaddle() {
    return m_paddle;
}

Game::~Game(){
    // if(m_brickGrid != nullptr){
        // delete m_brickGrid;
    // }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
   
    
}