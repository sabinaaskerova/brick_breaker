#include "game.hpp"

Game::Game(){
    m_brickGrid = std::make_unique<BrickGrid>(BRICKW, BRICKW);
    m_brickGrid->initGridFromFile("grids/grid3.txt", INITX, INITY);
    
    position ballPosition = {BALLX, BALLY};
    objectSize ballSize = {BALLSIZE, BALLSIZE};
    velocity ballVelocity = {40, 40};
    m_balls.push_back(std::make_unique<Ball>(ballPosition, ballSize, ballVelocity)); 
    position paddlePosition = {PADDLEX, PADDLEY};
    objectSize paddleSize = {PADDLEW, PADDLEH};
    m_paddle = std::make_unique<Paddle>(paddlePosition, paddleSize);

    position wallPosition = {WALLSX, WALLSY};
    objectSize wallSize = {WALLSW, WALLSH};
    m_wall = std::make_unique<Wall>(wallPosition, wallSize);
};

void Game::init(){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return ;
    }
  
    m_window = SDL_CreateWindow("Kirpish syndyru", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == nullptr) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return ; // TO DO: throw an exception
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return ; // TO DO: throw an exception throw std::runtime_error(SDL_GetError());
    }

    backgroundImage = IMG_LoadTexture(m_renderer, "img/qazaqyurt.png");
    if (backgroundImage == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }
   
    for(auto& ball : m_balls){
        ball->init(m_renderer, ball->getPosition().x, ball->getPosition().y);
        ball->setMoving(true);
        ball->setVelocityX(0);
        ball->setVelocityY(-2);
        ball->startGame();
    }  
    // SDL_RenderPresent(m_renderer);
    
    
    
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
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); 
    SDL_RenderClear(m_renderer);
    
    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->update();

            // Check for collision with walls
            if(ball->getPosition().x < 0 || ball->getPosition().x + ball->getSize().width > SCREEN_WIDTH){
                ball->setVelocityX(-ball->getVelocityX());
            }
            if(ball->getPosition().y < 0 || ball->getPosition().y + ball->getSize().height > SCREEN_HEIGHT){
                ball->setVelocityY(-ball->getVelocityY());
            }
            
            if(ball->collidesWith(*m_paddle)){
                handleCollision(ball.get(), m_paddle.get());
            }
            for(auto& brick_vector : m_brickGrid->getBricks()){
                for(auto& brick : brick_vector){
                    // std::cout << brick->getPosition().x << " " << brick->getPosition().y << " " << brick->getSize().width << " " << brick->getSize().height << std::endl;
                    if(ball->collidesWith(*brick.get()) ){
                        if(!brick->isDestroyed()){
                            handleCollision(ball.get(), brick.get());
                        }
                        
                    }
                }
            }
            // if (ball->collidesWith(*m_wall)) {
            //     // std::cout << "Collided with wall" << std::endl;
            //     ball->setVelocityX(-ball->getVelocityX());
            //     ball->setVelocityY(-ball->getVelocityY());
            // }
        }
    }
    
    // m_paddle->update();
    // m_brickGrid->update();
}

void Game::handleCollision(Ball* ball, GameObject* gameObject){
    

    Brick* brick = dynamic_cast<Brick*>(gameObject);
    if (brick != nullptr) { // if the object is a brick
        if(brick->getType() == typeBrick::EMPTY){
            // If the brick is of type EMPTY, return without changing the ball's direction
            return;
        }
        else if(brick->getType() == typeBrick::NORMAL){
            brick->setDestroyed(true);
        }else if(brick->getType() == typeBrick::DOUBLE){
            brick->setType(typeBrick::NORMAL);
        }else if(brick->getType() == typeBrick::TRIPLE){
            brick->setType(typeBrick::DOUBLE);
        }
    }

    ball->setVelocityX(-ball->getVelocityX());
    ball->setVelocityY(-ball->getVelocityY());
}

void Game::draw()
{
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, backgroundImage, nullptr, nullptr);
    m_wall->draw(m_renderer);
    m_brickGrid->draw(m_renderer);
    m_paddle->draw(m_renderer);

    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->draw(m_renderer);
        }
    }
    
    
    SDL_RenderPresent(m_renderer);
    SDL_UpdateWindowSurface(m_window);
}


BrickGrid& Game::getBrickGrid(){
    return *m_brickGrid;
}

std::unique_ptr<Paddle>& Game::getPaddle() {
    return m_paddle;
}

Game::~Game(){
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}