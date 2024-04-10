#include "game.hpp"

Game::Game(){
    m_brickGrid = std::make_unique<BrickGrid>(BRICKW, BRICKW);
    m_brickGrid->initGridFromFile("grids/grid3.txt", INITX, INITY);
    
    position ballPosition = {BALLX, BALLY};
    objectSize ballSize = {BALLSIZE, BALLSIZE};
    velocity ballVelocity = {40, 40};
    m_balls.push_back(std::make_unique<Ball>(ballPosition, ballSize, ballVelocity)); 
    m_numBalls = 1;
    
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
    

        // Initialize SDL_ttf
    if(TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
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
        ball->setVelocityY(-BALLSPEED);
        ball->startGame();
    }
}


void Game::game_loop()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    bool keep_running = true;
    while(keep_running)
    {
        frameStart = SDL_GetTicks();
		while(SDL_PollEvent(&m_window_event) > 0)
		{
			switch(m_window_event.type)
			{
			case SDL_QUIT:
				keep_running = false;
			}

			m_paddle->handle_input(m_window_event);
		}
        
        if(m_numBalls>0){
            update();
		    
        }
        draw();
        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
		
    }
}

void Game::update(){
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); 
    SDL_RenderClear(m_renderer);
    
    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->update();

           if(m_numBalls==1 && m_balls[0]->getPosition().y - m_balls[0]->getSize().height > SCREEN_HEIGHT){
                std::cout << "Game Over" << std::endl;
                m_numBalls=0;
            }
            if(ball->getPosition().x < WALLSX || ball->getPosition().x + ball->getSize().width > SCREEN_WIDTH - WALLSX){
                ball->setVelocityX(-ball->getVelocityX());
            }
            if(ball->getPosition().y < WALLSY ){
                ball->setVelocityY(-ball->getVelocityY());
            }
            
            if(ball->collidesWith(*m_paddle)){
                handleCollision(ball.get(), m_paddle.get());
            }

            for(auto& brick_vector : m_brickGrid->getBricks()){
                for(auto& brick : brick_vector){
                    if(ball->collidesWith(*brick.get()) ){
                        if(!brick->isDestroyed()){
                            handleCollision(ball.get(), brick.get());
                        }
                        
                    }
                }
            }
        }
    }
}

void Game::handleCollision(Ball* ball, GameObject* gameObject){
    
    Brick* brick = dynamic_cast<Brick*>(gameObject);
    Paddle* paddle = dynamic_cast<Paddle*>(gameObject);
    if (brick != nullptr) { // if the object is a brick
        double ballCenterX = ball->getPosition().x + ball->getSize().width / 2;
        double ballCenterY = ball->getPosition().y + ball->getSize().height / 2;
        double brickCenterX = brick->getPosition().x + brick->getSize().width / 2;
        double brickCenterY = brick->getPosition().y + brick->getSize().height / 2;

        double dx = ballCenterX - brickCenterX;
        double dy = ballCenterY - brickCenterY;
        
        if (std::abs(dx) > std::abs(dy)) {
            ball->setVelocityX(-ball->getVelocityX());
        } else {
            ball->setVelocityY(-ball->getVelocityY());
        }

        if(brick->getType() == typeBrick::EMPTY){
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
    else if(paddle != nullptr){
        ball->setVelocityY(-sqrt(abs(BALLSPEED - ball->getVelocityX() * ball->getVelocityX())));
        double impact = (ball->getPosition().x - paddle->getPosition().x) / paddle->getSize().width;
        ball->setVelocityX((impact - 0.5) * BALLSPEED);
        // ball->setVelocityY(-sqrt(abs(BALLSPEED - ball->getVelocityX() * ball->getVelocityX())));
    }
    
    // else{
    //     double impact = (ball->getPosition().x - gameObject->getPosition().x) / gameObject->getSize().width;
    //     // double impact = (ball->getPosition().x - (gameObject->getPosition().x + gameObject->getSize().width / 2)) / gameObject->getSize().width;
    //     ball->setVelocityX((impact - 0.5) * 2 * BALLSPEED);
    //     ball->setVelocityY(-sqrt(abs( BALLSPEED - ball->getVelocityX() * ball->getVelocityX())));
    // }

}

void Game::draw()
{
    
    // SDL_RenderCopy(m_renderer, backgroundImage, nullptr, nullptr); // background image
    m_brickGrid->draw(m_renderer);
    m_wall->draw(m_renderer);
    m_paddle->draw(m_renderer);

    for(auto& ball : m_balls){
        if(ball!=nullptr){
            ball->draw(m_renderer);
        }
    }
    if (m_numBalls == 0) {
        drawText("Game Over", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    SDL_RenderPresent(m_renderer);
}

void Game::drawText(const std::string& text, int x, int y) {
    TTF_Font* font = TTF_OpenFont("./LoveDays-2v7Oe.ttf", 10);
    SDL_Color color = {255,204,255,255}; 

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

    SDL_RenderCopy(m_renderer, texture, NULL, &dst);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
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